#include <Arduino.h>
#include <Arduino_FreeRTOS.h> // Include FreeRTOS library

// Define LED pin
#define LED_PIN 13

// Task function to measure ticks
void vMeasureTickTask(void *pvParameters) {
    (void)pvParameters; // Prevents unused parameter warning
    pinMode(LED_PIN, OUTPUT); // Set LED_PIN as output

    while (1) {
        // Toggle the LED every tick
        digitalWrite(LED_PIN, !digitalRead(LED_PIN)); // Toggle LED state
        vTaskDelay(0.01); // Delay exactly 1 tick
    }
}

void setup() {
    //Serial.begin(9600); // Initialize Serial (optional debugging)
    
    // Create the tick measuring task
    xTaskCreate(vMeasureTickTask, "MeasureTick", 128, NULL, 1, NULL);

    // Start FreeRTOS scheduler
    vTaskStartScheduler();
}

void loop() {
    // FreeRTOS does not use the Arduino main loop
}