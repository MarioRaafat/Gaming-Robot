import serial
import time

# Change 'COM3' to your Arduino's port (e.g., '/dev/ttyUSB0' for Linux)
arduino = serial.Serial('COM3', 9600, timeout=1)
time.sleep(2)  # Wait for Arduino to initialize

def send_command(command):
    arduino.write(command.encode())  # Send character
    response = arduino.readline().decode().strip()
    print(f"Arduino: {response}")

print("Enter commands: F (Forward), B (Backward), L (Left), R (Right), S (Stop), Q (Quit)")

while True:
    cmd = input("Command: ").upper()
    if cmd in ['F', 'B', 'L', 'R', 'S']:
        send_command(cmd)
    elif cmd == 'Q':
        break
    else:
        print("Invalid command.")

arduino.close()
