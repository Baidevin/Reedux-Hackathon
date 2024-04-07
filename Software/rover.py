import socket
import threading

class Rover:
    def __init__(self, client:socket, addr):
        self.client = client
        self.addr = addr
        
        self.id = None
        self.status = 'unconnected'
        
        self.rover_thread = threading.Thread(target=self.socketLoop)
        self.rover_thread.start()
        
    def send(self, data):
        self.client.send(data.encode())
        
    def socketLoop(self):
        while True:
            data = self.client.recv(1024)
            if not data:
                print("Connection closed")
                break
            input = data.decode()
            print(input)
            
            # Try to parse the input
            if input[0] == '&':
                input = input[1:]
                try:
                    command, value = input.split(',')
                    if command == 'id':
                        self.id = int(value)
                        print(f'Rover id is {self.id}')
                        self.status = 'idle'
                        print("Sending test command")
                        # self.send('$3,1000\n')
                    elif command == 'status':
                        self.status = value
                except:
                    print('Invalid input')
                    continue
    
        