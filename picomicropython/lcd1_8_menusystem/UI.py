from machine import Pin
import time

A = Pin(17, Pin.IN,Pin.PULL_DOWN)
B = Pin(16, Pin.IN,Pin.PULL_DOWN)
Push = Pin(18, Pin.IN, Pin.PULL_DOWN)
def UserInput():
        while A() != 0 or B() != 0  or Push()!= 0: #vent på alle signaler er passive
            pass  #gør ingenting
        time.sleep(0.02)  # vent på prell
        UP = 0
        DWN = 0
        SELECT = 0
        while True:
            if Push() == 1:
                SELECT = 1
                time.sleep(0.02)  # vent på prell
                return UP, DWN, SELECT
            if A():
                UP = 1
                time.sleep(0.02)  # vent på prell
                return UP, DWN, SELECT
            if B():
                DWN = 1
                time.sleep(0.02)  # vent på prell
                return UP, DWN, SELECT
