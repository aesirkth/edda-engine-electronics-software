#ifndef SixtyFourBitTime_H
#define SixtyFourBitTime_H

#include <stdint.h>
#include <Arduino.h>

class SixtyFourBitTime {
  private:
    uint32_t rolloverMillis;
    uint32_t rolloverMicros;

    uint64_t rolloverMillisFraction;
    uint64_t rolloverMicrosFraction;

    uint32_t lastMillis;
    uint32_t lastMicros;
  
  public:
    SixtyFourBitTime();
    
    uint64_t getCurrentMicros();
    uint64_t getCurrentMillis();

    int64_t getCurrentMicrosSigned();
    int64_t getCurrentMillisSigned();
};

#endif