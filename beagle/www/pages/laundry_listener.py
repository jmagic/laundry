import serial
import sys


port = "/dev/ttyUSB0"
ser = serial.Serial(port,9600)
value = 0


status = ['off','washer','dryer','washer and dryer']

#while 1:
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
