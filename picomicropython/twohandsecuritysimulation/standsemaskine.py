import pygame, sys
from pygame.locals import *


def init():
    global screen,red,white,green,blue,bg,Press,downwards,y,clock,sound1,sound2,sound3,b1,b2,es
    pygame.init()
    screen = pygame.display.set_mode((340, 480))
    pygame.display.set_caption("Pressemaskinen")
    sound1 =  pygame.mixer.Sound("womp.wav")
    sound2 =  pygame.mixer.Sound("womp2.wav")
    sound3 =  pygame.mixer.Sound("phone_slam.wav")
#    sound4 =  pygame.mixer.Sound("wagon_wheels.wav")
#    sound4.set_volume(0.02)

    clock = pygame.time.Clock()

    y=40
    downwards=True

    Press= False

    done = False
    white=(255,255,255)
    red = (255,0,0)
    green = (0,255,0)
    blue = (0,0,255)
    bg = (127,127,127)
    b1 = False
    b2 = False
    es = False


def run():
     global screen, red, white, green,blue, bg, Press, downwards, y,clock,sound1,sound2,sound3,b1,b2,es
     incolor = (0,0,0)
     if Press:
       incolor = red
       if downwards:
        y += 1
       else:
        y -= 1
       if (y < 40):
        downwards = True
       if (y > 120):
        downwards = False
     if (y < 45):
      outcolor = red
      es =True
     else:
      outcolor = (0,0,0)
      es = False

     if y==120:
         sound1.play()
     if y==43:
         sound2.play()
     if y==100:
         sound3.play()
     #if y==60:
     #    sound4.play()

     screen.fill(bg)
     pygame.draw.rect(screen, red, pygame.Rect(100, 30, 160, 400), 10)  #chassis
     pygame.draw.rect(screen, green, pygame.Rect(170, 200, 10, 20), 1)  #base
     pygame.draw.rect(screen, blue, pygame.Rect(110, y, 140, 100), 20)  #piston
     pygame.draw.rect(screen, green, pygame.Rect(110, 220, 140, 200), 10)  #base
     pygame.draw.circle(screen,incolor, [80,400], 10)
     pygame.draw.circle(screen,outcolor, [280,400], 10)  #output
     pygame.display.update()
     #pygame.image.save(screen, "circles.png")
     for event in pygame.event.get():
         if event.type == pygame.QUIT:
             done = True
         if event.type == pygame.MOUSEBUTTONDOWN:
             if event.button == 1: #left
                 b1=True
             if event.button == 3: #right
                 b2=True

         if event.type == pygame.MOUSEBUTTONUP:
             if event.button == 1: #left
                 b1=False
             if event.button == 3: #right
                 b2=False

         if event.type == pygame.KEYDOWN:
             if event.mod & pygame.KMOD_LSHIFT:
                     b1=True
             if event.mod & pygame.KMOD_RSHIFT:
                     b2=True
             if event.mod == (pygame.KMOD_RSHIFT | pygame.KMOD_LSHIFT):
                 b1 = True
                 b2 = True
         if event.type == pygame.KEYUP:
             if (event.mod ==pygame.KMOD_LSHIFT):
                     b1 = False
             if (event.mod  == pygame.KMOD_RSHIFT):
                     b2 = False
             if event.mod == 0:
                 b1 = False
                 b2 = False

     clock.tick(60)  # 120 fps  ??


def Activate(act):
    global Press
    Press=act

def B1():
    global b1
    return b1

def B2():
    global b2
    return b2

def Endestop():
    return es
