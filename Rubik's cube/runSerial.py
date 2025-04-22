import serial
import time

faces = [['B','B','R','Y','Y','B','B','Y','G','R','O',],[ 'G','G','Y','R','R','R','R','R','R','R',],[ 'Y','Y','Y','Y','Y','Y','O','Y','R'],[ 'W','W','W','W','W','W','W','W','W',],[ 'B','B','B','B','B','B','B','B','B',],[ 'R','O','O','G','G','G','G','G','G',]]
# BBRYYBBYGROROBYRRGWRGRRBOROYWYYGOBWGOGWBOWYOYOGBGWGWWW
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

# Flatten the 2D array to a 1D array
flattened_faces = [color for face in faces for color in face]

# Concatenate all items in the 1D array into a single string
toSend = ''.join(flattened_faces)
print(toSend)
# Red-Yellow-Blue-Green-White-Orange

#testdata = "R"*9 +"Y"*9 +"B"*9 +"G"*9 +"W"*9 +"O"*9
testdata = "RRWRRWRRWYYRYYRYYRBBBBBBBBBGGGGGGGGGOWWOWWOWWYOOYOOYOO" 
while True:
       
    if arduino.in_waiting > 0:
        line = arduino.readline().decode('utf-8').rstrip()
        print("Received:", line)
        break

sendDataToArduino(testdata)

# # print every
while True:
       
    if arduino.in_waiting > 0:
        line = arduino.readline().decode('utf-8').rstrip()
        print("Received:", line)

arduino.close()
# R'R   R'R   R'R    R'R    R'R     R'R



