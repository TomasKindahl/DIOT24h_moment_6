#include <Arduino_FreeRTOS.h>

struct blinker {
    int pin;
    int freq;
    TaskHandle_t thandle;
    BaseType_t rc_task;
};

blinker task[2] = {
    {3, 5},
    {4, 7}
};

void setup()
{
  Serial.begin(115200);
  while (!Serial) { }

  for(int i = 0; i < 2; i++) {
    task[i].rc_task = xTaskCreate
      (
        blinky_thread_func,
        static_cast<const char*>("LED blink"),
        512 / 4,         /* usStackDepth in words */
        (void *)&task[i],  /* pvParameters */
        1,               /* uxPriority */
        &task[i].thandle  /* pxCreatedTask */
    );

    if (task[i].rc_task != pdPASS) {
      Serial.println("Failed to create 'loop' thread");
      return;
    }
  }


  Serial.println("Starting scheduler ...");
  vTaskStartScheduler();
}

void loop()
{
  // Ole dole doff!
}

void blinky_thread_func(void *pvParameters)
{
  /* setup() */
  blinker *blink = (struct blinker *)pvParameters;
  pinMode(blink->pin, OUTPUT);
  digitalWrite(blink->pin, LOW);

  /* loop() */
  for(;;)
  {
    digitalWrite(blink->pin, !digitalRead(blink->pin));
    vTaskDelay(configTICK_RATE_HZ/blink->freq);
  }
}
