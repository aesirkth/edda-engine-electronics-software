#include "64bittime.h"

#define CLOCK_SCALING_FACTOR_MS 1
#define CLOCK_SCALING_FACTOR_US 1

#define GET_MILLIS ((uint32_t)(millis() * CLOCK_SCALING_FACTOR_MS))
#define GET_MICROS ((uint32_t)(micros() * CLOCK_SCALING_FACTOR_US))

SixtyFourBitTime::SixtyFourBitTime() {
  noInterrupts();
  rolloverMillis = 0;
  rolloverMicros = 0;
  lastMillis = GET_MILLIS;
  lastMicros = GET_MICROS;
  interrupts();
}

uint64_t SixtyFourBitTime::getCurrentMicros() {
  noInterrupts();
  uint32_t currentMicros = GET_MICROS;
  // This only really holds if calling this function once in each interval of 2^32 microseconds.
  if(currentMicros < lastMicros) {
    ++rolloverMicros;
    rolloverMicrosFraction = ((uint64_t) rolloverMicros) << 32;
  }

  lastMicros = currentMicros;

  uint64_t value = ((uint64_t) currentMicros) | rolloverMicrosFraction;
  interrupts();
  return value;
}

uint64_t SixtyFourBitTime::getCurrentMillis() {
  noInterrupts();
  uint32_t currentMillis = GET_MILLIS;
  // This only really holds if calling this function once in each interval of 2^32 microseconds.
  if(currentMillis < lastMicros) {
    ++rolloverMillis;
    rolloverMillisFraction = ((uint64_t) rolloverMillis) << 32;
  }

  lastMillis = currentMillis;

  uint64_t value = ((uint64_t) currentMillis) | rolloverMillisFraction;
  interrupts();
  return value;
}

int64_t SixtyFourBitTime::getCurrentMicrosSigned() {
  return (int64_t)getCurrentMicros();
}

int64_t SixtyFourBitTime::getCurrentMillisSigned() {
  return (int64_t)getCurrentMillis();
}
