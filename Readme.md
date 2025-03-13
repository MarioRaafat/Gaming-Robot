# Gamer Robot

## Introduction
Why play games when you can build a robot to do it for you? The **Gamer Robot** is designed to take on multiple classic games, using cameras, sensors, and smart decision-making to play, strategize, and compete. This project challenges us to design and build a robot capable of recognizing patterns, making intelligent moves, and physically interacting with game elements with speed and accuracy.

## Features
- **Pattern Recognition**: Uses cameras and sensors to recognize objects and patterns.
- **Strategic Decision-Making**: Implements AI and algorithms for optimal moves.
- **Mechanical Interaction**: Engages with game elements physically.
- **Multiple Game Modes**: Plays various classic games.

## Games Implemented

### 1. Shell Game (Find Ball Under 1 of 3 Cups)
**Objective**: Track the correct cup hiding the ball after shuffling.

#### Implementation Details:
- A ball is placed under one of three cups.
- The cups are shuffled randomly.
- The robot must identify the correct cup and indicate its choice.

### 2. Memory Matching Game
**Objective**: Identify and match pairs of cards with the same symbols.

#### Implementation Details:
- Uses cameras or sensors to scan cards.
- Remembers previously revealed cards.
- Matches identical pairs and eliminates them.
- Completes the task when all pairs are found.

### 3. Tic-Tac-Toe (X/O)
**Objective**: Play Tic-Tac-Toe and get three in a row while blocking the opponent.

#### Implementation Details:
- Scans the grid to detect existing Xs and Os.
- Uses predefined logic or AI to decide the best move.
- Places X or O in the chosen position.
- Recognizes the game outcome (win, lose, or draw).

### 4. Rubik’s Cube Solver
**Objective**: Solve a Rubik’s Cube using pattern recognition and algorithms.

#### Implementation Details:
- Detects cube colors using cameras or sensors.
- Computes an optimal solution using solving algorithms.
- Uses mechanical actuators to rotate the cube.
- Signals completion when all faces are uniform in color.

### 5. Target Shooting (Color-Based)
**Objective**: Detect and accurately hit color-based targets.

#### Implementation Details:
- Identifies targets based on color detection.
- Calculates trajectory and angle for precise aiming.
- Fires a projectile (e.g., water gun, soft projectile, or laser pointer).
- Tracks successful hits and provides feedback.

## Technologies Used
- **Microcontroller** (e.g., Arduino, Raspberry Pi, ESP32)
- **Sensors** (Camera, Color Sensor, IR Sensor)
- **Actuators** (Servos, Motors, Solenoids)
- **Programming Languages**: C/C++, Python
- **AI & Algorithms**: Machine Learning for Pattern Recognition, Minimax for Tic-Tac-Toe, Kociemba’s Algorithm for Rubik’s Cube

## How to Run the Project
1. Assemble the robot hardware as per the circuit design.
2. Upload the respective game firmware to the microcontroller.
3. Run the control software on a connected PC (if applicable).
4. Start the game mode and watch the robot play!
