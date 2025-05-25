#include <Arduino.h>
#include <Arduino_FreeRTOS.h>
#include "timers.h"

#define ONE_SHOT_TIMER_PERIOD (pdMS_TO_TICKS(500))
#define AUTO_RELOAD_TIMER_PERIOD (pdMS_TO_TICKS(300))

TimerHandle_t xTimer1, xTimer2;
BaseType_t xTimer1Started, xTimer2Started;

void prvAutoReloadTimerCallback(TimerHandle_t xTimer);
void prvOneShotTimerCallback(TimerHandle_t xTimer);


void setup() {
  Serial.begin(9600);
  xTimer1 = xTimerCreate("One Shot", ONE_SHOT_TIMER_PERIOD, pdFALSE, 0, prvOneShotTimerCallback);

  xTimer2 = xTimerCreate("Auto Reload", AUTO_RELOAD_TIMER_PERIOD,pdTRUE,0,prvAutoReloadTimerCallback);

  //Checking if the xtimer as started
  if((xTimer1 != NULL)&&(xTimer2 != NULL)){
    xTimerStart(xTimer1,0);
    xTimerStart(xTimer2,0);

}


}

void prvOneShotTimerCallback(TimerHandle_t xTimer){
 static TickType_t xTimeNow;
  xTimeNow = xTaskGetTickCount();
  Serial.print("One shot timer callback execution : ");
  Serial.println(xTimeNow);
}

void prvAutoReloadTimerCallback(TimerHandle_t xTimer){
  static TickType_t xTimeNow;
  xTimeNow = xTaskGetTickCount();
  Serial.print("Auto reload timer callback execution : ");
  Serial.println(xTimeNow);
}


void loop() {
  
}