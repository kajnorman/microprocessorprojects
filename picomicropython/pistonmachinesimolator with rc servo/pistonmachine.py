from machine import Pin, PWM
from time import sleep

pwm0 = PWM(Pin(28))
pwm0.freq(50)

enable = Pin(27, Pin.IN, Pin.PULL_DOWN)
done = Pin(26, Pin.OUT)
done(False)

'''
testet:
pwm0.duty_u16(5400)  #90 grader  ok
pwm1.duty_u16(6400)  #90 grader  ok
pwm0.duty_u16(7400)  #35 grader  ok
pwm1.duty_u16(8000)  #45 grader  ok
pwm1.duty_u16(4800)  #135 grader  ok
pwm0.duty_u16(3400)  #145 grader  ok
#  1600 svarer til 45 grader
#  2000 svarer til 55 grader
#ca 36 "ticks" / grad
#  6480 tick / 0.5-omgang
# ticks for 180 grader  :   pwm0  
'''


def setangle(angle):  #(degree)
    pwm0.duty_u16(int((angle/180)*6480)+2160)


Up=0
Down=1
Direction = Up
Angle = 90
Topangle=135
Bottomangle = 45

def run():
    global Up,Down,Direction,Angle,Topangle,Bottomangle
    if enable():
        if Direction == Up:
            Angle += 2
            if Angle>135:
                Direction = Down
        if Direction == Down:
            Angle -= 2
            if Angle<45:
                Direction = Up
        setangle(Angle)
        if Angle > 125:
            done(True)
        else:
            done(False)


