#include "Arduino_LED_Matrix.h"

ArduinoLEDMatrix matrix;

uint32_t digit[6][3] = {
/*1*/ { 0b00000000000000000000001000000000, 0b00100111111111100010000000100001, 0b00000010000000000000000000000000 },
/*2*/ { 0b00000000000000110000001001001100, 0b00100100001100100100000011100011, 0b00000010000000000000000000000000 },
/*3*/ { 0b00000000000000111001110001000110, 0b00100100011000100100000000100010, 0b00001100000000000000000000000000 },
/*4*/ { 0b00000100000000000100001001111111, 0b11100010010000100001010000000000, 0b11000000000001000000000000000000 },
/*5*/ { 0b00000000000001100011110001000100, 0b00100100010000100100010000100111, 0b11100100000000000000000000000000 },
/*6*/ { 0b00000000000000100011110001000100, 0b00100100010000100100010000100011, 0b11111100000000000000000000000000 },
};

int BUTTON = 2;
int button_bounces = 0;
int rollMode = 1;

void buttonPressed() {
    button_bounces ++;
    // delay(100); - inte bra!
}

void setup() {
    attachInterrupt(digitalPinToInterrupt(BUTTON), buttonPressed, FALLING);
    matrix.begin();
}

int i = 0;

void loop() {
    if(rollMode) {
        matrix.loadFrame(digit[i]);
        if(button_bounces > 0) {
            rollMode = 0;
            button_bounces = 0;
        }
        i++;
        if(i == 6) i = 0;
    }
    else {
        if(button_bounces > 0) {
            rollMode = 1;
            button_bounces = 0;
        }
    }
    delay(100);
}
