/*void Menu_Print() {
  // Print the menu header
  Serial.println(F("M E N U")); // Print "M E N U" to the serial monitor
  Serial.println(F("==============")); // Print a separator line

  // Print menu options
  Serial.println(F("i   intialize the cube")); // Option to initialize the assembled cube
  Serial.println(F("a   tune the motors")); // Option to fine-tune the motors
  Serial.println(F("s   Scramble the cube")); // Option to scramble the cube
  Serial.println(F("S   Solve the Cube")); // Option to solve the cube

  // Print an empty line for better readability
  Serial.println(F(""));
}
void (*on_going)(); // Declare a function pointer for ongoing operations

void Menu_Process() { 
  // Check if data is available on the serial port
  if (Serial.available()) {
    // Read the incoming character and process it
    switch(Serial.read()) {
      case 'i': // Initialize the cube
        rubik.Init(); // Initialize the Rubik's Cube
        rubik.Print(); // Print the current state of the cube
        break;

      case 'a': // Fine-tune motors
        Serial.println(F("Choose motor to tune\n")); // Prompt the user to choose a motor to fine-tune
        while(Serial.available() == 0) {} // Wait for user input
        switch(Serial.read()) { // Read the selected motor
          case 'B': // Fine-tune the back motor
            Serial.println(F("B\n")); // Print the selected motor
            while(true) { // Enter an infinite loop for fine-tuning
              Up_Back.afinar(); // Fine-tune the back motor
            }
            break;
          case 'R': // Fine-tune the right motor
            while(true) {
              Up_Right.afinar(); // Fine-tune the right motor
            }
            break;
          case 'F': // Fine-tune the front motor
            while(true) {
              Up_Front.afinar(); // Fine-tune the front motor
            }
            break;
          case 'L': // Fine-tune the left motor
            while(true) {
              Up_Left.afinar(); // Fine-tune the left motor
            }
            break;
        }
        break;

      case 'f': // Rotate the front face counter-clockwise
        rubik.RotateFrontCCW(); // Rotate the front face counter-clockwise
        ServosCube_Movex(); // Move servos for the cube
        ServosFace_BackCCW(); // Move servos for the back face counter-clockwise
        ServosCube_MoveX(); // Move servos for the cube
        rubik.Print(); // Print the current state of the cube
        break;

      case 'F': // Rotate the front face clockwise
        rubik.RotateFrontCW(); // Rotate the front face clockwise
        ServosCube_Movex(); // Move servos for the cube
        ServosFace_BackCW(); // Move servos for the back face clockwise
        ServosCube_MoveX(); // Move servos for the cube
        rubik.Print(); // Print the current state of the cube
        break;

      case 'r': // Rotate the right face counter-clockwise
        rubik.RotateRightCCW(); // Rotate the right face counter-clockwise
        ServosFace_RightCCW(); // Move servos for the right face counter-clockwise
        rubik.Print(); // Print the current state of the cube
        break;

      case 'R': // Rotate the right face clockwise
        rubik.RotateRightCW(); // Rotate the right face clockwise
        ServosFace_RightCW(); // Move servos for the right face clockwise
        rubik.Print(); // Print the current state of the cube
        break;

      case 'u': // Rotate the up face counter-clockwise
        rubik.RotateUpCCW(); // Rotate the up face counter-clockwise
        ServosFace_FrontCW(); // Move servos for the front face clockwise
        rubik.Print(); // Print the current state of the cube
        break;

      case 'U': // Rotate the up face clockwise
        rubik.RotateUpCW(); // Rotate the up face clockwise
        ServosFace_FrontCCW(); // Move servos for the front face counter-clockwise
        rubik.Print(); // Print the current state of the cube
        break;

      case 'l': // Rotate the left face counter-clockwise
        rubik.RotateLeftCCW(); // Rotate the left face counter-clockwise
        ServosFace_LeftCW(); // Move servos for the left face clockwise
        rubik.Print(); // Print the current state of the cube
        break;

      case 'L': // Rotate the left face clockwise
        rubik.RotateLeftCW(); // Rotate the left face clockwise
        ServosFace_LeftCCW(); // Move servos for the left face counter-clockwise
        rubik.Print(); // Print the current state of the cube
        break;

      case 'd': // Rotate the down face counter-clockwise
        rubik.RotateDownCCW(); // Rotate the down face counter-clockwise
        ServosFace_BackCCW(); // Move servos for the back face counter-clockwise
        rubik.Print(); // Print the current state of the cube
        break;

      case 'D': // Rotate the down face clockwise
        rubik.RotateDownCW(); // Rotate the down face clockwise
        ServosFace_BackCW(); // Move servos for the back face clockwise
        rubik.Print(); // Print the current state of the cube
        break;

      case 'b': // Rotate the back face counter-clockwise
        rubik.RotateBackCCW(); // Rotate the back face counter-clockwise
        ServosCube_Movex(); // Move servos for the cube
        ServosFace_FrontCW(); // Move servos for the front face clockwise
        ServosCube_MoveX(); // Move servos for the cube
        rubik.Print(); // Print the current state of the cube
        break;

      case 'B': // Rotate the back face clockwise
        rubik.RotateBackCW(); // Rotate the back face clockwise
        ServosCube_Movex(); // Move servos for the cube
        ServosFace_FrontCCW(); // Move servos for the front face counter-clockwise
        ServosCube_MoveX(); // Move servos for the cube
        rubik.Print(); // Print the current state of the cube
        break;

      case 'X': // Move the cube in the X direction
        ServosCube_MoveX(); // Move servos for the cube in the X direction
        break;

      case 'x': // Move the cube in the opposite X direction
        ServosCube_Movex(); // Move servos for the cube in the opposite X direction
        break;

      case 'Z': // Move the cube in the Z direction
        ServosCube_MoveZ(); // Move servos for the cube in the Z direction
        break;

      case 'z': // Move the cube in the opposite Z direction
        ServosCube_Movez(); // Move servos for the cube in the opposite Z direction
        break;

      case 'Y': // Move the cube in the Y direction
        ServosCube_MoveY(); // Move servos for the cube in the Y direction
        break;

      case 'y': // Move the cube in the opposite Y direction
        ServosCube_Movey(); // Move servos for the cube in the opposite Y direction
        break;

      case 's': // Scramble the cube
        rubik.Sramble(30); // Scramble the cube with 30 random moves
        rubik.Print(); // Print the current state of the cube
        break;

      case 'm': // Print the menu
        Menu_Print(); // Print the menu options
        break;

      case 'M': // Initialize the cube
        rubik.Init(); // Initialize the Rubik's Cube
        break;

      case 'S': // Solve the cube
        Serial.print(F("Solving the cube.")); delay(600); // Print "Solving the cube." with delays for effect
        Serial.print(F(".")); delay(600);
        Serial.print(F(".")); delay(800); Serial.print(F("\n"));
        Serial.print(F("\n")); Serial.print(F("Moves to solve the cube: ")); Serial.print(F("\n"));
        rubik.SolveSequence(); // Solve the cube
        lightAnimation(); // Play a light animation
        break;

      case 'p': // Initialize servos and print the cube state
        servos_init(); // Initialize the servos
        rubik.Print(); // Print the current state of the cube
        break;

      default: // Handle invalid commands
        Serial.print(F("invalid command")); // Print "Invalid Command"
    }
  }
}*/
