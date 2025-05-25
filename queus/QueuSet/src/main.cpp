#include <Arduino.h>
#include <Arduino_FreeRTOS.h> // Include FreeRTOS library
#include "queue.h" // Include FreeRTOS queue functionality

// Define pin numbers for LED indicators
#define RED 13
#define YELLOW 12
#define BLUE 11

// Declare queue handles for two individual queues
QueueHandle_t xQueue1;
QueueHandle_t xQueue2;

// Declare the queue set handle
QueueSetHandle_t xQueueSet;

// Function prototypes for the sender and receiver tasks
void vSenderTask1(void *pvParameters);
void vSenderTask2(void *pvParameters);
void vReceiverTask(void *pvParameters);

void setup() {

    Serial.begin(9600);

    // Create queues with space for 1 integer each
    xQueue1 = xQueueCreate(2, sizeof(const char *));
    xQueue2 = xQueueCreate(2, sizeof(const char * ));

    // Create a queue set that can monitor 2 queues
    xQueueSet = xQueueCreateSet(1 * 2);

    // Add the two queues to the queue set
    xQueueAddToSet(xQueue1, xQueueSet);
    xQueueAddToSet(xQueue2, xQueueSet);

    // Create two sender tasks with priority 1
    // Ideally, you would pass the queue handle (xQueue1 or xQueue2) as a parameter
    xTaskCreate(vSenderTask1, "Sender 1", 100, (void *)xQueue1, 1, NULL);
    xTaskCreate(vSenderTask2, "Sender 2", 100, (void *)xQueue2, 1, NULL);

    // Create one receiver task with higher priority (priority 2)
    xTaskCreate(vReceiverTask, "Receiver 1", 100, NULL, 2, NULL);
}

void vSenderTask1(void *pvParameters){
  const TickType_t xBlockTime = pdMS_TO_TICKS(100);
  const char * const messageToSend= "Message from sender 1";
  pinMode(BLUE,OUTPUT);
  while(1){
    digitalWrite(BLUE, HIGH);
    vTaskDelay(xBlockTime);
    xQueueSend(xQueue1, &messageToSend,0);
    vTaskDelay(50);
    digitalWrite(BLUE, LOW);
    vTaskDelay(50);
    
  }

}

void vSenderTask2(void *pvParameters){
  const TickType_t xBlockTime = pdMS_TO_TICKS(200);
  const char * const messageToSend= "Message from sender 2";
  pinMode(RED,OUTPUT);
  while(1){
    digitalWrite(RED, HIGH);
    vTaskDelay(xBlockTime);
    xQueueSend(xQueue2, &messageToSend,0);
    vTaskDelay(50);
    digitalWrite(RED, LOW);
    vTaskDelay(50);
    
  }

}

void vReceiverTask(void *pvParameters){
  QueueHandle_t xQueueThatContaintsData;
  const char *pcReceivedString;
  pinMode(YELLOW,OUTPUT);
  while(1){
    digitalWrite(YELLOW, HIGH);
    xQueueThatContaintsData = (QueueHandle_t)xQueueSelectFromSet(xQueueSet, portMAX_DELAY);
    xQueueReceive(xQueueThatContaintsData, (void*)&pcReceivedString, 0);
    Serial.println(pcReceivedString);
    vTaskDelay(50);
    digitalWrite(YELLOW, LOW);
    vTaskDelay(50);
  }
}


void loop() {
    // Loop function is unused in FreeRTOS-based applications
}