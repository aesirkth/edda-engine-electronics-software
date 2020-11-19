// Codegen file. Do not edit manually!

#ifndef EDDA_MESSAGES_TIMESYNCTIMERESPONSE_H
#define EDDA_MESSAGES_TIMESYNCTIMERESPONSE_H

#include <stdint.h>
#include <limits.h>
#include <string.h>
#include "../enums.h"
#include "../packers.h"

namespace EddaCAN {
  class alignas(8) TimeSyncTimeResponse_DataType {
    private:
      uint8_t destination __attribute__((packed));
      uint8_t requestIdentifier __attribute__((packed));
      uint32_t bits0through31 __attribute__((packed));
      uint16_t bits32through47 __attribute__((packed));

    public:

      void set_destination(uint8_t value);
      void set_requestIdentifier(uint8_t value);
      void set_bits0through31(uint32_t value);
      void set_bits32through47(uint16_t value);

      uint8_t get_destination();
      uint8_t get_requestIdentifier();
      uint32_t get_bits0through31();
      uint16_t get_bits32through47();

  };
  
}

#endif