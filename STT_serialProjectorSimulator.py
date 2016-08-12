#### #!/usr/bin/env python

'''
    http://www.binarytides.com/programming-udp-sockets-in-python/
    http://stor.altervista.org/python/seriale.html
'''

import sys
import serial
import random
import os
from time import sleep


# configure the serial connections (the parameters differs on the device you are connecting to)
# serial API: http://pyserial.sourceforge.net/pyserial_api.html

#port='/dev/ttyUSB0',

ser = serial.Serial(
    port='COM8',
    baudrate=115200,
    bytesize=serial.EIGHTBITS,
    parity=serial.PARITY_NONE,
    stopbits=serial.STOPBITS_ONE
)


if ser.isOpen() == False:
    print 'Serial opening failed'
    sys.exit()



while 1:
        received = ""
        print "waiting commands..."

    	if ser.inWaiting() > 0:
                received = ser.read(ser.inWaiting())
                print received

                if "BRT?" in received:
                    print "BRT received"
                    ser.write("(0-100, 35)")
                    ser.flush()

                if "CON?" in received:
                    print "CON received"
                    ser.write("(0-100, 76)")
                    ser.flush()

                if "PWR?" in received:
                    print "PWR received"
                    ser.write("(0-1, 1)")
                    ser.flush()

        sleep(0.3)
s.close()
