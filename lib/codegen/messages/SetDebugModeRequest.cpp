// Codegen file. Do not edit manually!

#include <stdint.h>
#include <limits.h>
#include <string.h>
#include "../enums.h"
#include "../packers.h"
#include "SetDebugModeRequest.h"

namespace EddaCAN {
  void SetDebugModeRequest_DataType::set_mode(DebugMode value) {
    mode = value;
  }

  DebugMode SetDebugModeRequest_DataType::get_mode() {
    return mode;
  }

  static_assert((sizeof(SetDebugModeRequest_DataType) <= 8), "sizeof(SetDebugModeRequest_DataType) must be less than 8 bytes!");
  
}