// Codegen file. Do not edit manually!

#include <stdint.h>;
#include <limits.h>;
#include <string.h>;
#include "../enums.h";
#include "../packers.h";
#include "MAX31850KColdJunctionData.h";

namespace EddaCAN {
  void MAX31850KColdJunctionData_Msg::set_temperatures_0(float value) {
    temperatures_0 = pack_float_into_uint8_t(value, temperatures_0_minValue, temperatures_0_maxValue);
  }
  void MAX31850KColdJunctionData_Msg::set_temperatures_1(float value) {
    temperatures_1 = pack_float_into_uint8_t(value, temperatures_1_minValue, temperatures_1_maxValue);
  }
  void MAX31850KColdJunctionData_Msg::set_temperatures_2(float value) {
    temperatures_2 = pack_float_into_uint8_t(value, temperatures_2_minValue, temperatures_2_maxValue);
  }
  void MAX31850KColdJunctionData_Msg::set_temperatures_3(float value) {
    temperatures_3 = pack_float_into_uint8_t(value, temperatures_3_minValue, temperatures_3_maxValue);
  }
  void MAX31850KColdJunctionData_Msg::set_temperatures_4(float value) {
    temperatures_4 = pack_float_into_uint8_t(value, temperatures_4_minValue, temperatures_4_maxValue);
  }
  void MAX31850KColdJunctionData_Msg::set_temperatures_5(float value) {
    temperatures_5 = pack_float_into_uint8_t(value, temperatures_5_minValue, temperatures_5_maxValue);
  }
  void MAX31850KColdJunctionData_Msg::set_temperatures_6(float value) {
    temperatures_6 = pack_float_into_uint8_t(value, temperatures_6_minValue, temperatures_6_maxValue);
  }
  void MAX31850KColdJunctionData_Msg::set_temperatures_7(float value) {
    temperatures_7 = pack_float_into_uint8_t(value, temperatures_7_minValue, temperatures_7_maxValue);
  }

  float MAX31850KColdJunctionData_Msg::get_temperatures_0() {
    return unpack_uint8_t_into_float(temperatures_0, temperatures_0_minValue, temperatures_0_maxValue);
  }
  float MAX31850KColdJunctionData_Msg::get_temperatures_1() {
    return unpack_uint8_t_into_float(temperatures_1, temperatures_1_minValue, temperatures_1_maxValue);
  }
  float MAX31850KColdJunctionData_Msg::get_temperatures_2() {
    return unpack_uint8_t_into_float(temperatures_2, temperatures_2_minValue, temperatures_2_maxValue);
  }
  float MAX31850KColdJunctionData_Msg::get_temperatures_3() {
    return unpack_uint8_t_into_float(temperatures_3, temperatures_3_minValue, temperatures_3_maxValue);
  }
  float MAX31850KColdJunctionData_Msg::get_temperatures_4() {
    return unpack_uint8_t_into_float(temperatures_4, temperatures_4_minValue, temperatures_4_maxValue);
  }
  float MAX31850KColdJunctionData_Msg::get_temperatures_5() {
    return unpack_uint8_t_into_float(temperatures_5, temperatures_5_minValue, temperatures_5_maxValue);
  }
  float MAX31850KColdJunctionData_Msg::get_temperatures_6() {
    return unpack_uint8_t_into_float(temperatures_6, temperatures_6_minValue, temperatures_6_maxValue);
  }
  float MAX31850KColdJunctionData_Msg::get_temperatures_7() {
    return unpack_uint8_t_into_float(temperatures_7, temperatures_7_minValue, temperatures_7_maxValue);
  }

  const float MAX31850KColdJunctionData_Msg::temperatures_0_minValue = -40.00000000;
  const float MAX31850KColdJunctionData_Msg::temperatures_0_maxValue = 125.00000000;
  const float MAX31850KColdJunctionData_Msg::temperatures_1_minValue = -40.00000000;
  const float MAX31850KColdJunctionData_Msg::temperatures_1_maxValue = 125.00000000;
  const float MAX31850KColdJunctionData_Msg::temperatures_2_minValue = -40.00000000;
  const float MAX31850KColdJunctionData_Msg::temperatures_2_maxValue = 125.00000000;
  const float MAX31850KColdJunctionData_Msg::temperatures_3_minValue = -40.00000000;
  const float MAX31850KColdJunctionData_Msg::temperatures_3_maxValue = 125.00000000;
  const float MAX31850KColdJunctionData_Msg::temperatures_4_minValue = -40.00000000;
  const float MAX31850KColdJunctionData_Msg::temperatures_4_maxValue = 125.00000000;
  const float MAX31850KColdJunctionData_Msg::temperatures_5_minValue = -40.00000000;
  const float MAX31850KColdJunctionData_Msg::temperatures_5_maxValue = 125.00000000;
  const float MAX31850KColdJunctionData_Msg::temperatures_6_minValue = -40.00000000;
  const float MAX31850KColdJunctionData_Msg::temperatures_6_maxValue = 125.00000000;
  const float MAX31850KColdJunctionData_Msg::temperatures_7_minValue = -40.00000000;
  const float MAX31850KColdJunctionData_Msg::temperatures_7_maxValue = 125.00000000;

  static_assert((sizeof(MAX31850KColdJunctionData_Msg) <= 8), "sizeof(MAX31850KColdJunctionData_Msg) must be less than 8 bytes!");
  
}