#include <Arduino.h>
#include <Arduino_FreeRTOS.h>
#include <queue.h>

#define RedLed 13
#define YellowLed 12
#define BlueLed 11
/*
//Creating task function
void redTask(void *pvParameters);
void yellowTask(void *pvParameters);
void blueTask(void *pvParameters);
*/
void vSenderTask(void *pvParameters);
void vReceiverTask(void *pvParameters);

//creating task profiler to debug in the serial monitor
typedef int TaskProfiler;
TaskProfiler SenderTaskProfilerMaky ;
TaskProfiler ReceiverTaskProfilerMaky;

//QueueHandle_t assigne value
QueueHandle_t yearQueue;



void setup() {
  Serial.begin(9600);
  /*
  xTaskCreate(redTask, "Red", 128, NULL, 1, NULL);
  xTaskCreate(yellowTask, "Yellow", 128, NULL, );
  xTaskCreate(blueTask, "Blue", 128, NULL, 1, NULL);
*/
  yearQueue=  xQueueCreate(5, sizeof(int32_t));
  xTaskCreate(vSenderTask, "Sender1", 128, 8221, 1, NULL);
  xTaskCreate(vSenderTask, "Sender2", 128, 2019, 1, NULL);
  xTaskCreate(vReceiverTask, "Receiver", 128, NULL, 2, NULL);
}

void loop() {
  
}
/*
void redTask(void *pvParameters) {
  pinMode(RedLed, OUTPUT);
  while(1) {
    digitalWrite(RedLed,HIGH);
    vTaskDelay(1000);
    digitalWrite(RedLed,LOW);
    vTaskDelay(1000);
  }
}

void yellowTask(void *pvParameters) {
pinMode(YellowLed, OUTPUT);
while(1) {
  digitalWrite(YellowLed,HIGH);
  vTaskDelay(1000);   
  digitalWrite(YellowLed,LOW);
  vTaskDelay(1000);
}
}

void blueTask(void *pvParameters){

  pinMode(BlueLed, OUTPUT);
  while(1) {
    digitalWrite(BlueLed,HIGH);
    vTaskDelay(1000);
    digitalWrite(BlueLed,LOW);
    vTaskDelay(1000);
  }
  }
*/
void vSenderTask(void *pvParameters) {
//
BaseType_t qStatus;
int32_t valueToSend;
valueToSend =(int32_t)pvParameters;
pinMode(RedLed, OUTPUT);
while (1)
{
  qStatus=xQueueSend(yearQueue, &valueToSend,0);
  if(qStatus != pdPASS){
    Serial.println("Could not send to the queue");

  }
  digitalWrite(RedLed,HIGH);
  vTaskDelay(500);
}
}

void vReceiverTask(void *pvParameters){
  BaseType_t qStatus;
  int32_t valueMreceive;
  const TickType_t xTicksToWait =pdMS_TO_TICKS(100);
  while (1)
  {
     qStatus =xQueueReceive(yearQueue, &valueMreceive, xTicksToWait);

    if (qStatus ==pdPASS)
    {
      Serial.println("Data received: ");
      Serial.println(valueMreceive);
    }
    else
    {
      Serial.print("Could not receive from queue. ");

    }
    digitalWrite(RedLed,LOW);
    vTaskDelay(500);
  }
  

}





