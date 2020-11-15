// Codegen file. Do not edit manually!

#ifndef EDDA_MESSAGES_TIMESYNCRESPONSE_H
#define EDDA_MESSAGES_TIMESYNCRESPONSE_H

#include <stdint.h>;
#include <limits.h>;
#include <string.h>;
#include "../enums.h";
#include "../packers.h";

namespace EddaCAN {
  class alignas(8) TimeSyncResponse_Msg {
    private:
      uint8_t destination;
      uint16_t requestIdentifier;
      uint32_t initiatedAtMicros;

    public:

      void set_destination(uint8_t value);
      void set_requestIdentifier(uint16_t value);
      void set_initiatedAtMicros(uint32_t value);

      uint8_t get_destination();
      uint16_t get_requestIdentifier();
      uint32_t get_initiatedAtMicros();

  };
  
}

#endif