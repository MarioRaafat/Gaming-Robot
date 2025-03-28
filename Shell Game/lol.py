import cv2
import numpy as np

# Load YOLO
weights_path = "yolov4.weights"
config_path = "yolov4.cfg"
labels_path = "coco.names"

# Load class labels
with open(labels_path, "r") as f:
    class_names = f.read().strip().split("\n")

# Define allowed objects
allowed_classes = ["cup", "sports ball"]

# Load YOLO model
net = cv2.dnn.readNet(weights_path, config_path)

# Use GPU (CUDA) instead of CPU
net.setPreferableBackend(cv2.dnn.DNN_BACKEND_CUDA)
net.setPreferableTarget(cv2.dnn.DNN_TARGET_CUDA)

# Get output layer names
layer_names = net.getUnconnectedOutLayersNames()

# Open webcam
cap = cv2.VideoCapture(0)

# Cup positions and ball tracking
cup_positions = {}  # Stores detected cup positions with unique IDs
ball_position = None  # Last known ball position
tracked_cup_id = None  # Currently tracked cup ID after ball detection

available_cup_ids = [1, 2, 3]  # Only allow 3 IDs at a time
last_seen_cups = {}  # Tracks when cups were last detected

def draw_text(frame, text, position, color=(0, 0, 255)):
    cv2.putText(frame, text, position, cv2.FONT_HERSHEY_SIMPLEX, 0.8, color, 2)

while cap.isOpened():
    ret, frame = cap.read()
    if not ret:
        break

    height, width = frame.shape[:2]

    # Convert frame to blob
    blob = cv2.dnn.blobFromImage(frame, 1/255.0, (416, 416), swapRB=True, crop=False)
    net.setInput(blob)

    # Run forward pass
    detections = net.forward(layer_names)

    boxes, confidences, class_ids = [], [], []
    detected_cups = []
    detected_ball = None

    for output in detections:
        for detection in output:
            scores = detection[5:]
            class_id = np.argmax(scores)
            confidence = scores[class_id]
            class_name = class_names[class_id]

            if confidence > 0.2 and class_name in allowed_classes:
                box = detection[:4] * np.array([width, height, width, height])
                (center_x, center_y, w, h) = box.astype("int")
                x = int(center_x - w / 2)
                y = int(center_y - h / 2)
                
                boxes.append([x, y, int(w), int(h)])
                confidences.append(float(confidence))
                class_ids.append(class_id)

                if class_name == "cup":
                    detected_cups.append((center_x, center_y, w, h))
                elif class_name == "sports ball":
                    detected_ball = (center_x, center_y)

    # Apply Non-Maximum Suppression (NMS)
    indices = cv2.dnn.NMSBoxes(boxes, confidences, 0.3, 0.2)

    if len(indices) > 0:
        for i in indices.flatten():
            x, y, w, h = boxes[i]
            label = f"{class_names[class_ids[i]]}: {confidences[i]:.2f}"
            color = (0, 255, 0)  # Green box
            cv2.rectangle(frame, (x, y), (x + w, y + h), color, 2)
            cv2.putText(frame, label, (x, y - 10), cv2.FONT_HERSHEY_SIMPLEX, 0.5, color, 2)

    # Assign IDs to detected cups (limit to 3)
    updated_cup_positions = {}
    new_cup_ids = []

    for detected_cup in detected_cups:
        cx, cy, w, h = detected_cup
        assigned = False

        # Try to match with existing IDs
        for cup_id, prev_cup in cup_positions.items():
            prev_cx, prev_cy, _, _ = prev_cup
            if abs(prev_cx - cx) < 100:  # Consider it the same cup if close in x-coordinates
                updated_cup_positions[cup_id] = detected_cup
                last_seen_cups[cup_id] = 0  # Reset disappearance counter
                assigned = True
                break
        
        # If it's a new cup and we have an available ID
        if not assigned and available_cup_ids:
            new_id = available_cup_ids.pop(0)
            updated_cup_positions[new_id] = detected_cup
            last_seen_cups[new_id] = 0
            new_cup_ids.append(new_id)

    # Remove old cups if we have more than 3
    while len(updated_cup_positions) > 3:
        oldest_cup = max(last_seen_cups, key=last_seen_cups.get)  # Get least recently updated cup
        del updated_cup_positions[oldest_cup]
        available_cup_ids.append(oldest_cup)  # Make the ID available for reuse

    cup_positions = updated_cup_positions

    # Update disappearance timers
    for cup_id in list(last_seen_cups.keys()):
        if cup_id not in cup_positions:
            last_seen_cups[cup_id] += 1
            if last_seen_cups[cup_id] > 5:  # If cup is missing for a while, free its ID
                available_cup_ids.append(cup_id)
                del last_seen_cups[cup_id]

    print("Cup Positions:", cup_positions)
    print("Detected Ball:", detected_ball)

    # Track ball movement
    if detected_ball:
        ball_position = detected_ball
        closest_cup_id = None
        min_dist = float("inf")
        
        for cup_id, cup in cup_positions.items():
            if cup is not None:
                cx, cy, w, h = cup
                distance = abs(ball_position[0] - cx)
                if distance < min_dist:
                    min_dist = distance
                    closest_cup_id = cup_id

        if closest_cup_id:
            tracked_cup_id = closest_cup_id  # Update the tracked cup ID

    # Draw cups with appropriate colors
    for cup_id, cup in cup_positions.items():
        if cup is not None:
            cx, cy, w, h = cup
            color = (255, 0, 0)  # Default blue
            if cup_id == tracked_cup_id:
                color = (0, 0, 255)  # Red for tracked cup
            cv2.rectangle(frame, (cx - w//2, cy - h//2), (cx + w//2, cy + h//2), color, 2)
            draw_text(frame, f"Cup {cup_id}", (cx - w//2, cy - h//2 - 10), color)

    # Display tracking status
    status_text = f"Tracking cup {tracked_cup_id}" if tracked_cup_id else "No tracked cup"
    draw_text(frame, status_text, (20, 40))

    cv2.imshow("YOLO Cup & Ball Tracking", frame)

    if cv2.waitKey(1) & 0xFF == ord("q"):
        break

cap.release()
cv2.destroyAllWindows()
