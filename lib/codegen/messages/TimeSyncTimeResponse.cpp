// Codegen file. Do not edit manually!

#include <stdint.h>
#include <limits.h>
#include <string.h>
#include "../enums.h"
#include "../packers.h"
#include "TimeSyncTimeResponse.h"

namespace EddaCAN {
  void TimeSyncTimeResponse_DataType::set_destination(uint8_t value) {
    destination = value;
  }
  void TimeSyncTimeResponse_DataType::set_requestIdentifier(uint8_t value) {
    requestIdentifier = value;
  }
  void TimeSyncTimeResponse_DataType::set_bits0through31(uint32_t value) {
    bits0through31 = value;
  }
  void TimeSyncTimeResponse_DataType::set_bits32through47(uint16_t value) {
    bits32through47 = value;
  }

  uint8_t TimeSyncTimeResponse_DataType::get_destination() {
    return destination;
  }
  uint8_t TimeSyncTimeResponse_DataType::get_requestIdentifier() {
    return requestIdentifier;
  }
  uint32_t TimeSyncTimeResponse_DataType::get_bits0through31() {
    return bits0through31;
  }
  uint16_t TimeSyncTimeResponse_DataType::get_bits32through47() {
    return bits32through47;
  }

  static_assert((sizeof(TimeSyncTimeResponse_DataType) <= 8), "sizeof(TimeSyncTimeResponse_DataType) must be less than 8 bytes!");
  
}