#include <Arduino.h>
#include <motor.hpp>

#define FORWARDSPEED 25
#define TURNSPEED 50

enum CommandEnum
{
    FORWARD = 1,
    BACKWARD = 2,
    LEFT = 3,
    RIGHT = 4,
    STOP = 5
};

struct Command
{
    int command;
    int value;
};
class Rover
{
public:
    Rover();
    void controlLoop();
    void queueCommand(int command, int value);
    void executeCommand();
    void stop();

    Command commandQueue[10];
private:
    Motor leftMotor = Motor(18, 17);
    Motor rightMotor = Motor(16, 15);
    int queueIndex = 0;
};