#define BLINK_OFF 0
#define BLINK_ON  1

int BLINK_LED;
int BLINK_MODE;
int button_bounces = 0;

void buttonPressed() {
    button_bounces ++;
}

void setup() {
    BLINK_LED = 3;
    BLINK_MODE = BLINK_OFF;
    pinMode(3, OUTPUT);
    pinMode(4, OUTPUT);
    attachInterrupt(digitalPinToInterrupt(2), buttonPressed, FALLING);
}

void loop() {
    if(button_bounces > 0) {
        if(BLINK_MODE == BLINK_OFF) {
            BLINK_MODE = BLINK_ON;
        }
        else {
            if(BLINK_LED == 3) BLINK_LED = 4; else BLINK_LED = 3;
            BLINK_MODE = BLINK_OFF;
        }
        button_bounces = 0;
    }
    if(BLINK_MODE == BLINK_ON) {
        digitalWrite(BLINK_LED, HIGH);
        delay(200);
        digitalWrite(BLINK_LED, LOW);
        delay(200);
    }
    else {
        delay(400);
    }
}
