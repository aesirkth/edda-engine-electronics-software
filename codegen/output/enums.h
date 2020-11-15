// Codegen file. Do not edit manually!

#ifndef EDDA_ENUMS_H
#define EDDA_ENUMS_H

#include <stdint.h>;

namespace EddaCAN {
  enum struct PowerMode: uint8_t {
    Idle = 0,
    HighPower = 1,
    LowPower = 2,
    MediumPower = 3,
    Hibernation = 4,
  };

  enum struct DebugMode: uint8_t {
    Enabled = 0,
    Disabled = 1,
  };
}

#endif