#include <Arduino.h>
#include <rover.hpp>

Rover::Rover()
{
  frontLeft.pin = 2;
  frontRight.pin = 3;
  backLeft.pin = 4;
  backRight.pin = 5;
}

void Rover::update()
{
  
}
