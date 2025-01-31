#define STATE_S1 0
#define STATE_S2 1
#define STATE_S3 2
#define INGEN_KNAPP 0
#define KNAPP_k1 1
#define KNAPP_k2 2

int state;

setup() {
    state = STATE_S1;
    // ... ANNAT ...
}

loop() {
    int knapp = INGEN_KNAPP;
    // ... beräkna knapp här ...
    if(state == STATE_S1) {
        if(knapp == KNAPP_k1) {
            state = STATE_S2;
        }
        else if(knapp == KNAPP_k2) {
            // Inget!
        }
    }
    else if(state == STATE_S2) {
        if(knapp == KNAPP_k1) {
            state = STATE_S3;
        }
        else if(knapp == KNAPP_k2) {
            state = STATE_S1;
        }
    }
    else if(state == STATE_S3) {
        if(knapp == KNAPP_k1) {
            // Inget!
        }
        else if(knapp == KNAPP_k2) {
            state = STATE_S2;
        }
    }
}