// Codegen file. Do not edit manually!

#include <stdint.h>;
#include "packers.h";

namespace EddaCAN {
  inline uint16_t pack_float_into_uint16_t(float value, const float minValue, const float maxValue) {
    if(value < minValue) { return 0; }
    if(value > maxValue) { return UINT16_MAX; }

    float ratio = ((float) value - minValue) / (maxValue - minValue);
    return 1 + (uint16_t) ((float) (UINT16_MAX - 2)) * ratio;
  }

  inline float unpack_uint16_t_into_float(uint16_t value, const float minValue, const float maxValue) {
    if(value <= 0) {
      return minValue - 1.0;
    }
    if(value >= UINT16_MAX) {
      return maxValue + 1.0;
    }

    float ratio = (float)(value - 1) / (float) (UINT16_MAX - 2);
    return ratio * (maxValue - minValue) + minValue;
  }

  inline uint8_t pack_float_into_uint8_t(float value, const float minValue, const float maxValue) {
    if(value < minValue) { return 0; }
    if(value > maxValue) { return UINT8_MAX; }

    float ratio = ((float) value - minValue) / (maxValue - minValue);
    return 1 + (uint8_t) ((float) (UINT8_MAX - 2)) * ratio;
  }

  inline float unpack_uint8_t_into_float(uint8_t value, const float minValue, const float maxValue) {
    if(value <= 0) {
      return minValue - 1.0;
    }
    if(value >= UINT8_MAX) {
      return maxValue + 1.0;
    }

    float ratio = (float)(value - 1) / (float) (UINT8_MAX - 2);
    return ratio * (maxValue - minValue) + minValue;
  }

  inline uint32_t pack_float_into_uint32_t(float value, const float minValue, const float maxValue) {
    if(value < minValue) { return 0; }
    if(value > maxValue) { return UINT32_MAX; }

    float ratio = ((float) value - minValue) / (maxValue - minValue);
    return 1 + (uint32_t) ((float) (UINT32_MAX - 2)) * ratio;
  }

  inline float unpack_uint32_t_into_float(uint32_t value, const float minValue, const float maxValue) {
    if(value <= 0) {
      return minValue - 1.0;
    }
    if(value >= UINT32_MAX) {
      return maxValue + 1.0;
    }

    float ratio = (float)(value - 1) / (float) (UINT32_MAX - 2);
    return ratio * (maxValue - minValue) + minValue;
  }
}