from VendorIO import Nickelreturn,Itemreturn,Trigger_Pin
from machine import Pin

n=Pin(16,Pin.IN,Pin.PULL_DOWN)
d=Pin(17,Pin.IN,Pin.PULL_DOWN)

nt = Trigger_Pin(n)
dt = Trigger_Pin(d)
def nick():
    return nt.Triggered()
    # or False
def dime():
    return dt.Triggered()
    # or False

print("Møntindkast initialiserer")
#ideen her er at definere en funktion for hver tilstand
#funktionen kaldes den pågældende tilstand er aktiv.
#


def S0():
    if dime():
        return S10
    if nick():
        return S5
    return S0
def S5():
    if dime():
        return S15
    if nick():
        return S10
    return S5
def S10():
    if dime():
        return S20
    if nick():
        return S15
    return S10
def S15():
    Itemreturn()
    return S0
def S20():
    Nickelreturn()
    return S15

state = S0   #startstate

def RunSm():
    global state
    state = state()


























