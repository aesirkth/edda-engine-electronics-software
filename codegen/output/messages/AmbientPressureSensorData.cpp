// Codegen file. Do not edit manually!

#include <stdint.h>;
#include <limits.h>;
#include <string.h>;
#include "../enums.h";
#include "../packers.h";
#include "AmbientPressureSensorData.h";

namespace EddaCAN {
  void AmbientPressureSensorData_Msg::set_pressure(float value) {
    pressure = pack_float_into_uint32_t(value, pressure_minValue, pressure_maxValue);
  }
  void AmbientPressureSensorData_Msg::set_temperature(float value) {
    temperature = pack_float_into_uint16_t(value, temperature_minValue, temperature_maxValue);
  }

  float AmbientPressureSensorData_Msg::get_pressure() {
    return unpack_uint32_t_into_float(pressure, pressure_minValue, pressure_maxValue);
  }
  float AmbientPressureSensorData_Msg::get_temperature() {
    return unpack_uint16_t_into_float(temperature, temperature_minValue, temperature_maxValue);
  }

  const float AmbientPressureSensorData_Msg::pressure_minValue = 0.00000000;
  const float AmbientPressureSensorData_Msg::pressure_maxValue = 5000000.00000000;
  const float AmbientPressureSensorData_Msg::temperature_minValue = -40.00000000;
  const float AmbientPressureSensorData_Msg::temperature_maxValue = 85.00000000;

  static_assert((sizeof(AmbientPressureSensorData_Msg) <= 8), "sizeof(AmbientPressureSensorData_Msg) must be less than 8 bytes!");
  
}