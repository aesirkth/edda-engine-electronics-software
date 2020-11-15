// Codegen file. Do not edit manually!

#include <stdint.h>;
#include <limits.h>;
#include <string.h>;
#include "../enums.h";
#include "../packers.h";
#include "TransducerPressures.h";

namespace EddaCAN {
  void TransducerPressures_DataType::set_pressures_0(float value) {
    pressures_0 = pack_float_into_uint32_t(value, pressures_0_minValue, pressures_0_maxValue);
  }
  void TransducerPressures_DataType::set_pressures_1(float value) {
    pressures_1 = pack_float_into_uint32_t(value, pressures_1_minValue, pressures_1_maxValue);
  }

  float TransducerPressures_DataType::get_pressures_0() {
    return unpack_uint32_t_into_float(pressures_0, pressures_0_minValue, pressures_0_maxValue);
  }
  float TransducerPressures_DataType::get_pressures_1() {
    return unpack_uint32_t_into_float(pressures_1, pressures_1_minValue, pressures_1_maxValue);
  }

  const float TransducerPressures_DataType::pressures_0_minValue = 0.00000000;
  const float TransducerPressures_DataType::pressures_0_maxValue = 100000000.00000000;
  const float TransducerPressures_DataType::pressures_1_minValue = 0.00000000;
  const float TransducerPressures_DataType::pressures_1_maxValue = 100000000.00000000;

  static_assert((sizeof(TransducerPressures_DataType) <= 8), "sizeof(TransducerPressures_DataType) must be less than 8 bytes!");
  
}