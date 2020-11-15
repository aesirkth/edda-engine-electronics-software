// Codegen file. Do not edit manually!

#include <stdint.h>;
#include <limits.h>;
#include <string.h>;
#include "../enums.h";
#include "../packers.h";
#include "Hello.h";

namespace EddaCAN {
  void Hello_DataType::set_source(uint8_t value) {
    source = value;
  }
  void Hello_DataType::set_powerMode(PowerMode value) {
    powerMode = value;
  }
  void Hello_DataType::set_debugMode(DebugMode value) {
    debugMode = value;
  }

  uint8_t Hello_DataType::get_source() {
    return source;
  }
  PowerMode Hello_DataType::get_powerMode() {
    return powerMode;
  }
  DebugMode Hello_DataType::get_debugMode() {
    return debugMode;
  }

  static_assert((sizeof(Hello_DataType) <= 8), "sizeof(Hello_DataType) must be less than 8 bytes!");
  
}