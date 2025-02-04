#include <Arduino.h>
#include <Arduino_FreeRTOS.h>
#include "DHT_Async.h"

/* Uncomment according to your sensortype. */
#define DHT_SENSOR_TYPE DHT_TYPE_11
//#define DHT_SENSOR_TYPE DHT_TYPE_21
//#define DHT_SENSOR_TYPE DHT_TYPE_22

static const int DHT_SENSOR_PIN = 10;
DHT_Async dht_sensor(DHT_SENSOR_PIN, DHT_SENSOR_TYPE);

TaskHandle_t loop_task, DHT_task;

void setup() {
    Serial.begin(115200);
    while (!Serial) { }

    auto const rc_loop = xTaskCreate
      (
        loop_thread_func,
        static_cast<const char*>("Loop Thread"),
        512 / 4,   /* usStackDepth in words */
        nullptr,   /* pvParameters */
        1,         /* uxPriority */
        &loop_task /* pxCreatedTask */
      );
    if (rc_loop != pdPASS) {
        Serial.println("Failed to create 'loop' thread");
        return;
    }
    Serial.println("Created 'loop' thread");

    auto const rc_DHT = xTaskCreate
      (
        DHT_thread_func,
        static_cast<const char*>("DHT Thread"),
        512 / 4,   /* usStackDepth in words */
        nullptr,   /* pvParameters */
        1,         /* uxPriority */
        &DHT_task /* pxCreatedTask */
      );
    if (rc_DHT != pdPASS) {
        Serial.println("Failed to create 'loop' thread");
        return;
    }
    Serial.println("Created 'DHT' thread");

    Serial.println("Starting scheduler ...");
    /* Start the scheduler. */
    vTaskStartScheduler();
    /* We'll never get here. */
    for( ;; );
}

float temperature;
float humidity;

void loop() {
}

void loop_thread_func(void *pvParameters) {
    Serial.println("loop_thread_func started");
    vTaskDelay(configTICK_RATE_HZ*1);
    for(;;) {
        Serial.print("T = ");
        Serial.print(temperature, 1);
        Serial.print("°C, H = ");
        Serial.print(humidity, 1);
        Serial.println("%");
        vTaskDelay(configTICK_RATE_HZ*4);
    }
}

void DHT_thread_func(void *pvParameters) {
    Serial.println("DHT_thread_func started");

    for(;;) {
        dht_sensor.measure(&temperature, &humidity);
        vTaskDelay(configTICK_RATE_HZ*4);
    }
}