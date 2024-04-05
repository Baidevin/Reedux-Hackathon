#include <Arduino.h>
#include <rover.hpp>
#include <pins_arduino.h>

Rover rover;

TaskHandle_t RoverTask;
TaskHandle_t SerialTask;

void roverTask(void *pvParameters)
{
    for (;;)
    {
        rover.controlLoop();
        vTaskDelay(10);
    }
}

void setup() 
{
    Serial.begin(9600);
    rover = Rover();
    xTaskCreate(roverTask, "RoverTask", 10000, NULL, 1, &RoverTask);
    rover.queueCommand(FORWARD, 3000);
    rover.queueCommand(BACKWARD, 3000);
    rover.queueCommand(FORWARD, 3000);
    rover.queueCommand(BACKWARD, 2000);
}

void loop() 
{
    
}