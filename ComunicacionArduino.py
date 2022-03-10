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
        # The info has to be a string, here it would be treated
        top=len(info)
        # if the data type is a string
        if type(info)==type(str()):
            info=info.upper()
            string=str()
            # First convert to lower cases the ones that are followed by '_'
            if type(info)==type(str()):
            info=info.upper()
            string=str()
            # First convert to lower cases the ones that are followed by '_'
            for i in range(0,top,1):
                if info[i]!='_':
                    if (i+1)<top:
                        if info[i+1]=='_':
                            string+=info[i].lower()
                        else:
                            string+=info[i]
                    else:
                        string+=info[i]
                            #info[i]=info[i].lower()
            # It sends only the letters
            print('Before Sending.  '+string)
        for i in string:
            self.ComHandler.write(i.encode('ascii')) # return the amount of sent data
        
        for i in info:
            return self.ComHandler.write(i.encode('ascii')) # return the amount of sent data
   
    def read(self):
        # It reads the amount of bytes passed
        return self.ComHandler.read_all().decode('ascii')

    def Close(self):
        # it closes the communication port
        self.ComHandler.close()

    pass




