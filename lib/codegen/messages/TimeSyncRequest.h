// Codegen file. Do not edit manually!

#ifndef EDDA_MESSAGES_TIMESYNCREQUEST_H
#define EDDA_MESSAGES_TIMESYNCREQUEST_H

#include <stdint.h>
#include <limits.h>
#include <string.h>
#include "../enums.h"
#include "../packers.h"

namespace EddaCAN {
  class alignas(8) TimeSyncRequest_DataType {
    private:
      uint8_t source __attribute__((packed));
      uint8_t requestIdentifier __attribute__((packed));
      uint32_t currentMicros __attribute__((packed));

    public:

      void set_source(uint8_t value);
      void set_requestIdentifier(uint8_t value);
      void set_currentMicros(uint32_t value);

      uint8_t get_source();
      uint8_t get_requestIdentifier();
      uint32_t get_currentMicros();

  };
  
}

#endif