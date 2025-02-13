#include <Arduino.h>

extern "C" int sum_array(int *arr);

void setup() {
    Serial.begin(9600);
}

void loop() {
    int myArray[5] = {1, 2, 3, 4, 5};
    int result = sum_array(myArray);

    Serial.print("Sum: ");
    Serial.println(result);
    delay(1000);
}