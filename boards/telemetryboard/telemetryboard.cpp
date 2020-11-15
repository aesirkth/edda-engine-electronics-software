#include "telemetryboard.h"

#define ONBOARD_LED_PIN 13
#define VCC_LED_PIN 33

void setup() {
  pinMode(ONBOARD_LED_PIN, OUTPUT);

  pinMode(VCC_LED_PIN, OUTPUT);
  digitalWrite(VCC_LED_PIN, HIGH);
}

void loop() {
  digitalToggle(ONBOARD_LED_PIN);
  delay(1000);
}