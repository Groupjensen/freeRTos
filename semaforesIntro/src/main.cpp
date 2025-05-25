#include <Arduino.h>
#include<Arduino_FreeRTOS.h>
#include "semphr.h"

#define RED 13
#define YELLOW 12
#define BLUE 11

typedef int TaskProfiler;
TaskProfiler RedTaskProfiler, YellowTaskProfiler, BlueTaskProfiler;

SemaphoreHandle_t xBinarySemaphore ;

void redTask(void *pvParameters);
void yellowTask(void *pvParameters);
void blueTask(void *pvParameters);

void setup() {
  Serial.begin(9600);
  
  xBinarySemaphore = xSemaphoreCreateBinary();
  
  xTaskCreate( redTask, "Red Task", 100, NULL, 1, NULL );
  xTaskCreate( yellowTask, "Yellow Task", 100, NULL, 1, NULL);
  xTaskCreate( blueTask, "Blue Task", 100, NULL, 1, NULL );
}
 
void redTask(void *pvParameters){
  pinMode(RED, OUTPUT);
  xSemaphoreGive(xBinarySemaphore);
  
  while(1){
    xSemaphoreTake(xBinarySemaphore, portMAX_DELAY);
    Serial.println("Red Task is running");
    xSemaphoreGive(xBinarySemaphore);
    vTaskDelay(1);
 }
}

void yellowTask(void *pvParameters){  
pinMode (YELLOW, OUTPUT);
//xSemaphoreGive(xBinarySemaphore);
while(1){
  xSemaphoreTake(xBinarySemaphore, portMAX_DELAY);
  Serial.println("Yellow Task is running");
  xSemaphoreGive(xBinarySemaphore);
  vTaskDelay(1);
}

}

void blueTask(void *pvParameters){
pinMode(BLUE, OUTPUT);
while(1){

  xSemaphoreTake(xBinarySemaphore, portMAX_DELAY);
  Serial.println("Blue Task is running");
  xSemaphoreGive(xBinarySemaphore);
  vTaskDelay(1);
  }

}



void loop() {
  // Empty. Things are done in Tasks.
}
