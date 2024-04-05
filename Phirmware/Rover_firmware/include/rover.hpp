#include <Arduino.h>
#include <motor.hpp>

#define FORWARDSPEED 128
#define TURNSPEED 128

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
    Motor leftMotor = Motor(3, 5);
    Motor rightMotor = Motor(6, 9);
    int queueIndex = 0;
};