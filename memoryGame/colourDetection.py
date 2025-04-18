import cv2
import numpy as np
import time

def get_color_from_hsv(h, s, v):
    """
    Detect color from HSV values (modified for memory game colors)
    Returns: color name and BGR color for display
    """
    if v < 30 and s < 30:  # Black (low brightness and low saturation)
        return 'black', (0, 0, 0)
    elif s < 40 and v > 120:  # White (low saturation, high brightness)
        return 'white', (255, 255, 255)
    elif (h < 8 or h >= 175) and s > 50 and v > 70:  # Red
        return 'red', (0, 0, 255)
    elif 10 <= h < 20 and s > 50 and v > 60:  # Orange
        return 'orange', (0, 165, 255)
    elif 20 <= h < 32 and s > 30 and v > 50:  # Yellow
        return 'yellow', (0, 255, 255)
    elif 35 <= h < 85 and s > 40 and v > 60:  # Green
        return 'green', (0, 255, 0)
    elif 90 <= h < 125 and s > 40 and v > 60:  # Blue
        return 'blue', (255, 0, 0)
    elif 125 <= h < 140 and s > 40 and v > 60:  # Purple
        return 'purple', (128, 0, 128)
    elif 140 <= h < 160 and s > 40 and v > 60:  # Pink
        return 'pink', (203, 192, 255)
    else:
        return 'unknown', (0, 0, 0)

def detect_card_colour(timeout=10):
    """
    Detects the color of a card in the center of the camera view
    Args:
        timeout: Maximum time to wait for detection (seconds)
    Returns:
        str: Detected color name or None if timeout
    """
    cap = None
    try:
        # Initialize camera
        cap = cv2.VideoCapture(0)
        cap.set(cv2.CAP_PROP_FRAME_WIDTH, 1280)
        cap.set(cv2.CAP_PROP_FRAME_HEIGHT, 720)
        
        # Detection parameters
        frame_center = (640, 360)  # Center of 1280x720 frame
        detection_size = 300
        sample_size = 50  # 50x50 pixel sample from center
        required_stable_frames = 5
        stable_frame_count = 0
        start_time = time.time()
        
        # For color averaging
        color_samples = []
        max_samples = 5
        
        while (time.time() - start_time) < timeout:
            ret, frame = cap.read()
            if not ret:
                print("Failed to capture frame")
                continue
            
            # Convert to HSV and normalize
            hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)
            hsv[:, :, 2] = cv2.equalizeHist(hsv[:, :, 2])
            
            # Get center region
            center_region = hsv[
                frame_center[1]-sample_size//2:frame_center[1]+sample_size//2,
                frame_center[0]-sample_size//2:frame_center[0]+sample_size//2
            ]
            
            if center_region.size > 0:
                # Calculate average HSV
                h_avg = int(np.mean(center_region[:, :, 0]))
                s_avg = int(np.mean(center_region[:, :, 1]))
                v_avg = int(np.mean(center_region[:, :, 2]))
                
                # Get current color
                current_color = get_color_from_hsv(h_avg, s_avg, v_avg)
                
                # Add to samples buffer
                color_samples.append((h_avg, s_avg, v_avg))
                if len(color_samples) > max_samples:
                    color_samples.pop(0)
                
                # Check if we have stable detection
                if len(color_samples) == max_samples:
                    # Check if all recent samples agree
                    colors = [get_color_from_hsv(h,s,v) for h,s,v in color_samples]
                    if all(c == colors[0] for c in colors):
                        stable_frame_count += 1
                    else:
                        stable_frame_count = max(0, stable_frame_count - 1)
                    
                    if stable_frame_count >= required_stable_frames:
                        # Return the most common color from samples
                        avg_h = int(np.mean([s[0] for s in color_samples]))
                        avg_s = int(np.mean([s[1] for s in color_samples]))
                        avg_v = int(np.mean([s[2] for s in color_samples]))
                        return get_color_from_hsv(avg_h, avg_s, avg_v)
            
            # Small delay to prevent high CPU usage
            time.sleep(0.05)
        
        return None  # Timeout
    
    except Exception as e:
        print(f"Error during color detection: {e}")
        return None
    
    finally:
        # Ensure camera is released
        if cap is not None and cap.isOpened():
            cap.release()

# Example usage in a main program
if __name__ == "__main__":
    print("Starting color detection... Show a card to the camera")
    detected_color = detect_card_colour()
    
    if detected_color:
        print(f"Detected color: {detected_color}")
    else:
        print("Color detection failed or timed out")