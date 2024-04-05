#include <Arduino.h>
#include <motor.hpp>

Motor::Motor(int fwdPin, int revPin)
{
    this->fwdPin = fwdPin;
    this->revPin = revPin;
    pinMode(fwdPin, OUTPUT);
    pinMode(revPin, OUTPUT);

    analogWrite(fwdPin, 0);
    analogWrite(revPin, 0);
    this->speed = 0;
}

void Motor::setSpeed(int speed)
{
    this->speed = speed;
}

void Motor::stop()
{
    speed = 0;
    analogWrite(fwdPin, 0);
    analogWrite(revPin, 0);
}

void Motor::update()
{
    if (speed > 0)
    {
        analogWrite(fwdPin, speed);
        analogWrite(revPin, 0);
    }
    else if (speed < 0)
    {
        analogWrite(fwdPin, 0);
        analogWrite(revPin, -speed);
    }
    else
    {
        analogWrite(fwdPin, 0);
        analogWrite(revPin, 0);
    }
}