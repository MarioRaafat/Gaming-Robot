import serial
import time

arduino = serial.Serial('COM1', 9600, timeout=1)

time.sleep(2) 

arduino.write(b'Hello, World!\n')

arduino.close()
