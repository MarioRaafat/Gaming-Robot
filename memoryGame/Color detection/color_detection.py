import cv2
import numpy as np
import urllib.request

# Change this URL to match your phone's camera stream (IP Webcam)
PHONE_CAMERA_URL = "http://192.168.1.7:8080/shot.jpg"

# Define color ranges in HSV (Adjust based on your lighting conditions)
COLOR_RANGES = {
    "Red": [(0, 100, 100), (19, 255, 255)],
    "Orange": [(20, 100, 100), (49, 255, 255)],
    "Yellow": [(50, 100, 100), (89, 255, 255)],
    "Green": [(90, 40, 40), (159, 255, 255)],
    "Sky blue": [(160, 50, 50), (210, 255, 255)],
    "Blue": [(211, 50, 50), (261, 255, 255)],
    "Purple": [(262, 50, 50), (324, 255, 255)],
    "Pink": [(325, 50, 50), (360, 255, 255)],
    "Black": [(0, 0, 0), (180, 255, 50)],
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
        return None, None

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
    avg_hsv = np.mean(roi, axis=(0, 1)).astype(int)
    detected_hsv = tuple(avg_hsv)

    # Check which color matches best
    detected_color = "Unknown"
    for color, (lower, upper) in COLOR_RANGES.items():
        if all(lower[i] <= avg_hsv[i] <= upper[i] for i in range(3)):
            detected_color = color
            break

    return detected_color, detected_hsv


def release_camera():
    """Closes all OpenCV windows."""
    cv2.destroyAllWindows()
