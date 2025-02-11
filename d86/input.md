# Hintar

## pinMode(BUTTON_PIN, INPUT)

Om

```C
R_PFS->PORT[LED_PORT_NUM].PIN[LED_PIN_NUM].PmnPFS_b.PDR = 1;
```

är `// "Output"`, så vore det väl en bra chansning att


```C
R_PFS->PORT[BUTTON_PORT_NUM].PIN[BUTTON_PIN_NUM].PmnPFS_b.PDR = 0;
```

är input. Det andra begriper vi knappt något av, så det rör vi inte!

## digitalRead(BUTTON_PIN)

Om du sladdat som står i övningen så funkar det följande:




Om vi nu vill byta till GPIO 8 så står den markerad som P304. 
Förslagsvis ändra koden till

```C
if(R_PFS->PORT[BUTTON_PORT_NUM].PIN[BUTTON_PIN_NUM].PmnPFS_b.PIDR == 0) {
    // DO SOMETHING!!
}
```

