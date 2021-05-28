
#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Tue May 27 2021

@author: karapresbrey
"""

import matplotlib.pyplot as plt
from itertools import count
import pandas as pd
from matplotlib.animation import FuncAnimation

import serial


# serial_port = 'COM8'
# write_file_to = "20210303_fulltask.txt"

# serial_port = '/dev/cu.usbmodem89918301'
# write_file_to = 'test'

# baud_rate = 4000000

# output_file = open(write_file_to,"w+")


# class ReadLine:
#     def __init__(self, s):
#         self.buf = bytearray()
#         self.s = s
    
#     def readline(self):
#         i = self.buf.find(b"\n")
#         if i >= 0:
#             r = self.buf[:i+1]
#             self.buf = self.buf[i+1:]
#             return r
#         while True:
#             i = max(1, min(2048, self.s.in_waiting))
#             data = self.s.read(i)
#             i = data.find(b"\n")
#             if i >= 0:
#                 r = self.buf + data[:i+1]
#                 self.buf[0:] = data[i+1:]
#                 return r
#             else:
#                 self.buf.extend(data)



# ser = serial.Serial(serial_port, baud_rate)

# rl = ReadLine(ser)


# index = count()
fig = plt.figure()
ax = plt.axes()
line, = ax.plot([], [], lw=2)



# vals = []
def animate(i):
    # line = rl.readline()
    # line = int(line.decode("utf-8"))
    # type(line)
    # isinstance(line)
    # print(line)
    data = pd.read_csv('rtplottest.csv')
    vals = data['val']
    # vals.append(line)
    plt.cla()
    # plt.plot(data)
    # plt.plot(vals)
    # line.set_data(vals)
    line, = ax.plot(vals, lw=2,color='k')
    # plt.show()
    return line,

anim = FuncAnimation(fig, animate, interval=1000,blit = True)

plt.show()



# while True:
#     line = rl.readline()
#     line = line.decode("utf-8")
#     # output_file.write(line)
    
    
    
# ser.close()
# output_file.close()


