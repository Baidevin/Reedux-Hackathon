#pragma once
#include <Arduino.h>

class Motor
{
public:
    Motor(int fwdPin, int revPin);
    void setSpeed(int speed);
    void stop();
    void update();
    
private:
    int fwdPin;
    int revPin;
    int speed;
};