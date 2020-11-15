// Codegen file. Do not edit manually!

#include <stdint.h>;
#include <limits.h>;
#include <string.h>;
#include "../enums.h";
#include "../packers.h";
#include "TimeSyncResponse.h";

namespace EddaCAN {
  void TimeSyncResponse_DataType::set_destination(uint8_t value) {
    destination = value;
  }
  void TimeSyncResponse_DataType::set_requestIdentifier(uint16_t value) {
    requestIdentifier = value;
  }
  void TimeSyncResponse_DataType::set_initiatedAtMicros(uint32_t value) {
    initiatedAtMicros = value;
  }

  uint8_t TimeSyncResponse_DataType::get_destination() {
    return destination;
  }
  uint16_t TimeSyncResponse_DataType::get_requestIdentifier() {
    return requestIdentifier;
  }
  uint32_t TimeSyncResponse_DataType::get_initiatedAtMicros() {
    return initiatedAtMicros;
  }

  static_assert((sizeof(TimeSyncResponse_DataType) <= 8), "sizeof(TimeSyncResponse_DataType) must be less than 8 bytes!");
  
}