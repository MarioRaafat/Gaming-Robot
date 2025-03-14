import cv2
import numpy as np
import urllib.request

# Change this URL to match your phone's camera stream (IP Webcam)
PHONE_CAMERA_URL = "http://192.168.46.90:8080/shot.jpg"

# Define color ranges in HSV (Adjust based on your lighting conditions)
COLOR_RANGES = {
   "Red": [(0, 100, 100), (10, 255, 255)],
    "Orange": [(10, 100, 100), (25, 255, 255)],  
    "Yellow": [(20, 100, 100), (40, 255, 255)],
    "Green": [(40, 40, 40), (80, 255, 255)],
    "Blue": [(90, 50, 50), (130, 255, 255)],
    "Black": [(0, 0, 0), (180, 255, 30)]
}

def get_frame():
    """Fetches a single frame from the phone camera stream."""
    try:
        resp = urllib.request.urlopen(PHONE_CAMERA_URL)
        img_array = np.array(bytearray(resp.read()), dtype=np.uint8)
        frame = cv2.imdecode(img_array, -1)

        if frame is None:
            print("Error: Could not decode frame from phone camera.")
            return None

        return frame
    except Exception as e:
        print(f"Error: {e}")
        return None

def detect_color():
    """Detects the color in the center region of the frame."""
    frame = get_frame()
    if frame is None:
        return None

    # Convert frame to HSV
    hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)

        # Get frame dimensions
    h, w, _ = frame.shape
    cx, cy = w // 2, h // 2  # Ensure exact center

    # Define a centered ROI
    roi_size = 300  # Adjust for larger area
    x1, y1 = cx - roi_size // 2, cy - roi_size // 2
    x2, y2 = cx + roi_size // 2, cy + roi_size // 2

    # Ensure ROI is inside frame
    x1, y1 = max(0, x1), max(0, y1)
    x2, y2 = min(w, x2), min(h, y2)

    roi = hsv[y1:y2, x1:x2]  # Extract ROI

    # Calculate average color in ROI
    avg_color = np.mean(roi, axis=(0, 1)).astype(int)

    # Check which color matches best
    detected_color = "Unknown"
    for color, (lower, upper) in COLOR_RANGES.items():
        if all(lower[i] <= avg_color[i] <= upper[i] for i in range(3)):
            detected_color = color
            break

    return detected_color

def release_camera():
    """Closes all OpenCV windows."""
    cv2.destroyAllWindows()
