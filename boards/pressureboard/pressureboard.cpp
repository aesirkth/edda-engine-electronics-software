#include "pressureboard.h"
#include <FlexCAN_T4.h>
#include "codegen.h"
#include <string.h>

IntervalTimer canTimer;
FlexCAN_T4<CAN2, RX_SIZE_256, TX_SIZE_16> myCan;

#define ONBOARD_LED_PIN 13
#define VCC_LED_PIN 3

#define CAN_RS_PIN 2

#define TIMESYNC_REQUEST_RX_ID 4
#define TIMESYNC_LATENCY_RESPONSE_RX_ID 5
#define TIMESYNC_TIME_RESPONSE_RX_ID 6

#define TIMESYNC_REQUEST_TX_ID 1
#define TIMESYNC_LATENCY_RESPONSE_TX_ID 2
#define TIMESYNC_TIME_RESPONSE_TX_ID 3

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

void canSniff(const CAN_message_t &msg) {
}

elapsedMillis sinceLastRequest;

void checkEvents() {
  myCan.events();
}

volatile uint32_t currentRTT;
volatile uint64_t currentTime;
volatile double clockScaling = 1.0;
volatile bool hasCurrentTime = false;
elapsedMicros timeSinceLastTimeAssignment;

void ext_output2(const CAN_message_t &msg){
  if(msg.id == TIMESYNC_REQUEST_RX_ID) {
    // Serial.println("== Got sync request ==");
    EddaCAN::TimeSyncRequest_DataType syncRequest;
    memcpy(&syncRequest, msg.buf, msg.len);

    // Serial.print("source: "); Serial.println(syncRequest.get_source());
    // Serial.print("requestIdentifier: "); Serial.println(syncRequest.get_requestIdentifier());
    // Serial.print("initiatedAtMicros: "); Serial.println(syncRequest.get_initiatedAtMicros());

    
    EddaCAN::TimeSyncLatencyResponse_DataType latencyResponse;
    latencyResponse.set_destination(syncRequest.get_source());
    latencyResponse.set_requestIdentifier(syncRequest.get_requestIdentifier());
    latencyResponse.set_initiatedAtMillis(syncRequest.get_initiatedAtMillis());
    latencyResponse.set_initiatedAtMicros(syncRequest.get_initiatedAtMicros());

    CAN_message_t msg;
    msg.id = TIMESYNC_LATENCY_RESPONSE_TX_ID;
    msg.len = sizeof(latencyResponse);
    msg.seq = true;
    memcpy(msg.buf, &latencyResponse, sizeof(latencyResponse));
    
    myCan.write(msg);


    EddaCAN::TimeSyncTimeResponse_DataType timeResponse;
    timeResponse.set_destination(syncRequest.get_source());
    timeResponse.set_requestIdentifier(syncRequest.get_requestIdentifier());
    uint32_t currentMillis = millis();
    uint32_t currentMicros = micros();
    timeResponse.set_responseMillis(currentMillis);
    timeResponse.set_responseMicros(currentMicros % 1000);

    msg.id = TIMESYNC_TIME_RESPONSE_TX_ID;
    msg.len = sizeof(timeResponse);
    msg.seq = true;
    memcpy(msg.buf, &timeResponse, sizeof(timeResponse));
    
    myCan.write(msg);
  }

  if(msg.id == TIMESYNC_LATENCY_RESPONSE_RX_ID) {
    // Serial.println("== Got sync response ==");
    EddaCAN::TimeSyncLatencyResponse_DataType latencyResponse;
    memcpy(&latencyResponse, msg.buf, msg.len);

    // Serial.print("destination: "); Serial.println(syncResponse.get_destination());
    // Serial.print("requestIdentifier: "); Serial.println(syncResponse.get_requestIdentifier());
    // Serial.print("initiatedAtMicros: "); Serial.println(syncResponse.get_initiatedAtMicros());
    uint32_t millisLatency = millis() - latencyResponse.get_initiatedAtMillis();
    uint32_t microsLatency = (micros() % 1000) - latencyResponse.get_initiatedAtMicros();
    currentRTT = (uint32_t)millisLatency * 1000 + (uint32_t)microsLatency;
  }

  if(msg.id == TIMESYNC_TIME_RESPONSE_RX_ID) {
    // Serial.println("== Got sync response ==");
    EddaCAN::TimeSyncTimeResponse_DataType timeResponse;
    memcpy(&timeResponse, msg.buf, msg.len);

    // Serial.print("destination: "); Serial.println(syncResponse.get_destination());
    // Serial.print("requestIdentifier: "); Serial.println(syncResponse.get_requestIdentifier());
    // Serial.print("initiatedAtMicros: "); Serial.println(syncResponse.get_initiatedAtMicros());
    uint32_t millisTime = timeResponse.get_responseMillis();
    uint32_t microsTime = timeResponse.get_responseMicros();

    uint64_t newTime = (uint64_t)millisTime * 1000 + (uint64_t)microsTime + currentRTT / 2;

    Serial.print("latency: "); Serial.println(currentRTT);
    Serial.print("fetched time: "); Serial.println(newTime / 1.0e6);

    if(hasCurrentTime) {
      uint64_t correctedTime = currentTime + (uint64_t)((double)timeSinceLastTimeAssignment * clockScaling);
      Serial.print("time: "); Serial.println(correctedTime / 1.0e6);
      int32_t drift = correctedTime - newTime;
      clockScaling = 1.0 - drift * 1e-3;
      Serial.print("drift: "); Serial.println(drift);
      Serial.print("clockScaling: "); Serial.println(clockScaling, 10);
    } else {
      currentTime = newTime;
      timeSinceLastTimeAssignment = 0;
      clockScaling = 1.0;
    }
    hasCurrentTime = true;
  }
}

void loop() {
  if(sinceLastRequest > 10000) {
    sinceLastRequest = 0;
    digitalToggle(ONBOARD_LED_PIN);

    EddaCAN::TimeSyncRequest_DataType syncRequest;
    syncRequest.set_source(0);
    syncRequest.set_requestIdentifier(0);
    syncRequest.set_initiatedAtMillis(millis());
    syncRequest.set_initiatedAtMicros(micros() % 1000);

    CAN_message_t msg;
    msg.id = TIMESYNC_REQUEST_TX_ID;
    msg.len = sizeof(syncRequest);
    msg.seq = true;
    memcpy(msg.buf, &syncRequest, sizeof(syncRequest));
    
    myCan.write(msg);

    delayMicroseconds(250);
  }
}