long randNumber;

void setup() {
    pinMode(13, OUTPUT);
    Serial.begin(9600);
    randomSeed(analogRead(0));
}

int myexp2(int num) {
    int res = 1;
    while(num > 0) {
        res = res << 2;
        num--;
    }
    return res;
}

void loop() {
    randNumber = myexp2(random(2, 10));
    Serial.println(randNumber);
    digitalWrite(13, HIGH);
    delay(randNumber);

    randNumber = myexp2(random(2, 10));
    Serial.println(randNumber);
    digitalWrite(13, LOW);
    delay(randNumber);
}

