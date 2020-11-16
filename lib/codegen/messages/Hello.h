// Codegen file. Do not edit manually!

#ifndef EDDA_MESSAGES_HELLO_H
#define EDDA_MESSAGES_HELLO_H

#include <stdint.h>
#include <limits.h>
#include <string.h>
#include "../enums.h"
#include "../packers.h"

namespace EddaCAN {
  class alignas(8) Hello_DataType {
    private:
      uint8_t source __attribute__((packed));
      PowerMode powerMode __attribute__((packed));
      DebugMode debugMode __attribute__((packed));

    public:

      void set_source(uint8_t value);
      void set_powerMode(PowerMode value);
      void set_debugMode(DebugMode value);

      uint8_t get_source();
      PowerMode get_powerMode();
      DebugMode get_debugMode();

  };
  
}

#endif