// Codegen file. Do not edit manually!

#include <stdint.h>;
#include <limits.h>;
#include <string.h>;
#include "../enums.h";
#include "../packers.h";
#include "SetPowerModeRequest.h";

namespace EddaCAN {
  void SetPowerModeRequest_DataType::set_mode(PowerMode value) {
    mode = value;
  }

  PowerMode SetPowerModeRequest_DataType::get_mode() {
    return mode;
  }

  static_assert((sizeof(SetPowerModeRequest_DataType) <= 8), "sizeof(SetPowerModeRequest_DataType) must be less than 8 bytes!");
  
}