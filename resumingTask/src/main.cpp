#include <Arduino.h>
#include<Arduino_FreeRTOS.h>


#define RED 13
#define YELLOW 12
#define BLUE 11

TaskHandle_t red_handle, yellow_handle, blue_handle;

void redtask(void *pvParameters);
void yellowtask(void *pvParameters);
void bluetask(void *pvParameters);

//Manipulate  tasksuspend
//uint8_t suspend_monitor, resume_monitor;
uint32_t suspend_monitor, resume_monitor;

bool suspend=false;
// Using explicitly declared TickType_t
const TickType_t _500ms = pdMS_TO_TICKS(500);




void setup(){
	//Serial.begin(9600);
	xTaskCreate(redtask, "Red task debug", 100, NULL, 1, &red_handle);
	xTaskCreate(yellowtask, "Yellow task debug", 100, NULL, 1, &yellow_handle);
	xTaskCreate(bluetask, "Blue task debug", 100, NULL, 1, &blue_handle);
	
}

void loop(){
	
	}

void redtask(void *pvParameters){
	pinMode(RED, OUTPUT);
	while(1){
		digitalWrite(RED, HIGH);
		//Serial.println("led 13");
		vTaskDelay(pdMS_TO_TICKS(125/2));
		digitalWrite(RED, LOW);	
		vTaskDelay(pdMS_TO_TICKS(125/2));
	}
}

void yellowtask(void *pvParameters){
	pinMode(YELLOW, OUTPUT);
	while(1){
		digitalWrite(YELLOW, HIGH);
		//Serial.println("led 12");
		vTaskDelay(pdMS_TO_TICKS(125));
		digitalWrite(YELLOW, LOW);	
		vTaskDelay(pdMS_TO_TICKS(125));

		if(suspend==true){
			resume_monitor++;
			if (resume_monitor==260){
				vTaskResume(blue_handle);
				resume_monitor=0;
				suspend=false;
			}
	}
}
}						

void bluetask(void *pvParameters){
	pinMode(BLUE, OUTPUT);
	while(1){
		suspend_monitor++;
		if(suspend_monitor==260)
		{
			suspend=true;
			suspend_monitor=0;
			//pre  implementation is necessary for the inner task up toward down
			//if not the task get stuck
			vTaskSuspend(blue_handle);
		}

		//blinking led
		digitalWrite(BLUE, HIGH);	
		//Serial.println("led 11");
		vTaskDelay(_500ms);
		digitalWrite(BLUE, LOW);	
		vTaskDelay(_500ms);
	}
	
}


