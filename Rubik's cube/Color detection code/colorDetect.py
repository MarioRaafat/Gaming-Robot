import cv2
import numpy as np


h_avg = 0
s_avg = 0
v_avg = 0
# Instructions for scanning each face of the Rubik's Cube
face_instructions = [
    "Show the face with YELLOW center",
    "Show the face with BLUE center",
    "Show the face with RED center",
    "Show the face with GREEN center",
    "Show the face with ORANGE center",
    "Show the face with WHITE center"
]

def get_color_from_hsv(h, s, v):
    if s < 40 and v > 120:  # White (low saturation, high brightness)
        return 'w'
    elif (h < 10 or h >= 170) and s > 40:  # Red (hue near 0 or 180)
        return 'r'
    elif 10 <= h < 20 and s > 50:  # Orange (distinct hue)
        return 'o'
    elif 20 <= h < 30 and s > 50:  # Yellow (clear separation)
        return 'y'
    elif 35 <= h < 85 and s > 40:  # Green (medium hue range)
        return 'g'
    elif 90 <= h < 125 and s > 40:  # Blue (typical blue hue)
        return 'b'
    else:
        return 'unknown'  # Default for unclassified colors






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
videoFeed = cv2.VideoCapture("http://192.168.1.10:4747/video")  # Replace with your camera source if different
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
        print(f"HSV - H: {h_avg}, S: {s_avg}, V: {v_avg}")
        
        print("Detected Colors:", color_sequence)
        face_index = (face_index + 1) % 6  # Move to the next face
    elif key == ord('s'):  # Save or display all faces when 's' is pressed
        print("Final Cube Colors:", faces)
    elif key == ord('q'):  # Exit the program when 'q' is pressed
        break

# Release video feed and close OpenCV windows
videoFeed.release()
cv2.destroyAllWindows()
