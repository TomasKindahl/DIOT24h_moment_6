#define BLINK_OFF 0
#define BLINK_ON  1

int BLINK_LED;
int BLINK_MODE;

void setup() {
    BLINK_LED = 3;
    BLINK_MODE = BLINK_OFF;
    pinMode(3, OUTPUT);
    pinMode(4, OUTPUT);
    pinMode(7, INPUT_PULLUP);
}

// the loop function runs over and over again forever
void loop() {
    if(digitalRead(7) != HIGH) {
        if(BLINK_MODE == BLINK_OFF) {
            BLINK_MODE = BLINK_ON;
        }
        else {
            if(BLINK_LED == 3) BLINK_LED = 3; else BLINK_LED = 3;
            BLINK_MODE = BLINK_OFF;
        }
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
