#include <Arduino.h>

extern "C" int add_numbers(int a, int b);
extern "C" int mul_numbers(int a, int b);

void setup() {
    Serial.begin(9600);
}

void loop() {
    for (size_t i = 0; i < 10; i++)
    {
      for(size_t j = 0; j < 10; j++)
      {
        Serial.print(i);
        Serial.print(" + ");
        Serial.print(j);
        Serial.print(" = ");
        Serial.print(add_numbers(i, j));
        Serial.print(" ; ");
        Serial.print(i);
        Serial.print(" * ");
        Serial.print(j);
        Serial.print(" = ");
        Serial.println(mul_numbers(i, j));
      }
    }
    delay(1000);
}
