import socket
import struct
import sys
from time import sleep
import serial

SLEEP_TIME = 2


BEACON_TIME = 30

MYPORT = 10001
group = '238.0.0.1'
port = "/dev/ttyUSB0"
ser = serial.Serial(port,9600)
states = [ 'off', 'washer', 'dryer', 'both' ]
old_state = 'off'
data = 0
i = 0

def send_status(data):
    addrinfo = socket.getaddrinfo(group, None)[0]
    s = socket.socket(addrinfo[0], socket.SOCK_DGRAM)
    s.setsockopt(socket.IPPROTO_IP, socket.IP_MULTICAST_TTL, 1)
    s.sendto(states[data]  , (addrinfo[4][0], MYPORT))
    s.close()

while True:
    
    if ser.inWaiting() >= 1:
        data = ser.read()
        data = int(data)
 
    i += 1
    #print i
    if i >= (BEACON_TIME / SLEEP_TIME):
        ser.write('S')
        i = 0
    #print states[data]
    #print old_state
    if old_state != states[data]:
        old_state = states[data]
        #print old_state
        send_status(data)
        f = open('/www/pages/status.txt', 'w')
        f.write(states[data])
        f.close()
        i = 0
    sleep(SLEEP_TIME)
    
