#include <Servo.h>

Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;

const int servo1Pin = 3;
const int servo2Pin = 5;
const int servo3Pin = 6;
const int servo4Pin = 9;

void attach_servos(){
  servo1.attach(servo1Pin);
  servo2.attach(servo2Pin);
  servo3.attach(servo3Pin);
  servo4.attach(servo4Pin);
}

void reset_servos(){
  servo1.write(0);
  servo2.write(0);
  servo3.write(0);
  servo4.write(0);
}

void servos_init(){
  attach_servos();
  reset_servos();
}

void analyze_moves(String solution_string){
  if(solution_string == "null") return;

  for(int i = 0 ;i < solution_string.length() ; i++){
    char move = solution_string[i];
    char modifier = ' ';    // any extra char add with a certain move (' or 2)

    if (i + 1 < solution_string.length()) {
      if (solution_string[i+1] == '\'' || solution_string[i+1] == '2') {
        modifier = solution_string[i+1];
        i++; // skip modifier for next iteration
      }
    }

    execute_move(move, modifier);
  }
}

void execute_move(char move, char modifier){
  int times = 1; // Default 90 degree clockwise
  if (modifier == '2') {
    times = 2; // 180 degree turn
  } else if (modifier == '\'') {
    times = 3; // 270 degree clockwise = 90 degree counter-clockwise
  }

   //todo send the correct servo 
   for (int i = 0; i < times; i++) {
    switch (move) {
      case 'U': rotate_up(); break;
      case 'D': rotate_down(); break;
      case 'L': rotate_left(); break;
      case 'R': rotate_right(); break;
      case 'F': rotate_front(); break;
      case 'B': rotate_back(); break;
      default: 
        Serial.print("Unknown move: ");
        Serial.println(move);
        break;
    }
    delay(500); // Small delay between rotations
  }
}

// todo set the angles on real
void rotate_front() {
  Serial.println("Rotating Front Face...");
  servo1.write(90); 
  delay(500);
  servo1.write(0); 
  delay(500);
}

void rotate_back() {
  Serial.println("Rotating Back Face...");
  servo2.write(90); 
  delay(500);
  servo2.write(0); 
  delay(500);
}

void rotate_left() {
  Serial.println("Rotating Left Face...");
  servo3.write(90); 
  delay(500);
  servo3.write(0); 
  delay(500);
}

void rotate_right() {
  Serial.println("Rotating Right Face...");
  servo4.write(90); 
  delay(500);
  servo4.write(0); 
  delay(500);
}

void rotate_up() {
  Serial.println("Rotating Up (top)...");

  servo1.write(90);
  servo2.write(90);
  delay(500);
  servo1.write(0);
  servo2.write(0);
  delay(500);
}

void rotate_down() {
  Serial.println("Rotating Down (bottom)...");

  servo3.write(90);
  servo4.write(90);
  delay(500);
  servo3.write(0);
  servo4.write(0);
  delay(500);
}