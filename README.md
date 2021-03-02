# DSP-Sensing

Repository will handle the acquisition of sensor data on the teensy, its streaming and debugging/piloting of its synchronization with Summit RC+S neural data.

Teensy sensing and serial comm + keyboard is handled in C++, and Teensy code can be easily compiled using Teensyduino. Keyboard feature interacts as standard keyboard with receiving laptop, and in our case is used to progress a motor learning task program.
Laptop side of serial comm is handled in Python with pyserial.

Teensy code has not been optimized but can easily achieve a few kHz. Users seeking to achieve higher sampling rates can parallelize use of ADCs, adjust ADC prescale factor, overclock the CPU, etc., but should be aware that rate limiting step will ultimately be the USB transfer and available resources of the receiving laptop.
