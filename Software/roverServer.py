import socket
import threading
from rover import Rover

class RoverServer:
    def __init__(self):
        self.server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.server.bind(('0.0.0.0', 6996))
        self.server.listen(0)
        
        self.rovers = []
        
        self.accept_thread = threading.Thread(target=self.accept)
        self.accept_thread.start()
        
    def accept(self):
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
    rover = RoverServer()
