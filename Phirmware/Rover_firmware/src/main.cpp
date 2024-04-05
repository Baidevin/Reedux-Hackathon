#include <Arduino.h>
#include <rover.hpp>
#include <pins_arduino.h>
#include <WiFi.h>

const char* ssid = "Bush did 911";
const char* password = "buslunk69";

#define ROVERID 1

Rover rover;

TaskHandle_t RoverTask;
TaskHandle_t SocketTask;

void roverTask(void *pvParameters)
{
    for (;;)
    {
        rover.controlLoop();
        vTaskDelay(10);
    }
}

void socketTask(void *pvParameters)
{
    WiFiClient client;

    for (;;)
    {
        if (!client.connect(IPAddress('ros2-red.local'), 6996))
        {
            Serial.println("Failed to connect to server");
            delay(1000);
            continue;
        }

        vTaskDelay(10);
    }
}

void setup() 
{
    Serial.begin(9600);

    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.println("Connecting to WiFi...");
    }

    Serial.println("Connected to WiFi");
    Serial.println(WiFi.localIP());

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