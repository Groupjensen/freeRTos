#include <Arduino.h>
#include <Arduino_FreeRTOS.h>
#include <semphr.h>


#define RED 13
#define YELLOW 12
#define BLUE 11

SemaphoreHandle_t xCountingSemaphore;

void redLedControlerTask(void *pvParameter);
void yellowControlerTask(void *pvParameter);
void blueControlerTask(void *pvParameter);


void setup(){
  pinMode(RED,OUTPUT);
  pinMode(YELLOW,OUTPUT);
  pinMode(BLUE,OUTPUT);

  Serial.begin(9600);
  xCountingSemaphore= xSemaphoreCreateCounting(1,0);

  xTaskCreate(redLedControlerTask,"RED TASK", 100, NULL, 1 , NULL); 
  xTaskCreate(yellowControlerTask,"Yellow Task", 100, NULL, 1 , NULL);
  xTaskCreate(blueControlerTask,"BLUE TASK", 100, NULL, 1 , NULL); 
  xSemaphoreGive(xCountingSemaphore);
  vTaskStartScheduler();
}

void redLedControlerTask(void *pvParameter){ 
  while(1){
    xSemaphoreTake(xCountingSemaphore, portMAX_DELAY);
    digitalWrite(RED, digitalRead(RED)^1); // Fixed: Corrected pin name
    Serial.println("Red led");
    xSemaphoreGive(xCountingSemaphore);
    vTaskDelay(2000 / portTICK_PERIOD_MS); // Fixed: Corrected delay unit
  }
}



void yellowControlerTask(void *pvParameter){
  while(1){
    xSemaphoreTake(xCountingSemaphore, portMAX_DELAY);
    digitalWrite(YELLOW, digitalRead(RED)^0);
    Serial.println("Yellow led");
    xSemaphoreGive(xCountingSemaphore);
    vTaskDelay(2000 / portTICK_PERIOD_MS); // Fixed: Corrected delay unit
  }
}

void blueControlerTask(void *pvParameter){ 
  while(1){
    xSemaphoreTake(xCountingSemaphore, portMAX_DELAY);
    digitalWrite(BLUE, digitalRead(RED)^1);
    Serial.println("Blue led");
    xSemaphoreGive(xCountingSemaphore);
    vTaskDelay(2000 / portTICK_PERIOD_MS); // Fixed: Corrected delay unit
  }
}

void loop(){
  
}