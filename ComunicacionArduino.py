import serial

''' 
    This class is used to facilitated the communication
    between Python and Arduino for the proyect

    It hasn't been tested yet
'''
class ArduinoCom(object):
    def __init__(self, port, baudios):
        self.port=port
        self.baudios= baudios
        self.ComHandler=serial.Serial(self.port,self.baudios)

    def write(self, info):
        # The info has to be a string, here it would be treated7
        for i in info:
            return self.ComHandler.write(i.encode('ascii')) # return the amount of sent data
   
    def read(self,Nobytes):
        # It reads the amount of bytes passed
        return self.ComHandler.read(NoBytes)

    def Close(self):
        # it closes the communication port
        self.ComHandler.close()

    pass




