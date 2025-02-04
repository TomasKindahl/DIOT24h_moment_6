SemaphoreHandle_t sem = NULL;

void setup() {
   sem = xSemaphoreCreateBinary();
   ···
   XCreateTask(task_time_writer, ···);
   XCreateTask(task_time_reader, ···);
   ··· annat ···
   vTaskStartScheduler();
}

struct MyTime_s {
   int T, M, S;
} Time;

void task_time_writer(void *pvParameters) {
   // setup
   for (;;) {
       if(xSemaphoreTake(sem, (TickType_t)100) != pdTRUE) {
           int sec = get_sec();
           T = sec/3600;
           M = (sec - T*3600)/60;
           S = sec - T*3600 - M*60;
           xSemaphoreGive(sem);
       }
       else {
           // do something else
       }
   }
   vTaskDelay(configTICK_RATE_HZ);
}

void task_time_reader(void *pvParameters) {
   // setup
   for (;;) {
       if(xSemaphoreTake(sem, (TickType_t)100) != pdTRUE) {
           Serial.print(T); Serial.print(":");
           Serial.print(M); Serial.print(":");
           Serial.println(S);
           xSemaphoreGive(sem);
       }
       else {
           // do something else
       }
   }
   vTaskDelay(configTICK_RATE_HZ*0.01);
}
