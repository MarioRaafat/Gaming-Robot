import cv2
import numpy as np
import kociemba
from sender import sendDataToArduino, arduino

h_avg = 0
s_avg = 0
v_avg = 0

# Instructions for scanning each face of the Rubik's Cube
face_instructions = [
    "Show the face with WHITE center"
    "Show the face with RED center",
    "Show the face with BLUE center",
    "Show the face with YELLOW center",
    "Show the face with ORANGE center",
    "Show the face with GREEN center",
]

def get_color_from_hsv(h, s, v):
    if s < 70 and v > 120:  # White (low saturation, high brightness)
        return 'W'
    elif (h >= 130) :  # Red (hue near 0 or 180)
        return 'R'
    elif 5 <= h < 25 :  # Orange (distinct hue)
        return 'O'
    elif 20 <= h < 38 :  # Yellow (clear separation)
        return 'Y'
    elif 40 <= h < 53 and s>=90:  # Green (medium hue range)
        return 'G'
    elif 90 <= h < 100 :  # Blue (typical blue hue)
        return 'B'
    else:
        return 'B'  # Default for unclassified colors


# Function to preprocess the frame (Gaussian blur and brightness normalization)
def preprocess_frame(frame):
    # Apply Gaussian blur to smooth noise
    blurred_frame = cv2.GaussianBlur(frame, (7, 7), 0)

    # Convert to HSV
    hsv_frame = cv2.cvtColor(blurred_frame, cv2.COLOR_BGR2HSV)
    # Normalize the brightness channel (V) to reduce lighting inconsistencies
    hsv_frame[:, :, 2] = cv2.normalize(hsv_frame[:, :, 2], None, 0, 255, cv2.NORM_MINMAX)
    hsv_frame[:, :, 2] = cv2.equalizeHist(hsv_frame[:, :, 2])
    return hsv_frame

# Function to draw a 3x3 grid on the frame
def drawCube(img, size, shape, start_point):
    cell = int(size / shape)
    for i in range(shape + 1):
        # Draw horizontal lines
        cv2.line(img, (start_point[0], start_point[1] + i * cell),
                 (start_point[0] + size, start_point[1] + i * cell), (0, 0, 0), 2)
        # Draw vertical lines
        cv2.line(img, (start_point[0] + i * cell, start_point[1]),
                 (start_point[0] + i * cell, start_point[1] + size), (0, 0, 0), 2)

# Initialize camera
videoFeed = cv2.VideoCapture(0)  # Replace with your camera source if different
face_index = 0  # Keep track of which face is being scanned
faces = []  # List to store color sequences for all six faces

while True:
    ret, frame = videoFeed.read()
    if not ret:
        print("Failed to capture video. Please check your camera.")
        break

    # Preprocess the frame for consistent color detection
    hsv_frame = preprocess_frame(frame)

    # Define cube regions (3x3 grid for Rubik's Cube)
    # Define smaller regions for detecting colors, avoiding white frames
    cube_regions = [
    hsv_frame[88:98, 138:148], hsv_frame[88:98, 198:208], hsv_frame[88:98, 258:268],
    hsv_frame[148:158, 138:148], hsv_frame[148:158, 198:208], hsv_frame[148:158, 258:268],
    hsv_frame[208:218, 138:148], hsv_frame[208:218, 198:208], hsv_frame[208:218, 258:268]
    ]   

    # Detect colors for each region
    color_sequence = []
    for region in cube_regions:
        # Compute the average HSV values for the region
        h_avg = int(np.mean(region[:, :, 0]))
        s_avg = int(np.mean(region[:, :, 1]))
        v_avg = int(np.mean(region[:, :, 2]))
        color = get_color_from_hsv(h_avg, s_avg, v_avg)
        color_sequence.append(color)

    # Store the detected colors for the current face
    if len(faces) < 6:  # Only store data for 6 faces
        faces.append(color_sequence[:])
    else:
        faces[face_index] = color_sequence[:]

    # Overlay instructions for the user
    cv2.putText(frame, face_instructions[face_index], (30, 30),
                cv2.FONT_HERSHEY_SIMPLEX, 0.7, (0, 255, 255), 2)

    # Draw the cube grid on the frame
    drawCube(frame, 180, 3, (100, 60))
    cv2.imshow("Rubik's Cube Scanner", frame)

    # Handle keypress events
    key = cv2.waitKey(1) & 0xFF
    if key == ord('c'):  # Capture the current face when 'c' is pressed
        print(f"Processing: {face_instructions[face_index]}")
        print("Detected Colors:", color_sequence)
        face_index = (face_index + 1) % 6  # Move to the next face
    elif key == ord('s'):  # Save or display all faces when 's' is pressed
        print("Final Cube Colors:", faces)
        break
    elif key == ord('q'):  # Exit the program when 'q' is pressed
        break
    
# Release video feed and close OpenCV windows
videoFeed.release()
cv2.destroyAllWindows()

# start to solve and then send to arduino
<<<<<<< HEAD:Rubik's cube/Color detection code/colorDetect.py


def sendDataToArduino(data):
    arduino.write((data + "\n").encode('utf-8'))
 #   arduino.write((data + "\n").encode('utf-8'))
    time.sleep(0.2)  # Wait for Arduino to process the data
    ack = arduino.readline().decode().strip()
    if ack:
     print(f"{ack}")

# Initialize serial communication
arduino = serial.Serial(port='COM4', baudrate=9600, timeout=1)  
time.sleep(5)  # Wait for Arduino to initialize
=======
>>>>>>> 8ab3b83e344df183bafb2257bc8c7b8fe2301437:Rubik's cube/color detection/colorDetection.py

# Flatten the 2D array to a 1D array
flattened_faces = [color for face in faces for color in face]

color_input = ""
for color in flattened_faces:
    color_input += color

color_input = (color_input)

print("\n--------\n")
print(color_input)


# Map colors to face codes based on center stickers
def custom_map_colors_to_faces(color_string):
    if len(color_string) != 54:
        raise ValueError("Input must be 54 characters long.")
    # Map colors to face codes
    return color_string.replace("W", "U").replace("R", "R").replace("G", "C").replace("Y", "D").replace("O", "L").replace("B", "F").replace("C", "B")


stringToSolve = custom_map_colors_to_faces(color_input)
print("Scrambled cube string:", stringToSolve)
if (stringToSolve=="UUUUUUUUURRRRRRRRRFFFFFFFFFDDDDDDDDDLLLLLLLLLBBBBBBBBB"):
    print("The cube is already solved.")
else:
    solution = kociemba.solve(stringToSolve)
    print("Solution:", solution)


sendDataToArduino(solution)

while True:
       
    if arduino.in_waiting > 0:
        line = arduino.readline().decode('utf-8').rstrip()
        print("Received:", line)

arduino.close()