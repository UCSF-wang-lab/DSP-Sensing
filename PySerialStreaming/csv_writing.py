#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Thu May 27 20:23:16 2021

@author: karapresbrey
"""

import serial
import csv

# serial_port = 'COM8'
# write_file_to = "20210303_fulltask.txt"

serial_port = '/dev/cu.usbmodem89918301'
write_file_to = 'rtplottest.csv'
baud_rate = 4000000

class ReadLine:
    def __init__(self, s):
        self.buf = bytearray()
        self.s = s
    
    def readline(self):
        i = self.buf.find(b"\n")
        if i >= 0:
            r = self.buf[:i+1]
            self.buf = self.buf[i+1:]
            return r
        while True:
            i = max(1, min(2048, self.s.in_waiting))
            data = self.s.read(i)
            i = data.find(b"\n")
            if i >= 0:
                r = self.buf + data[:i+1]
                self.buf[0:] = data[i+1:]
                return r
            else:
                self.buf.extend(data)



# output_file = open(write_file_to,"w+")

ser = serial.Serial(serial_port, baud_rate)

rl = ReadLine(ser)

fieldnames = ["val"]

with open(write_file_to, 'w') as csv_file:
    csv_writer = csv.DictWriter(csv_file, fieldnames=fieldnames)
    csv_writer.writeheader()

while True:
    with open(write_file_to, 'a') as csv_file:
        line = rl.readline()
        line = line.decode("utf-8")
        
        csv_writer = csv.DictWriter(csv_file, fieldnames=fieldnames)
        info = {
            "val":int(line)}
        csv_writer.writerow(info)
        # csv_writer = csv.writer(csv_file)
        # csv_writer.writerow([line])
    
    
    

    # output_file.write(line)
    
    
# ser.close()
# output_file.close()


