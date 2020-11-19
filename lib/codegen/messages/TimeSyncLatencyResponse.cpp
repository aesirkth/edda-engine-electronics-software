// Codegen file. Do not edit manually!

#include <stdint.h>
#include <limits.h>
#include <string.h>
#include "../enums.h"
#include "../packers.h"
#include "TimeSyncLatencyResponse.h"

namespace EddaCAN {
  void TimeSyncLatencyResponse_DataType::set_destination(uint8_t value) {
    destination = value;
  }
  void TimeSyncLatencyResponse_DataType::set_requestIdentifier(uint8_t value) {
    requestIdentifier = value;
  }
  void TimeSyncLatencyResponse_DataType::set_initiatorMicros(uint32_t value) {
    initiatorMicros = value;
  }

  uint8_t TimeSyncLatencyResponse_DataType::get_destination() {
    return destination;
  }
  uint8_t TimeSyncLatencyResponse_DataType::get_requestIdentifier() {
    return requestIdentifier;
  }
  uint32_t TimeSyncLatencyResponse_DataType::get_initiatorMicros() {
    return initiatorMicros;
  }

  static_assert((sizeof(TimeSyncLatencyResponse_DataType) <= 8), "sizeof(TimeSyncLatencyResponse_DataType) must be less than 8 bytes!");
  
}