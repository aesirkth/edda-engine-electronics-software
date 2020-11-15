// Codegen file. Do not edit manually!

#include <stdint.h>;
#include <limits.h>;
#include <string.h>;
#include "../enums.h";
#include "../packers.h";
#include "SetDebugModeRequest.h";

namespace EddaCAN {
  void SetDebugModeRequest_Msg::set_mode(PowerMode value) {
    mode = value;
  }

  PowerMode SetDebugModeRequest_Msg::get_mode() {
    return mode;
  }

  static_assert((sizeof(SetDebugModeRequest_Msg) <= 8), "sizeof(SetDebugModeRequest_Msg) must be less than 8 bytes!");
  
}