from time import sleep
import serial

def readresponse():
        b = bytearray(b"                                                                    ");
        ser.readinto(b) #when the serial connection is initialized the usb-power is "flicked"
#        print(b[0])  for full array
        print ("Value read was  :  ")
        print(b[0])




#setup serial connection
#ser = serial.Serial('/dev/ttyACM0',115200,timeout=0.5)  # open serial port
ser = serial.Serial('COM29',9600,timeout=0.5)  # open serial port
print(ser.name)         # check which port was really used
sleep(3)
#when the serial connection is initialized the usb-power is "flicked"
#causing the arduino to boot and thereby iddentify itself
readresponse()

def menu():
    print("[R] Read")
    print("[W] Write")
    print("[0] Exit")

def whatelement():
    print("[N] Nickels")
    print("[D] Dimes")
    print("[I] Items")


menu()
option = (input("Enter your command : "))

while option != 0:
    if option== 'R':
        whatelement()
        element = (input("What element will you read : "))
        x = bytearray(":","ascii")
        x += bytes('R','ascii')
        x += bytes(element,'ascii')
        x += bytes('\r','ascii')
        ser.write(x)
        readresponse()
        pass
    if option== 'W':
        print("Not implemented ")
        pass
    menu()
    option = (input("Enter your command : "))
