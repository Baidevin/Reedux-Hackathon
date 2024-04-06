from roverServer import RoverServer


if __name__ == "__main__":
    roverServer = RoverServer()

    # listen to arrow keys
    while True:
        direction  = input("Enter W,A,S,D and press enter: ")

        if direction == 'w':
            roverServer.sendCommand(1, 1, 2000)
        elif direction == 's':
            roverServer.sendCommand(1, 2, 2000)
        elif direction == 'a':
            roverServer.sendCommand(1, 3, 5000)
        elif direction == 'd':
            roverServer.sendCommand(1, 4, 5000)