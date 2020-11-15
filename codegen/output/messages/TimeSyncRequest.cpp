// Codegen file. Do not edit manually!

#include <stdint.h>;
#include <limits.h>;
#include <string.h>;
#include "../enums.h";
#include "../packers.h";
#include "TimeSyncRequest.h";

namespace EddaCAN {
  void TimeSyncRequest_Msg::set_source(uint8_t value) {
    source = value;
  }
  void TimeSyncRequest_Msg::set_requestIdentifier(uint16_t value) {
    requestIdentifier = value;
  }
  void TimeSyncRequest_Msg::set_initiatedAtMicros(uint32_t value) {
    initiatedAtMicros = value;
  }

  uint8_t TimeSyncRequest_Msg::get_source() {
    return source;
  }
  uint16_t TimeSyncRequest_Msg::get_requestIdentifier() {
    return requestIdentifier;
  }
  uint32_t TimeSyncRequest_Msg::get_initiatedAtMicros() {
    return initiatedAtMicros;
  }

  static_assert((sizeof(TimeSyncRequest_Msg) <= 8), "sizeof(TimeSyncRequest_Msg) must be less than 8 bytes!");
  
}