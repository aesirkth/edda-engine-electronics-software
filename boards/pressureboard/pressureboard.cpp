#include "pressureboard.h"
#include <FlexCAN_T4.h>
#include "codegen.h"
#include <string.h>

#include "64bittime.h"
#include "timeSync.h"
#include "canTimeSync.h"
#include "printNonNativeTypes.h"

#define ONBOARD_LED_PIN 13
#define VCC_LED_PIN 3

#define CAN_RS_PIN 2


EddaCANTimeSync canTimeSync(2, 1, 4, 3, 6, 5);

IntervalTimer canTimer;
FlexCAN_T4<CAN2, RX_SIZE_256, TX_SIZE_16> myCan;

SixtyFourBitTime sixtyFourBitTime;
TimeSync timeSync;

void canSniff(const CAN_message_t &msg);
void checkEvents();

void setup() {
  Serial.begin(9600);

  pinMode(CAN_RS_PIN, OUTPUT); 
  digitalWrite(CAN_RS_PIN, LOW);

  myCan.begin();
  myCan.setBaudRate(1000000);
  myCan.onReceive(canSniff);
  myCan.enableMBInterrupts();

  pinMode(ONBOARD_LED_PIN, OUTPUT);

  pinMode(VCC_LED_PIN, OUTPUT);
  digitalWrite(VCC_LED_PIN, HIGH);

  canTimer.begin(checkEvents, 2500);
}

void checkEvents() {
  myCan.events();
}

elapsedMillis timeSinceLastSync;

bool lastLedNum = false;
bool lastPrintNum = false;
void loop() {
  noInterrupts();
  uint64_t timeNow = timeSync.getMicroseconds();

  bool ledNum = (timeNow / 200000) % 2 == 0;
  bool printNum = (timeNow / 1000000) % 2 == 0;

  if(ledNum != lastLedNum) {
    digitalWrite(ONBOARD_LED_PIN, ledNum);
    lastLedNum = ledNum;
  }

  if(timeSinceLastSync > 500) {
    timeSinceLastSync = 0;
    timeSync.updateRemoteTime(sixtyFourBitTime.getCurrentMicros());
  }
  
  if(printNum != lastPrintNum) {
    switch(timeSync.getStatus()) {
      case TimeSyncStatus::PendingRemoteTime:
        Serial.println("PendingRemoteTime");
        break;
      case TimeSyncStatus::AcquiringSync:
        Serial.println("AcquiringSync");
        break;
      case TimeSyncStatus::SyncedWithinMillisecond:
        Serial.println("SyncedWithinMillisecond");
        break;
      case TimeSyncStatus::Synced:
        Serial.println("Synced");
        break;
    }
    Serial.print("Remote: "); Serial.println((double)sixtyFourBitTime.getCurrentMicros() / 1e6, 8);
    Serial.print("Time: "); Serial.println(timeSync.getSeconds(), 8);
    Serial.print("Deviation: "); Serial.println((int)timeSync.getDeviation());
    Serial.print("Scaling Rate: "); Serial.println(timeSync.getScalingRate(), 10);
    Serial.print("RTT: "); Serial.println(canTimeSync.getRTT());
    lastPrintNum = printNum;
  }
  interrupts();
}

void canSniff(const CAN_message_t &msg) {
}


void ext_output2(const CAN_message_t &msg){
  uint64_t remoteTime;
  if(timeSync.getStatus() == TimeSyncStatus::Synced && canTimeSync.processFrame(&remoteTime, timeSync, msg, [](auto a) { return myCan.write(a); })) {
    timeSync.updateRemoteTime(remoteTime);
    return;
  }
}