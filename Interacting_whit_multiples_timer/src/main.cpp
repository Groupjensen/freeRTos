#include <Arduino.h>
#include <Arduino_FreeRTOS.h>
#include "timers.h"

#define RED 13
#define YELLOW 12
#define BLUE 11

#define BLUE_TIMER_PERIOD (pdMS_TO_TICKS(120))
#define RED_TIMER_PERIOD (pdMS_TO_TICKS(300))

void pvTimerCallBack(TimerHandle_t xTimer);

TimerHandle_t xBlueTimer, xRedTimer;

void setup() {
  Serial.begin(9600);
  BaseType_t xBlueTimerStarted, xRedTimerStarted;
 xBlueTimer =xTimerCreate("Blue Timer ", BLUE_TIMER_PERIOD, pdTRUE, 0,pvTimerCallBack);
  xRedTimer =xTimerCreate("Red Timer ", RED_TIMER_PERIOD, pdTRUE, 0,pvTimerCallBack);

  if ((xBlueTimer != NULL) &&(xRedTimer != NULL)){
    xBlueTimerStarted = xTimerStart(xBlueTimer,0);
    xRedTimerStarted = xTimerStart(xRedTimer,0);

    //if not created get stuck here
    while((xBlueTimerStarted !=pdPASS) && (xRedTimerStarted !=pdPASS)){}
  }
}

//uint32_t bluExecutionCount;
void pvTimerCallBack(TimerHandle_t xTimer){
  TickType_t xTimeNow;
  xTimeNow = xTaskGetTickCount();
  if(xTimer == xBlueTimer){
    pinMode(BLUE, OUTPUT);
    //bluExecutionCount++;
    Serial.print("Blue Timer execution : ");
    Serial.println(xTimeNow);
    digitalWrite(BLUE, digitalRead(BLUE) ^ 1);
      /*if(bluExecutionCount==4000)
      {
        xTimerStop(xBlueTimer, 0);
      }
        */
  }
  else if(xTimer == xRedTimer){
    pinMode(RED, OUTPUT);
    Serial.print("Red Timer execution : ");
    Serial.println(xTimeNow);
    digitalWrite(RED, digitalRead(RED) ^ 1);
  }
   }


void loop() {

  }