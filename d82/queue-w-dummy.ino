// #include <Arduino.h>
#define configUSE_QUEUES 1
#include <Arduino_FreeRTOS.h>
#include <FreeRTOSConfig.h>

#include "DHT_Async.h"

/* Uncomment according to your sensortype. */
#define DHT_SENSOR_TYPE DHT_TYPE_11
//#define DHT_SENSOR_TYPE DHT_TYPE_21
//#define DHT_SENSOR_TYPE DHT_TYPE_22

static const int DHT_SENSOR_PIN = 10;
DHT_Async dht_sensor(DHT_SENSOR_PIN, DHT_SENSOR_TYPE);

TaskHandle_t loop_task, DHT_task;
QueueHandle_t queue = NULL;

struct _climate_S {
    float temp, humid;
};

void setup() {
    Serial.begin(115200);
    while (!Serial) { }

    Serial.println("==== START ====");
    queue = xQueueCreate( 5, sizeof(struct _climate_S) );

    if( queue == NULL ) {
        Serial.println("failed to create queue");
    }
    else {
        Serial.println("mutex queue");
    }

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

void loop() { 
    // Sim sala bim
}

void loop_thread_func(void *pvParameters) {
    struct _climate_S climate;
    Serial.println("loop_thread_func started");

    for(;;) {
        while(xQueueReceive(queue, &climate, (TickType_t)1000) == pdPASS) {
            Serial.print("---- T = ");
            Serial.print(climate.temp, 1);
            Serial.print("°C, H = ");
            Serial.print(climate.humid, 1);
            Serial.println("%");
        }
        vTaskDelay(configTICK_RATE_HZ*4);
    }
}

float dumtemp = 23.2, dumhumid = 34.2;

void DHT_thread_func(void *pvParameters) {
    struct _climate_S climate;
    Serial.println("DHT_thread_func started");

    for(;;) {
        if(dht_sensor.measure(&climate.temp, &climate.humid, false)) {
            climate.temp = dumtemp; dumtemp += 0.7;
            climate.humid = dumhumid; dumhumid += 0.63;
            /* 
            Serial.print("???? T = ");
            Serial.print(climate.temp, 1);
            Serial.print("°C, H = ");
            Serial.print(climate.humid, 1);
            Serial.println("%");
            Serial.println("DHT_thread_func ENQUEUES");
            */
            xQueueSend(queue, (void *)&climate, (TickType_t) 0);
        }
        vTaskDelay(configTICK_RATE_HZ*5);
    }
}