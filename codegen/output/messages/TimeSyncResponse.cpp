// Codegen file. Do not edit manually!

#include <stdint.h>;
#include <limits.h>;
#include <string.h>;
#include "../enums.h";
#include "../packers.h";
#include "TimeSyncResponse.h";

namespace EddaCAN {
  void TimeSyncResponse_Msg::set_destination(uint8_t value) {
    destination = value;
  }
  void TimeSyncResponse_Msg::set_requestIdentifier(uint16_t value) {
    requestIdentifier = value;
  }
  void TimeSyncResponse_Msg::set_initiatedAtMicros(uint32_t value) {
    initiatedAtMicros = value;
  }

  uint8_t TimeSyncResponse_Msg::get_destination() {
    return destination;
  }
  uint16_t TimeSyncResponse_Msg::get_requestIdentifier() {
    return requestIdentifier;
  }
  uint32_t TimeSyncResponse_Msg::get_initiatedAtMicros() {
    return initiatedAtMicros;
  }

  static_assert((sizeof(TimeSyncResponse_Msg) <= 8), "sizeof(TimeSyncResponse_Msg) must be less than 8 bytes!");
  
}