#include "printNonNativeTypes.h"

void printUint64(uint64_t num) {
  uint8_t digits[100];
  int nDigits = 0;

  while(num > 0 && nDigits < 100) {
    int val = (int)(num % 10);
    num /= 10;

    digits[nDigits++] = val;
  }

  for(int n = 0; n < nDigits; n++) {
    Serial.print(digits[nDigits - n - 1], DEC);
  }
  if(nDigits == 0) {
    Serial.print(0, DEC);
  }
}

void printInt64(int64_t num) {
  if(num < 0) {
    Serial.print("-");
    printUint64((uint64_t)(-num));
  } else {
    printUint64((uint64_t)num);
  }
}