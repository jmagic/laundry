import socket
import struct
import sys
from time import sleep
import serial

SLEEP_TIME = 5
MYPORT = 10001
group = '238.0.0.1'
port = "/dev/ttyUSB0"
ser = serial.Serial(port,9600)
old_state = 'off'

while True:
    addrinfo = socket.getaddrinfo(group, None)[0]

    s = socket.socket(addrinfo[0], socket.SOCK_DGRAM)

    s.setsockopt(socket.IPPROTO_IP, socket.IP_MULTICAST_TTL, 1)

    ser.write('*')
    data = ser.read()

    data = int(data)
    states = [ 'off', 'washer', 'dryer', 'both' ]
   
    #print states[data]
    if old_state != states[data]:
        old_state = states[data]
        print old_state
        s.sendto(states[data]  , (addrinfo[4][0], MYPORT))
        s.close()
    sleep(SLEEP_TIME)
    
