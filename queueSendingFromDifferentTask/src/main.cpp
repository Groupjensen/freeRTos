#include <Arduino.h>
#include <Arduino_FreeRTOS.h>
#include "queue.h"

QueueHandle_t makyqueue = NULL;
void makeySenderTask(void *pvParameters);
void makeyReceiverTask(void *pvParameters);


void setup(){
  Serial.begin(9600);
  makyqueue = xQueueCreate(5,sizeof(int32_t));
  

  xTaskCreate(makeySenderTask, "Sender task", 100, NULL, 1, NULL);
  xTaskCreate(makeyReceiverTask,"Receiver task", 100, NULL, 1, NULL);
}

void loop(){

}

void makeySenderTask(void *pvParameters){
    BaseType_t qStatus;
    int32_t valueTosend=2025;

    while(1){
        qStatus = xQueueSend(makyqueue,&valueTosend,0);
    }
}

void makeyReceiverTask(void *pvParameters){
    BaseType_t qStatus;
    int32_t valueReceived;
    const TickType_t xTicksToWait =pdMS_TO_TICKS(100);
    while(1){
        xQueueReceive(makyqueue,&valueReceived,xTicksToWait);
        Serial.print("Value received: ");
        Serial.println(valueReceived);
    }
    

    }


