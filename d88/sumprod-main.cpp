#include <Arduino.h>

extern "C" int sum_array(int *arr);
extern "C" int prod_array(int *arr);

void setup() {
    Serial.begin(9600);
}

void loop() {
    int myArray[5] = {1, 2, 3, 4, 5};
    int sum = sum_array(myArray);
    int prod = prod_array(myArray);

    Serial.print("Sum: ");
    Serial.println(sum);
    Serial.print("Prod: ");
    Serial.println(prod);
    delay(1000);
}
