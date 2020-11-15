// Codegen file. Do not edit manually!

#ifndef EDDA_MESSAGES_SETDEBUGMODEREQUEST_H
#define EDDA_MESSAGES_SETDEBUGMODEREQUEST_H

#include <stdint.h>;
#include <limits.h>;
#include <string.h>;
#include "../enums.h";
#include "../packers.h";

namespace EddaCAN {
  class alignas(8) SetDebugModeRequest_DataType {
    private:
      DebugMode mode;

    public:

      void set_mode(DebugMode value);

      DebugMode get_mode();

  };
  
}

#endif