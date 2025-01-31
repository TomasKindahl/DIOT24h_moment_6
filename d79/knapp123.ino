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

#define STATE_S1 0
#define STATE_S2 1
#define STATE_S3 2
#define INGEN_KNAPP 0
#define KNAPP_k1 1
#define KNAPP_k2 2

int BUTTON1 = 2;
int BUTTON2 = 3;
int button1_bounces = 0;
int button2_bounces = 0;

int state;

void button1Pressed() { button1_bounces ++; }
void button2Pressed() { button2_bounces ++; }

void setup() {
    state = STATE_S1; 
    attachInterrupt(digitalPinToInterrupt(BUTTON1), button1Pressed, FALLING);
    attachInterrupt(digitalPinToInterrupt(BUTTON2), button2Pressed, FALLING);
    matrix.begin();
    Serial.begin(9600);
}

int i = 0;

void loop() {
    int knapp = INGEN_KNAPP;
    if(button1_bounces > 0) {
        button1_bounces = 0;
        knapp = KNAPP_k1;
    }
    if(button2_bounces > 0) {
        button2_bounces = 0;
        knapp = KNAPP_k2;
    }

    if(state == STATE_S1) {
        matrix.loadFrame(digit[0]);
        if(knapp == KNAPP_k1) {
            state = STATE_S2;
        }
        else if(knapp == KNAPP_k2) {
            // Inget!
        }
    }
    else if(state == STATE_S2) {
        matrix.loadFrame(digit[1]);
        if(knapp == KNAPP_k1) {
            state = STATE_S3;
        }
        else if(knapp == KNAPP_k2) {
            state = STATE_S1;
        }
    }
    else if(state == STATE_S3) {
        matrix.loadFrame(digit[2]);
        if(knapp == KNAPP_k1) {
            // Inget!
        }
        else if(knapp == KNAPP_k2) {
            state = STATE_S2;
        }
    }
    delay(200);
}
