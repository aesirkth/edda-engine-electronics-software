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
      uint32_t initiatedAtMillis __attribute__((packed));
      uint16_t initiatedAtMicros __attribute__((packed));

    public:

      void set_source(uint8_t value);
      void set_requestIdentifier(uint8_t value);
      void set_initiatedAtMillis(uint32_t value);
      void set_initiatedAtMicros(uint16_t value);

      uint8_t get_source();
      uint8_t get_requestIdentifier();
      uint32_t get_initiatedAtMillis();
      uint16_t get_initiatedAtMicros();

  };
  
}

#endif