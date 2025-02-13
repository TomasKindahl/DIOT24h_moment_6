#include <Arduino.h>

void setup() {
  Serial.begin(9600);
}

uint32_t a = 0, b = 0;

void loop() {
  uint32_t result;

  for(uint32_t a = 0; a < 10; a++) {
    for(uint32_t b = 0; b < 10; b++) {
      __asm__ volatile (
        "add %0, %1, %2"   // result = a + b
        : "=r" (result)     // Output operand
        : "r" (a), "r" (b)   // Input operands
      );
      Serial.print("Result: ");
      Serial.println(result);
    }
  }


  delay(1000);
}
