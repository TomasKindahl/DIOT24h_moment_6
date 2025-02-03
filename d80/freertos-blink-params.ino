#include <Arduino_FreeRTOS.h>

struct blinker {
    int pin;
    int freq;
    TaskHandle_t thandle;
    BaseType_t rc_task;
};

blinker task_1 = {3, 5}, task_2 = {4, 7};

void setup()
{
  Serial.begin(115200);
  while (!Serial) { }

  task_1.rc_task = xTaskCreate
    (
      blinky_thread_func,
      static_cast<const char*>("LED blink"),
      512 / 4,         /* usStackDepth in words */
      (void *)&task_1,  /* pvParameters */
      1,               /* uxPriority */
      &task_1.thandle  /* pxCreatedTask */
    );

  if (task_1.rc_task != pdPASS) {
    Serial.println("Failed to create 'loop' thread");
    return;
  }

  task_2.rc_task = xTaskCreate
    (
      blinky_thread_func,
      static_cast<const char*>("LED blink"),
      512 / 4,         /* usStackDepth in words */
      (void *)&task_2,  /* pvParameters */
      1,               /* uxPriority */
      &task_2.thandle  /* pxCreatedTask */
    );

  if (task_2.rc_task != pdPASS) {
    Serial.println("Failed to create 'loop' thread");
    return;
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
