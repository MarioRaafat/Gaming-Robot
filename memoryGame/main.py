import serial
import random
import time
import colourDetection as cd


# constant angles
elimnate_angels = [115, 60, 10]
camera_angels = [100, 100, 100]
flip_angels = [100, 100, 100]
unflip_angels = [100, 100, 100]


# 20 card slots initialized as "unknown"
cards_memory = ["unknown"] * 16

# Function to wait for Enter key press in terminal,
# the purpose is to pause the execution to check is the arm is in the right position or not
# and to check the color detection
def wait_for_enter():
    """Pause execution until Enter key is pressed in the terminal."""
    input("Press Enter to continue...")
    return


# the next line is for virtual serial communication
# serial_com = SerialCom.SerialCom()

# the next line is for real serial communication
# Make sure to change the COM port to match your Arduino's port
ser = serial.Serial("COM6", 9600, timeout=None)

def send_command_to_arduino(command):
    time.sleep(1)     
    ser.write(command.encode())
    print("Message sent!")

    # that line will wait for the arduino to send a message back, so it blocks the code until the message is received
    str = ser.readline().decode()
    print(str)
 


def find_matching_cards():
    """Finds two cards with the same color in memory."""
    color_positions = {}  # Store color locations

    for i, color in enumerate(cards_memory):
        if color not in ["unknown", "deleted"]:
            if color in color_positions:
                return (color_positions[color], i)  # Return matched indices
            color_positions[color] = i  # Store first occurrence

    return None  # No match found


def pick_random_card():
    """Selects a random unknown card."""
    unknown_positions = [i for i in range(16) if cards_memory[i] == "unknown"]
    if not unknown_positions:
        return None  # No unknown cards left
    return random.choice(unknown_positions)


def calculate_angles(n):
    if not (0 <= n <= 15):
        raise ValueError("Input number must be between 0 and 15")

    angels = [
        [75, 10, 0],  # Position 0
        [65, 5, 0],
        [65, 3, 0],
        [65, 3, 0],
        [72, 3, 0],
        [85, 7, 0],
        [100, 10, 0],
        [92, 10, 0],
        [85, 12, 0],  # Position 8
        [90, 42, 80],
        [95, 14, 0],
        [100, 17, 0],
        [115, 30, 0],
        [105, 30, 0],
        [105, 30, 0],
        [110, 35, 0], # Position 15
    ]

    return angels[n]


def check_match(pos1, pos2):
    """Simulates checking if two flipped cards match."""
    if cards_memory[pos1] == cards_memory[pos2]:
        print(f"✅ MATCH FOUND! Removing cards at {pos1} and {pos2}")
        return True
    else:
        print(f"❌ No match. Remembering colors.")
        return False



############################################### ARDUINO COMMANDS #######################################################
# we are sending only 6 commands to the arduino
# 1. MOVE: to move the arm to a specific position
# 2. FLIP: to flip the card
# 3. UP: to move the arm up
# 4. DOWN: to move the arm down
# 5. ACTIVE: to activate the pump
# 6. DEACTIVETED: to deactivate the pump

# the handling of the commands is done in the arduino code

def deactivate_pump():
    send_command_to_arduino(f"DOWN")
    send_command_to_arduino(f"DEACTIVATE")
    send_command_to_arduino(f"UP")
    return

def active_pump():
    send_command_to_arduino(f"DOWN")
    send_command_to_arduino(f"ACTIVE")
    send_command_to_arduino(f"UP")
    return

def elimnate_card(pos):
    print(f"🎯 Matching cards found! at {pos}")
    card_angles = calculate_angles(pos)

    send_command_to_arduino(f"MOVE {card_angles[0]} {card_angles[1]} {card_angles[2]}")
    active_pump()
    send_command_to_arduino(f"MOVE {elimnate_angels[0]} {elimnate_angels[1]} {elimnate_angels[2]}")
    deactivate_pump()
    
    cards_memory[pos] = "deleted"
    return



# Our game loop
# This loop will run until all cards are matched and removed from the game
def play_turn():
    """Handles one turn of the game, ensuring the user flips a card before proceeding."""
    print("\n🔄 NEW TURN STARTED!")
    

    # Step 1: Check if there’s a known match
    match = find_matching_cards()
    if match:
        pos1, pos2 = match
        elimnate_card(pos1)
        elimnate_card(pos2)
        

    # Step 2: Pick a random unknown card
    pos = pick_random_card()
    if pos is None:
        print("🏁 No more unknown cards left.")
        return

    angles = calculate_angles(pos) # calculate the required angles
    print(f"📏 Angles for {pos}: {angles[0]}, {angles[1], angles[2]}")
    
    send_command_to_arduino(f"MOVE {angles[0]},{angles[1]},{angles[2]}")
    active_pump()
    send_command_to_arduino(f"MOVE {camera_angels[0]} {camera_angels[1]} {camera_angels[2]}")


    # Step 4: Detect color using the camera module
    send_command_to_arduino(f"DOWN")

    # بص يسطا الكود مخرف من ابو اخر ف احنا بناخده علي اد عقله و بناخد اللون مرتين عشان البيه يرتاح
    detected_color = cd.detect_card_colour()
    time.sleep(1)
    detected_color = cd.detect_card_colour()
    print(f"🎨 Detected color at {pos}: {detected_color}")

    send_command_to_arduino(f"UP")
    
    # Step 5: Save detected color in memory
    cards_memory[pos] = detected_color

    send_command_to_arduino(f"MOVE {flip_angels[0]},{flip_angels[1]},{flip_angels[2]}")
    deactivate_pump()
    send_command_to_arduino(f"FLIP")
    send_command_to_arduino(f"MOVE {unflip_angels[0]},{unflip_angels[1]},{unflip_angels[2]}")
    active_pump()

    send_command_to_arduino(f"MOVE {flip_angels[0]},{flip_angels[1]},{flip_angels[2]}")
    deactivate_pump()
    send_command_to_arduino(f"FLIP")
    
    # Step 6: Look for a known match
    for i in range(16):
        if cards_memory[i] == cards_memory[pos] and i != pos:
            print(f"🎯 Matching found for {cards_memory[pos]} at {pos} and {i}")
           
            elimnate_card(i)

            send_command_to_arduino(f"MOVE {unflip_angels[0]},{unflip_angels[1]},{unflip_angels[2]}")
            active_pump()
            send_command_to_arduino(f"MOVE {elimnate_angels[0]},{elimnate_angels[1]},{elimnate_angels[2]}")
            deactivate_pump()
            cards_memory[pos] = "deleted"
            return
        
    send_command_to_arduino(f"MOVE {unflip_angels[0]},{unflip_angels[1]},{unflip_angels[2]}")
    active_pump()
    send_command_to_arduino(f"MOVE {angles[0]},{angles[1]},{angles[2]}")
    deactivate_pump()


    print("📝 Round done")
    detected_color = None
    print("📝 Current memory:", cards_memory)  # Show memory updates




# Test function to check the movement of the arm and the camera
def test_move():

    pos = 9
    angles = calculate_angles(pos) # calculate the required angles
    print(f"📏 Angles for {pos}: {angles[0]},{angles[1]},{angles[2]}")
    
    send_command_to_arduino(f"MOVE {angles[0]},{angles[1]},{angles[2]}")
    #active_pump()
    wait_for_enter()
    send_command_to_arduino(f"DOWN")
    wait_for_enter()
    send_command_to_arduino(f"MOVE {flip_angels[0]},{flip_angels[1]},{flip_angels[2]}")
    wait_for_enter()

    # Step 4: Detect color using the camera module
    send_command_to_arduino(f"DOWN")
    time.sleep(3)
    send_command_to_arduino("UP")

    wait_for_enter()

    send_command_to_arduino(f"MOVE {angles[0]},{angles[1]},{angles[2]}")
    #deactivate_pump()
    wait_for_enter()
    send_command_to_arduino(f"MOVE {camera_angels[0]} {camera_angels[1]} {camera_angels[2]}")

while "unknown" in cards_memory:
    # temporarily comment the play_turn function to test the arm movement and the camera detection
    # so please use the test_move function to test the arm movement and the camera detection till you are sure that the arm is working fine
    
    #play_turn()
    test_move()
    time.sleep(2)