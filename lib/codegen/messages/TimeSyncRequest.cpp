// Codegen file. Do not edit manually!

#include <stdint.h>
#include <limits.h>
#include <string.h>
#include "../enums.h"
#include "../packers.h"
#include "TimeSyncRequest.h"

namespace EddaCAN {
  void TimeSyncRequest_DataType::set_source(uint8_t value) {
    source = value;
  }
  void TimeSyncRequest_DataType::set_requestIdentifier(uint8_t value) {
    requestIdentifier = value;
  }
  void TimeSyncRequest_DataType::set_currentMicros(uint32_t value) {
    currentMicros = value;
  }

  uint8_t TimeSyncRequest_DataType::get_source() {
    return source;
  }
  uint8_t TimeSyncRequest_DataType::get_requestIdentifier() {
    return requestIdentifier;
  }
  uint32_t TimeSyncRequest_DataType::get_currentMicros() {
    return currentMicros;
  }

  static_assert((sizeof(TimeSyncRequest_DataType) <= 8), "sizeof(TimeSyncRequest_DataType) must be less than 8 bytes!");
  
}