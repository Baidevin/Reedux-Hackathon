import turtle
from time import sleep
import threading

class RoverUI:
    
    starting_position = (-300,-300)
    starting_angle = 90

    def __init__(self):
        self.cmds = []

        self.window = turtle.Screen()
        self.window.setup(800, 800)
        self.window.title('Rover Control')
        self.window.bgcolor('grey')
        self.make_grid()

        # Add inputs for bearing and distance
        
        self.rover = turtle.Turtle()
        self.rover.penup()
        self.rover.setpos(self.starting_position)
        self.rover.setheading(self.starting_angle)
        self.rover.pendown()
        self.rover.speed(1)
        self.rover.color('blue')
        self.rover.shape('turtle')
        self.rover.shapesize(2, 2)
        self.rover.width(2)

        self.windowThread = threading.Thread(target=self.window.mainloop)
        self.windowThread.start()
        
    def make_grid(self):
        grid = turtle.Turtle()
        grid.speed(0)
        grid.color('red')
        # Create an 8x8 grid on the screen
        resolution = 800
        for i in range(9):
            grid.penup()
            grid.goto(-resolution/2, resolution/2 - i * resolution/8)
            grid.pendown()
            grid.forward(resolution)
            grid.penup()
            grid.goto(-resolution/2 + i * resolution/8, resolution/2)
            grid.pendown()
            grid.right(90)
            grid.forward(resolution)
            grid.left(90)
    
    def run_cmd(self):
        
        for command in self.cmds:
            if command['command'] == 'forward':
                self.rover.forward(command['value'] * 10)
            elif command['command'] == 'backward':
                self.rover.backward(command['value'] * 10)
            elif command['command'] == 'left':
                self.rover.left(command['value'])
            elif command['command'] == 'right':
                self.rover.right(command['value'])
            sleep(1)
    
    def enter_cmd(self):
        self.rotation_input = turtle.numinput("Rotation", "Enter rotation (degrees):")
        self.distance_input = turtle.numinput("Distance", "Enter distance (1/10th Grid):")
        try:
            if self.rotation_input < 0:
                self.cmds.append({'command': 'left', 'value': int(-self.rotation_input)})
            else:
                self.cmds.append({'command': 'right', 'value': int(self.rotation_input)})

            if self.distance_input < 0:
                self.cmds.append({'command': 'backward', 'value': int(-self.distance_input)})
            else:
                self.cmds.append({'command': 'forward', 'value': int(self.distance_input)})
                print("negative")
        except:
            print("Invalid input")
            return
        print(self.cmds)