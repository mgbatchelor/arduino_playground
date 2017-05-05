# python code for interfacing to VC0706 cameras and grabbing a photo
# pretty basic stuff
# written by ladyada. MIT license

import serial
from datetime import datetime

BAUD = 38400
PORT = "/dev/cu.usbmodem1451"      # change this to your com port!

def readsignal(s):
    r = s.read(1)
    print r
    if(len(r) == 1):
        return r[0] == '!'
    return False

def getbufferlength(s):
    return int(s.read(18)[2:], 2)

def readbuffer(s, bytes):
    addr = 0
    photo = []

    while(addr < bytes + 32):
        reply = s.read(32 + 2)
        r = list(reply)
        photo += r[2:]
        addr += 32
        print str(addr) + "/" + str(bytes)
    return photo

######## main

s = serial.Serial(port=PORT, baudrate=BAUD, timeout=0.2)

while(1==1):
    if(readsignal(s)):
        print "reading picture"
        bytes = getbufferlength(s)
        print bytes, "bytes to read"
        photo = readbuffer(s, bytes)

        f = open(datetime.now().strftime('photo_%d%m%y-%H%M%S.jpg'), 'w')
        #print photo
        photodata = ''.join(photo)
        print "writing picture"
        f.write(photodata)
        f.close()
        print "done"
