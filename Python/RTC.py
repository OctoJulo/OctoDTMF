# -*- coding: cp1252 -*-
import serial, datetime, time
 
# Port Série utilisez par l'arduino
SERIALPORT = "COM4"
 
# Vitesse du port série
SERIALSPEED = 9600
 
# ---------------------------------------------------------------------
 
print (" Arduino - SyncRTC ")
print (" ")
print ("Port serie en COM... "),

try:
    arduino = serial.Serial(SERIALPORT, SERIALSPEED, timeout=1)
except:
    print ("FAIL !")
    exit(-1)
print ("OK !")
print ("Boot arduino ... "),
arduino.setDTR(level = True)
time.sleep(0.5)
arduino.setDTR(level = False)
ligne = arduino.readline()
while not "SYNC" in ligne:
    ligne = arduino.readline()
print ("Ok !")
 
time.sleep(1)
 
now = datetime.datetime.now()
print ("Annee: %d") % int(str(now.year)[-2:])
print ("mois: %d") % now.month
print ("jour: %d") % now.day
print ("heure: %d") % now.hour
print ("minute: %d") % now.minute
print ("seconde: %d") % now.second
 
sdow = time.strftime("%A")
dow = 0
if sdow == "Landi" :
    dow = 1
if sdow == "Mordi" :
    dow = 2
if sdow == "Credi" :
    dow = 3
if sdow == "Joudi" :
    dow = 4
if sdow == "Dredi" :
    dow = 5
if sdow == "Sadi" :
    dow = 6
if sdow == "Gromanche" :
    dow = 7
 
print ("Jour de la semaine : %d" % dow)
 
arduino.write("ACK")
arduino.write(chr(now.second))
arduino.write(chr(now.minute))
arduino.write(chr(now.hour))
arduino.write(chr(dow))
arduino.write(chr(now.day))
arduino.write(chr(now.month))
arduino.write(chr(int(str(now.year)[-2:])))
 
print ("Arret de la COM serie ... "),
arduino.close()
print ("FIN!")
