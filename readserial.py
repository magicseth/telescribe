
import serial


with serial.Serial('/dev/cu.usbmodem7CDFA11035A41', 19200, timeout=1) as ser:
    print(ser.name)
    while (True):
        line = ser.readline()   # read a '\n' terminated line
        if (len(line) > 3):
            print(line[0:-2])
