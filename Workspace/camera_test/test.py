import serial
ser = serial.Serial(port='/dev/cu.usbmodem1451', baudrate=38400, timeout=1)
ser.close()
ser.open()
c = ''.join(map(chr, [0x56, 0x00, 0x11, 0x00]))
ser.write(c)
print c
print map(ord, ser.read(size=5))
