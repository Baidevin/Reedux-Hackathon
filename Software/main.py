import roverServer
import json
import os
import turtle
from time import sleep

if __name__ == '__main__':
    
    data = {}
    
    window = turtle.Screen()
    window.setup(800, 800)
    window.title('Rover Control')
    window.bgcolor('blue')
    
    rover = turtle.Turtle()
    rover.speed(1)
    
    with open('commands.json', 'r') as commands:
        data = json.load(commands)
    
    for command in data['rovers'][0]['commands']:
        if command['command'] == 'forward':
            rover.forward(command['value'])
        elif command['command'] == 'backward':
            rover.backward(command['value'])
        elif command['command'] == 'left':
            rover.left(command['value'])
        elif command['command'] == 'right':
            rover.right(command['value'])
        sleep(1)
        
    window.mainloop()
    