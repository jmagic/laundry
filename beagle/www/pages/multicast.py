import socket
import struct
import sys
import time
from urllib import urlopen
import pickle

MYPORT = 10001
MYGROUP_4 = '238.0.0.1'

multicast_group = ('238.0.0.1', 10001 )
MYTTL = 1 

group = MYGROUP_4

addrinfo = socket.getaddrinfo(group, None)[0]

s = socket.socket(addrinfo[0], socket.SOCK_DGRAM)

ttl_bin = struct.pack('@i', MYTTL)

#sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

s.setsockopt(socket.IPPROTO_IP, socket.IP_MULTICAST_TTL, ttl_bin)

#sock.settimeout(0.2)

#ttl = struct.pack('@i', 1)
#sock.setsockopt(socket.IPPROTO_IP, socket.IP_MULTICAST_TTL, ttl)
#int(data) = 123

f = open('/tmp/my_status', 'r')
data = pickle.load(f)

states = [ 'off', 'washer', 'dryer', 'both' ]
   
print states[data]



s.sendto(states[data]  , (addrinfo[4][0], MYPORT))

s.close()
