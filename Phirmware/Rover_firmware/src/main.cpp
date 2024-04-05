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
    rover = Rover();
    xTaskCreate(roverTask, "RoverTask", 1000, NULL, 1, &RoverTask);
}

void loop() 
{
    
}