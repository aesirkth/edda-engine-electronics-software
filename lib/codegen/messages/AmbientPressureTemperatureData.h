// Codegen file. Do not edit manually!

#ifndef EDDA_MESSAGES_AMBIENTPRESSURETEMPERATUREDATA_H
#define EDDA_MESSAGES_AMBIENTPRESSURETEMPERATUREDATA_H

#include <stdint.h>
#include <limits.h>
#include <string.h>
#include "../enums.h"
#include "../packers.h"

namespace EddaCAN {
  class alignas(8) AmbientPressureTemperatureData_DataType {
    private:
      uint32_t pressure __attribute__((packed));
      uint16_t temperature __attribute__((packed));

    public:
      static const float pressure_minValue __attribute__((packed));
      static const float pressure_maxValue __attribute__((packed));
      static const float temperature_minValue __attribute__((packed));
      static const float temperature_maxValue __attribute__((packed));

      void set_pressure(float value);
      void set_temperature(float value);

      float get_pressure();
      float get_temperature();

  };
  
}

#endif