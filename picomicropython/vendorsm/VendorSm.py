from VendorIO import Nickelreturn,Itemreturn,Trigger_Pin
from machine import Pin

n=Pin(16,Pin.PULL_DOWN)
d=Pin(17,Pin.PULL_DOWN)

nt = Trigger_Pin(n)
dt = Trigger_Pin(d)
def nick():
    return nt.Triggered()
    # or False
def dime():
    return dt.Triggered()
    # or False

print("Møntindkast initialiserer")

S0 = 0
S5 = 5
S10 = 10
S15 = 15
S20 = 20
Tilstand = S0 # her starter maskinen
def RunSm():
    global Tilstand
    if Tilstand == S0:
        if dime():
            Tilstand = S10
        if nick():
            Tilstand = S5
    if Tilstand == S5:
        if dime():
            Tilstand = S15
        if nick():
            Tilstand = S10
    if Tilstand == S10:
        if dime():
            Tilstand = S20
        if nick():
            Tilstand = S15
    if Tilstand == S15:
        #release item
        Itemreturn()
        Tilstand = S0
    if Tilstand == S20:
        #release change
        Nickelreturn()
        Tilstand = S15

