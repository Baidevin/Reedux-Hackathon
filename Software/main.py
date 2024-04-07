from roverServer import RoverServer
from roverUI import RoverUI

cmdEnum = {
    "forward": 2,
    "backward": 1,
    "left": 4,
    "right": 3
}

if __name__ == '__main__':
    roverServer = RoverServer()
    roverUI = RoverUI()
    
    while True:
        roverUI.enter_cmd()
        roverUI.run_cmd()
        # Emulate a cmd clear
        # for rover in roverServer.rovers:
        for cmd in roverUI.cmds:
            roverServer.sendCommand(1, cmdEnum[cmd['command']], cmd["value"] * (200 if cmd["command"] in ["forward", "backward"] else 40))
        roverUI.cmds = []