from machine import Pin
from time import sleep
class Trigger_Pin:

    def __init__(self, pin):
        self.p = pin
        self.PreviousValue = False
        self.CurrentValue = False

    def Triggered(self):
        self.CurrentValue = self.p()
        if (self.PreviousValue == False and self.CurrentValue == True):
            self.PreviousValue = self. CurrentValue
            sleep(0.015)# undgå kontaktprell
            return True
        else:
            self.PreviousValue = self.CurrentValue
            sleep(0.015)# undgå kontaktprell
            return False


#18 og 19
R = Pin(18,Pin.OUT)
C = Pin(19,Pin.OUT)



def Nickelreturn():
    C.on()
    sleep(0.5)
    C.off()

def Itemreturn():
    R.on()
    sleep(0.5)
    R.off()
