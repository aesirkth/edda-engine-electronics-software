// Codegen file. Do not edit manually!

#ifndef EDDA_MESSAGES_AMBIENTPRESSURESENSORDATA_H
#define EDDA_MESSAGES_AMBIENTPRESSURESENSORDATA_H

#include <stdint.h>;
#include <limits.h>;
#include <string.h>;
#include "../enums.h";
#include "../packers.h";

namespace EddaCAN {
  class alignas(8) AmbientPressureSensorData_Msg {
    private:
      uint32_t pressure;
      uint16_t temperature;

    public:
      static const float pressure_minValue;
      static const float pressure_maxValue;
      static const float temperature_minValue;
      static const float temperature_maxValue;

      void set_pressure(float value);
      void set_temperature(float value);

      float get_pressure();
      float get_temperature();

  };
  
}

#endif