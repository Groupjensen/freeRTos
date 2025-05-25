#include <Arduino.h>
#include <Arduino_FreeRTOS.h>
#include "semphr.h"

// Declare a global variable to hold the handle for our mutex.
// A 'handle' is like an ID that FreeRTOS uses to refer to this specific mutex.
// Mutexes are used to protect shared resources from being accessed by multiple tasks simultaneously.
SemaphoreHandle_t xMutex;

void outputTask(void *pvParameters);
void printTask(const char *pcTaskName);

void setup() {
  Serial.begin(115200);

  // Create a mutex.
  // xSemaphoreCreateMutex() initializes a mutex and returns a handle to it.
  // This mutex will be used to ensure that only one task can print to the Serial monitor at a time.
  xMutex = xSemaphoreCreateMutex();
  xTaskCreate(outputTask, "Output Task", 150, "You are now using the mutex1. #Mutex2 is locked", 1, NULL);
  xTaskCreate(outputTask, "Think about function overloading", 150, "You are now using the mutex2. Mutex1 is locked", 1, NULL);
}

// This is the function that defines the behavior of our 'outputTask' instances.
void outputTask(void *pvParameters) {
  char *pcTaskName = (char *)pvParameters;
  while (1) {
    printTask(pcTaskName);
    // This delay allows other tasks to run.
    vTaskDelay(pdMS_TO_TICKS(200));
  }
}
void printTask(const char *pcTaskName) {
  // - portMAX_DELAY: If the mutex is not available, the task will block indefinitely (wait) until it can be taken.
  // This ensures that no other task holding this mutex can proceed past this point until this task gives it back.
  xSemaphoreTake(xMutex, portMAX_DELAY);
  Serial.println(pcTaskName);

  // Give back (release) the mutex.
  // This makes the mutex available for other tasks that might be waiting to acquire it.
  xSemaphoreGive(xMutex);
  
}

void loop() {
  // Intentionally empty, as FreeRTOS tasks are managing the program flow.
}
