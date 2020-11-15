// Codegen file. Do not edit manually!

#include <stdint.h>;
#include <limits.h>;
#include <string.h>;
#include "../enums.h";
#include "../packers.h";
#include "SetPowerModeRequest.h";

namespace EddaCAN {
  void SetPowerModeRequest_Msg::set_mode(DebugMode value) {
    mode = value;
  }

  DebugMode SetPowerModeRequest_Msg::get_mode() {
    return mode;
  }

  static_assert((sizeof(SetPowerModeRequest_Msg) <= 8), "sizeof(SetPowerModeRequest_Msg) must be less than 8 bytes!");
  
}