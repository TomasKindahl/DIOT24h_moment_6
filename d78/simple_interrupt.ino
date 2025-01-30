#define DO_NOTHING   0
#define DO_SOMETHING 1

int BUTTON = 2;
int button_bounces = 0;
int activity = 1;

void buttonPressed() {
    button_bounces ++;
    // delay(100); - inte bra!
}

void setup() {
    button_bounces = 0;
    activity = DO_NOTHING;
    attachInterrupt(digitalPinToInterrupt(BUTTON), buttonPressed, FALLING);
    Serial.begin(9600);
}

void loop() {
    if(button_bounces > 0)
        Serial.println("BUTTON WAS PRESSED");
    if(activity == DO_SOMETHING) {
        if(button_bounces > 0) {
            activity = DO_NOTHING;
            Serial.println("BUTTON WAS PRESSED");
            button_bounces = 0;
        }
    }
    else {
        if(button_bounces > 0) {
            activity = DO_SOMETHING;
            button_bounces = 0;
        }
    }
    if(activity == DO_SOMETHING)
        Serial.println("DO SOMETHING");
    else
        Serial.println("DO NOTHING");
    delay(200);
}
