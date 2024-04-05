#include <Arduino.h>
#include <rover.hpp>
#include <motor.hpp>

Rover::Rover()
{

}

void Rover::stop()
{
    leftMotor.stop();
    rightMotor.stop();
}

void Rover::controlLoop()
{
    if (queueIndex > 0)
    {
        executeCommand();
    }
    else
    {
        stop();
    }
}

void Rover::executeCommand()
{
    if (queueIndex == 0)
    {
        return;
    }

    Command currentCommand = commandQueue[0];
    switch (currentCommand.command)
    {
    case FORWARD:
        if (currentCommand.value > 0)
        {
            leftMotor.setSpeed(FORWARDSPEED);
            rightMotor.setSpeed(FORWARDSPEED);
        }
        else
        {
            leftMotor.setSpeed(-FORWARDSPEED);
            rightMotor.setSpeed(-FORWARDSPEED);
        }
        break;
    case BACKWARD:
        if (currentCommand.value > 0)
        {
            leftMotor.setSpeed(-FORWARDSPEED);
            rightMotor.setSpeed(-FORWARDSPEED);
        }
        else
        {
            leftMotor.setSpeed(FORWARDSPEED);
            rightMotor.setSpeed(FORWARDSPEED);
        }
        break;
    case LEFT:
        if (currentCommand.value > 0)
        {
            leftMotor.setSpeed(-TURNSPEED);
            rightMotor.setSpeed(TURNSPEED);
        }
        else
        {
            leftMotor.setSpeed(TURNSPEED);
            rightMotor.setSpeed(-TURNSPEED);
        }
        break;
    case RIGHT:
        if (currentCommand.value > 0)
        {
            leftMotor.setSpeed(TURNSPEED);
            rightMotor.setSpeed(-TURNSPEED);
        }
        else
        {
            leftMotor.setSpeed(-TURNSPEED);
            rightMotor.setSpeed(TURNSPEED);
        }
        break;
    case STOP:
        stop();
        break;
    
    default:
        Serial.println("Invalid command\n");
        break;
    }
    leftMotor.update();
    rightMotor.update();
    delay(currentCommand.value);
    stop();

    // Shift all commands in the queue
    for (int i = 0; i < queueIndex - 1; i++)
    {
        commandQueue[i] = commandQueue[i + 1];
    }
    queueIndex--;

}

void Rover::queueCommand(int command, int value)
{
    //  Add FIFO queue logic here
    Command newCommand;
    newCommand.command = command;
    newCommand.value = value;

    if (queueIndex >= 10)
    {
        Serial.println("Queue is full, cannot add new command\n");
        return;
    }
    
    // Add new command to the queue
    commandQueue[queueIndex] = newCommand;
    queueIndex++;
}