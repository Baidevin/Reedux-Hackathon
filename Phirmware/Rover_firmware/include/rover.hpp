#include <Arduino.h>

struct Motor
{
    int pin;
    int speed;
};

class Rover
{
public:
    Rover();
    void update();

private:
    Motor frontLeft;
    Motor frontRight;
    Motor backLeft;
    Motor backRight;
};