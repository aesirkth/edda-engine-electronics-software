// Codegen file. Do not edit manually!

#ifndef EDDA_PACKERS_H
#define EDDA_PACKERS_H

#include <stdint.h>

namespace EddaCAN {
  uint16_t pack_float_into_uint16_t(float value, const float minValue, const float maxValue);

  float unpack_uint16_t_into_float(uint16_t value, const float minValue, const float maxValue);

  uint8_t pack_float_into_uint8_t(float value, const float minValue, const float maxValue);

  float unpack_uint8_t_into_float(uint8_t value, const float minValue, const float maxValue);

  uint32_t pack_float_into_uint32_t(float value, const float minValue, const float maxValue);

  float unpack_uint32_t_into_float(uint32_t value, const float minValue, const float maxValue);
}

#endif