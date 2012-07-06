#!/usr/bin/env python
# -*- coding: UTF-8 -*-

# enable debugging
import cgi
import serial
import sys
#import cgitb
#cgitb.enable()

print "Content-Type: text/plain;charset=utf-8"
print



form = cgi.FieldStorage()
reset = form.getvalue("reset")


port = "/dev/ttyUSB0"
ser = serial.Serial(port,9600)
value = 0


status = ['off','washer','dryer','washer and dryer']


ser.write('*')
value = ser.read()
if (value == '0'):
    print status[0] 
if (value == '1'):
    print status[1]
if (value == '2'):
    print status[2] 
if (value == '3'):
    print status[3]
ser.write(reset)
    

