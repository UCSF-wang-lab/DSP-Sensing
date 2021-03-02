# -*- coding: utf-8 -*-
"""
Spyder Editor

This is a temporary script file.
"""

import serial

serial_port = '/dev/tty.usbmodem89166801'
baud_rate = 4000000

write_file_to = "output_30min_4milbaud_2kHz.txt"
output_file = open(write_file_to,"w+")

ser = serial.Serial(serial_port, baud_rate)

while True:
    line = ser.readline()
    line = line.decode("utf-8")
    output_file.write(line)
    
    
# ser.close()
# output_file.close()