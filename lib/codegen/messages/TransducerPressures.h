// Codegen file. Do not edit manually!

#ifndef EDDA_MESSAGES_TRANSDUCERPRESSURES_H
#define EDDA_MESSAGES_TRANSDUCERPRESSURES_H

#include <stdint.h>
#include <limits.h>
#include <string.h>
#include "../enums.h"
#include "../packers.h"

namespace EddaCAN {
  class alignas(8) TransducerPressures_DataType {
    private:
      uint32_t pressures_0 __attribute__((packed));
      uint32_t pressures_1 __attribute__((packed));

    public:
      static const float pressures_0_minValue __attribute__((packed));
      static const float pressures_0_maxValue __attribute__((packed));
      static const float pressures_1_minValue __attribute__((packed));
      static const float pressures_1_maxValue __attribute__((packed));

      void set_pressures_0(float value);
      void set_pressures_1(float value);

      float get_pressures_0();
      float get_pressures_1();

  };
  
}

#endif