from time import sleep
import serial

def readresponse():
        b = bytearray(b"                                                                    ");
        ser.readinto(b) #when the serial connection is initialized the usb-power is "flicked"
        print(b)  #for full array


def readnumber():
    b = bytearray(b"                                                                    ");
    ser.readinto(b)  # when the serial connection is initialized the usb-power is "flicked"
    print("Value read was  :  ")
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

while option != '0':
    if option== 'R':
        whatelement()
        element = (input("What element will you read : "))
        x = bytearray(":","ascii")
        x += bytes('R','ascii')
        x += bytes(element,'ascii')
        x += bytes('\r','ascii')
        ser.write(x)
        readnumber()
    if option== 'W':
        whatelement()
        element = (input("What element will you write : "))
        number = int(input("How many elements are in the machine now : "))
        x = bytearray(":","ascii")
        x += bytes('W','ascii')
        x += bytes(element,'ascii')
        x += bytes(chr(number),'ascii')
        x += bytes('\r','ascii')
        ser.write(x)
        print("sent package  ")
        print(x)
    menu()
    option = (input("Enter your command : "))
