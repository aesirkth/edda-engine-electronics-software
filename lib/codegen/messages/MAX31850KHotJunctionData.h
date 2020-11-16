// Codegen file. Do not edit manually!

#ifndef EDDA_MESSAGES_MAX_____KHOTJUNCTIONDATA_H
#define EDDA_MESSAGES_MAX_____KHOTJUNCTIONDATA_H

#include <stdint.h>
#include <limits.h>
#include <string.h>
#include "../enums.h"
#include "../packers.h"

namespace EddaCAN {
  class alignas(8) MAX31850KHotJunctionData_DataType {
    private:
      uint16_t temperatures_0 __attribute__((packed));
      uint16_t temperatures_1 __attribute__((packed));
      uint16_t temperatures_2 __attribute__((packed));
      uint16_t temperatures_3 __attribute__((packed));

    public:
      static const float temperatures_0_minValue __attribute__((packed));
      static const float temperatures_0_maxValue __attribute__((packed));
      static const float temperatures_1_minValue __attribute__((packed));
      static const float temperatures_1_maxValue __attribute__((packed));
      static const float temperatures_2_minValue __attribute__((packed));
      static const float temperatures_2_maxValue __attribute__((packed));
      static const float temperatures_3_minValue __attribute__((packed));
      static const float temperatures_3_maxValue __attribute__((packed));

      void set_temperatures_0(float value);
      void set_temperatures_1(float value);
      void set_temperatures_2(float value);
      void set_temperatures_3(float value);

      float get_temperatures_0();
      float get_temperatures_1();
      float get_temperatures_2();
      float get_temperatures_3();

  };
  
}

#endif