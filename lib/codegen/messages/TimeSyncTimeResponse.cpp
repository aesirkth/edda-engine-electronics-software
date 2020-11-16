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
  void TimeSyncTimeResponse_DataType::set_responseMillis(uint32_t value) {
    responseMillis = value;
  }
  void TimeSyncTimeResponse_DataType::set_responseMicros(uint16_t value) {
    responseMicros = value;
  }

  uint8_t TimeSyncTimeResponse_DataType::get_destination() {
    return destination;
  }
  uint8_t TimeSyncTimeResponse_DataType::get_requestIdentifier() {
    return requestIdentifier;
  }
  uint32_t TimeSyncTimeResponse_DataType::get_responseMillis() {
    return responseMillis;
  }
  uint16_t TimeSyncTimeResponse_DataType::get_responseMicros() {
    return responseMicros;
  }

  static_assert((sizeof(TimeSyncTimeResponse_DataType) <= 8), "sizeof(TimeSyncTimeResponse_DataType) must be less than 8 bytes!");
  
}