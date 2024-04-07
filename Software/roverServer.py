import socket
import threading
from rover import Rover

class RoverServer:
    def __init__(self):
        self.server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.server.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        self.server.bind(('0.0.0.0', 6996))
        self.server.listen(0)
        
        self.rovers = []
        
        self.accept_thread = threading.Thread(target=self.accept)
        self.accept_thread.start()
        
    def accept(self):
        print("Accepting connections...")
        while True:
            client, addr = self.server.accept()
            print('Connection from', addr)
            self.rovers.append(Rover(client, addr))
            
    def sendCommand(self, id, command, value):
        for rover in self.rovers:
            if rover.id == id:
                rover.send(f"${command},{value}\n")
                return
        print('Rover ID not valid')

if __name__ == '__main__':
    roverServer = RoverServer()
    waiting = True
    while waiting:
        for rover in roverServer.rovers:
            # print(rover.id)
            if rover.id == 1:
                roverServer.sendCommand(1, 1, 1000)
                roverServer.sendCommand(1, 2, 1000)
                roverServer.sendCommand(1, 3, 1000)
                roverServer.sendCommand(1, 4, 1000)
                roverServer.sendCommand(1, 1, 1000)
                roverServer.sendCommand(1, 2, 1000)
                roverServer.sendCommand(1, 5, 1000)
                roverServer.sendCommand(1, 1, 1000)
                print("Commands sent")
                waiting = False
                break