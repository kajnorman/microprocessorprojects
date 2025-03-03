import standsemaskine
import time

standsemaskine.init()  # denne linje initierer den animerede maskine

'''
API beskrivelse
standsemaskine.B1() -- er den ene knap i tohåndsstyringen
standsemaskine.B2() -- er den anden knap i tohåndsstyringen
standsemaskine.Endestop()  -- er aktiv når stemplet er i top 
standsemaskine.Activate(1) --  vil aktivere maskinen
standsemaskine.Activate(0) --  vil deaktivere maskinen
'''

#test1
'''
while True:
    standsemaskine.run() # denne linje skal indgå i while løkken for at animere maskinen
    if standsemaskine.B1() and standsemaskine.B2():
        standsemaskine.Activate(1)
    else:
        standsemaskine.Activate(0)
'''
#test2
'''
while True:
    standsemaskine.run() # denne linje skal indgå i while løkken for at animere maskinen
    if standsemaskine.B1() or (standsemaskine.B2() and not standsemaskine.Endestop()):
        standsemaskine.Activate(1)
    else:
        standsemaskine.Activate(0)
'''

#test3  delay
deadline = time.time()

while True:
    standsemaskine.run() # denne linje skal indgå i while løkken for at animere maskinen
    if standsemaskine.B1():
        deadline = time.time() + 3
        standsemaskine.Activate(1)
    if time.time() > deadline:
        standsemaskine.Activate(0)

def getDistance():
    return 120 - y
