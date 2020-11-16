// Codegen file. Do not edit manually!

#include <stdint.h>
#include <limits.h>
#include <string.h>
#include "../enums.h"
#include "../packers.h"
#include "MAX31850KHotJunctionData.h"

namespace EddaCAN {
  void MAX31850KHotJunctionData_DataType::set_temperatures_0(float value) {
    temperatures_0 = pack_float_into_uint16_t(value, temperatures_0_minValue, temperatures_0_maxValue);
  }
  void MAX31850KHotJunctionData_DataType::set_temperatures_1(float value) {
    temperatures_1 = pack_float_into_uint16_t(value, temperatures_1_minValue, temperatures_1_maxValue);
  }
  void MAX31850KHotJunctionData_DataType::set_temperatures_2(float value) {
    temperatures_2 = pack_float_into_uint16_t(value, temperatures_2_minValue, temperatures_2_maxValue);
  }
  void MAX31850KHotJunctionData_DataType::set_temperatures_3(float value) {
    temperatures_3 = pack_float_into_uint16_t(value, temperatures_3_minValue, temperatures_3_maxValue);
  }

  float MAX31850KHotJunctionData_DataType::get_temperatures_0() {
    return unpack_uint16_t_into_float(temperatures_0, temperatures_0_minValue, temperatures_0_maxValue);
  }
  float MAX31850KHotJunctionData_DataType::get_temperatures_1() {
    return unpack_uint16_t_into_float(temperatures_1, temperatures_1_minValue, temperatures_1_maxValue);
  }
  float MAX31850KHotJunctionData_DataType::get_temperatures_2() {
    return unpack_uint16_t_into_float(temperatures_2, temperatures_2_minValue, temperatures_2_maxValue);
  }
  float MAX31850KHotJunctionData_DataType::get_temperatures_3() {
    return unpack_uint16_t_into_float(temperatures_3, temperatures_3_minValue, temperatures_3_maxValue);
  }

  const float MAX31850KHotJunctionData_DataType::temperatures_0_minValue = -270.00000000;
  const float MAX31850KHotJunctionData_DataType::temperatures_0_maxValue = 1372.00000000;
  const float MAX31850KHotJunctionData_DataType::temperatures_1_minValue = -270.00000000;
  const float MAX31850KHotJunctionData_DataType::temperatures_1_maxValue = 1372.00000000;
  const float MAX31850KHotJunctionData_DataType::temperatures_2_minValue = -270.00000000;
  const float MAX31850KHotJunctionData_DataType::temperatures_2_maxValue = 1372.00000000;
  const float MAX31850KHotJunctionData_DataType::temperatures_3_minValue = -270.00000000;
  const float MAX31850KHotJunctionData_DataType::temperatures_3_maxValue = 1372.00000000;

  static_assert((sizeof(MAX31850KHotJunctionData_DataType) <= 8), "sizeof(MAX31850KHotJunctionData_DataType) must be less than 8 bytes!");
  
}