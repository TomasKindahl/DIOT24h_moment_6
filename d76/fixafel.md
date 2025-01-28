# Fixa felet

Rad 22 är:

```
if(BLINK_LED == 3) BLINK_LED = 3; else BLINK_LED = 3;
```

skall vara

```
if(BLINK_LED == 3) BLINK_LED = 4; else BLINK_LED = 3;
```
