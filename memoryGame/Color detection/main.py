import cv2
import threading
from color_detection import get_frame, detect_color, release_camera


def display_camera():
    """Displays the phone camera feed in a moderate-sized window with a centered ROI box."""
    cv2.namedWindow("Live Camera", cv2.WINDOW_NORMAL)
    cv2.resizeWindow("Live Camera", 800, 600)

    while True:
        frame = get_frame()
        if frame is None:
            continue  # Skip if no frame is captured

        # Get frame dimensions
        h, w, _ = frame.shape
        cx, cy = w // 2, h // 2  # Center coordinates

        # Define a centered ROI (100×100 pixels)
        roi_size = 300
        x1, y1 = cx - roi_size // 2, cy - roi_size // 2
        x2, y2 = cx + roi_size // 2, cy + roi_size // 2

        # Draw dynamically centered ROI box
        cv2.rectangle(frame, (x1, y1), (x2, y2), (255, 255, 255), 2)

        # Display the live camera feed
        cv2.imshow("Live Camera", frame)

        # Press 'Q' to quit
        if cv2.waitKey(1) & 0xFF == ord("q"):
            break

    release_camera()


def color_detection_loop():
    """Waits for user input to trigger color detection."""
    while True:
        user_input = input("Press ENTER to detect color... (Type 'exit' to quit)")
        if user_input.lower() == "exit":
            break
        detected_color = detect_color()
        print(f"Detected Color: {detected_color}")


# Run the camera display in a separate thread
camera_thread = threading.Thread(target=display_camera, daemon=True)
camera_thread.start()

# Run the user-triggered color detection loop
color_detection_loop()
