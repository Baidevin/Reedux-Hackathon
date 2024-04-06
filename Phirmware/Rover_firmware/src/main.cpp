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
    bool connected = false;

    for (;;)
    {
        if (!client.connected())
        {
            if (!client.connect(IPAddress(192,168,247,137), 6996))
            {
                Serial.println("Failed to connect to server");
                delay(1000);
                continue;
            }
        }

        if (!connected)
        {
            Serial.println("Connected to server");
            connected = true;

            // Send rover id in format %id,<idnumber>
            client.printf("&id,%d\n", ROVERID);
        }

        if (client.available())
        {
            Command command;
            String input = client.readStringUntil('\n');
            Serial.println(input);
            if (input[0] == '$')
            {
                command.command = input.substring(1, input.indexOf(',')).toInt();
                command.value = input.substring(input.indexOf(',') + 1).toInt();
            }
            else
            {
                Serial.println("Invalid command");
            }
            rover.queueCommand(command.command, command.value);
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
    
    // xTaskCreate(roverTask, "RoverTask", 10000, NULL, 1, &RoverTask);
    // xTaskCreate(socketTask, "SocketTask", 10000, NULL, 1, &SocketTask);
    xTaskCreatePinnedToCore(roverTask, "RoverTask", 10000, NULL, 1, &RoverTask, 0);
    xTaskCreatePinnedToCore(socketTask, "SocketTask", 10000, NULL, 1, &SocketTask, 1);
    // rover.queueCommand(FORWARD, 3000);
    // rover.queueCommand(BACKWARD, 3000);
    // rover.queueCommand(FORWARD, 3000);
    // rover.queueCommand(BACKWARD, 2000);
}

void loop() 
{

}