# Hur tänker man?

På [figuren](https://docs.arduino.cc/resources/pinouts/ABX00087-full-pinout.pdf) ser vi att LED_BUILTIN är P102 samtidigt som koden är

```
#define LED_PORT_NUM 1
#define LED_PIN_NUM 2
```

Om vi nu vill byta till GPIO 8 så står den markerad som P304. 
Förslagsvis ändra koden till

```
#define LED_PORT_NUM 3
#define LED_PIN_NUM 4
```

