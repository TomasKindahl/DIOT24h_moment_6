#include <Arduino_FreeRTOS.h>

TaskHandle_t blink_1, blink_2;

void setup()
{
  Serial.begin(115200);
  while (!Serial) { }

  const BaseType_t rc_blink_1 = xTaskCreate
    (
      blinky_thread_func,
      static_cast<const char*>("LED1 blink"),
      512 / 4,    /* usStackDepth in words */
      (void *)3,  /* pvParameters */
      1,          /* uxPriority */
      &blink_1    /* pxCreatedTask */
    );

  if (rc_blink_1 != pdPASS) {
    Serial.println("Failed to create 'loop' thread");
    return;
  }

  const BaseType_t rc_blink_2 = xTaskCreate
    (
      blinky_thread_func,
      static_cast<const char*>("LED2 blink"),
      512 / 4,    /* usStackDepth in words */
      (void *)4,  /* pvParameters */
      1,          /* uxPriority */
      &blink_2    /* pxCreatedTask */
    );

  if (rc_blink_2 != pdPASS) {
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
  int PIN = (int)pvParameters;
  pinMode(PIN, OUTPUT);
  digitalWrite(PIN, LOW);
  int freq;
  if (PIN == 3) freq = 3; else freq = 5;

  /* loop() */
  for(;;)
  {
    digitalWrite(PIN, !digitalRead(PIN));
    vTaskDelay(configTICK_RATE_HZ/freq);
  }
}
