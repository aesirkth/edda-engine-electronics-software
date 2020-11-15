// Codegen file. Do not edit manually!

#ifndef EDDA_MESSAGES_MAX_____KCOLDJUNCTIONDATA_H
#define EDDA_MESSAGES_MAX_____KCOLDJUNCTIONDATA_H

#include <stdint.h>;
#include <limits.h>;
#include <string.h>;
#include "../enums.h";
#include "../packers.h";

namespace EddaCAN {
  class alignas(8) MAX31850KColdJunctionData_Msg {
    private:
      uint8_t temperatures_0;
      uint8_t temperatures_1;
      uint8_t temperatures_2;
      uint8_t temperatures_3;
      uint8_t temperatures_4;
      uint8_t temperatures_5;
      uint8_t temperatures_6;
      uint8_t temperatures_7;

    public:
      static const float temperatures_0_minValue;
      static const float temperatures_0_maxValue;
      static const float temperatures_1_minValue;
      static const float temperatures_1_maxValue;
      static const float temperatures_2_minValue;
      static const float temperatures_2_maxValue;
      static const float temperatures_3_minValue;
      static const float temperatures_3_maxValue;
      static const float temperatures_4_minValue;
      static const float temperatures_4_maxValue;
      static const float temperatures_5_minValue;
      static const float temperatures_5_maxValue;
      static const float temperatures_6_minValue;
      static const float temperatures_6_maxValue;
      static const float temperatures_7_minValue;
      static const float temperatures_7_maxValue;

      void set_temperatures_0(float value);
      void set_temperatures_1(float value);
      void set_temperatures_2(float value);
      void set_temperatures_3(float value);
      void set_temperatures_4(float value);
      void set_temperatures_5(float value);
      void set_temperatures_6(float value);
      void set_temperatures_7(float value);

      float get_temperatures_0();
      float get_temperatures_1();
      float get_temperatures_2();
      float get_temperatures_3();
      float get_temperatures_4();
      float get_temperatures_5();
      float get_temperatures_6();
      float get_temperatures_7();

  };
  
}

#endif