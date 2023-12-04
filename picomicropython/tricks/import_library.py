'''
#to install umqtt.simple ....  do this (or use Thony  with installer)
import network
#Configure your WiFi SSID and password
ssid = 'ITEK 2nd'
password = '2nd_Semester_F23v'
wlan = network.WLAN(network.STA_IF)
wlan.active(True)
wlan.connect(ssid, password)
wlan.active(True)
wlan.isconnected()
wlan.ifconfig()
import mip
mip.install("umqtt.simple")
'''


