
#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Tue Mar  2 13:48:35 2021

@author: karapresbrey
"""

def PySerialStreamTeensy_good(serial_port, write_file_to):

    import serial
    
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
    
    # serial_port = 'COM8'
    baud_rate = 4000000
    
    # write_file_to = "20210303_fulltask.txt"
    output_file = open(write_file_to,"w+")
    
    ser = serial.Serial(serial_port, baud_rate)
    
    rl = ReadLine(ser)
    
    while True:
        line = rl.readline()
        line = line.decode("utf-8")
        output_file.write(line)
        
        
    # ser.close()
    # output_file.close()


