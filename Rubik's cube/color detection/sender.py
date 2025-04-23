import serial
import time

def sendDataToArduino(data):
    arduino.write((data + "\n").encode('utf-8'))
    time.sleep(0.2)  # Wait for Arduino to process the data
    arduino.write((data + "\n").encode('utf-8'))
    time.sleep(0.2)  # Wait for Arduino to process the data
    ack = arduino.readline().decode().strip()
    if ack:
     print(f"{ack}")

# Initialize serial communication
arduino = serial.Serial(port='COM3', baudrate=9600, timeout=1)  
time.sleep(5)  # Wait for Arduino to initialize
