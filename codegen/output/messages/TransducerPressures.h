// Codegen file. Do not edit manually!

#ifndef EDDA_MESSAGES_TRANSDUCERPRESSURES_H
#define EDDA_MESSAGES_TRANSDUCERPRESSURES_H

#include <stdint.h>;
#include <limits.h>;
#include <string.h>;
#include "../enums.h";
#include "../packers.h";

namespace EddaCAN {
  class alignas(8) TransducerPressures_Msg {
    private:
      uint32_t pressures_0;
      uint32_t pressures_1;

    public:
      static const float pressures_0_minValue;
      static const float pressures_0_maxValue;
      static const float pressures_1_minValue;
      static const float pressures_1_maxValue;

      void set_pressures_0(float value);
      void set_pressures_1(float value);

      float get_pressures_0();
      float get_pressures_1();

  };
  
}

#endif