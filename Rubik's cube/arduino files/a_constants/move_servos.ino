#include <Servo.h>

Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;

// pins on arduino
const int servo1Pin = 2;
const int servo2Pin = 3;
const int servo3Pin = 4;
const int servo4Pin = 5;

// variables storing the last state of each servo
int servo1State = 90; // Front
int servo2State = 90; // Left
int servo3State = 90; // Right
int servo4State = 90; // Back

void attach_servos(){
  servo1.attach(servo1Pin,500,2500);
  servo2.attach(servo2Pin,500,2500);
  servo3.attach(servo3Pin,500,2500);
  servo4.attach(servo4Pin,500,2500);
}

// setting them in vertical position as initial state
void reset_servos(){
  servo1.write(90);
  servo2.write(90);
  servo3.write(90);
  servo4.write(90);
}

void servos_init(){
  attach_servos();
  reset_servos();
  delay(1000);
}

void analyze_moves(String solution_string){
  if(solution_string == "null" || solution_string == "") return;

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
    delay(500);
  }
}

void execute_move(char move, char modifier){
  int times = 1; // Default 90 degree clockwise
  bool ccw = 0;
  if (modifier == '2') {
    times = 2; // 180 degree turn
  } else if (modifier == '\'') {
    ccw= 1; // 270 degree clockwise = 90 degree counter-clockwise
  }

   for (int i = 0; i < times; i++) {
    switch (move) {
      case 'U': rotate_up(ccw); break;
      case 'D': rotate_down(ccw); break;
      case 'L': rotate_left(ccw); break;
      case 'R': rotate_right(ccw); break;
      case 'F': rotate_front(ccw); break;
      case 'B': rotate_back(ccw); break;
      default: 
        Serial.print("Unknown move: ");
        Serial.println(move);
        break;
    }
    delay(500); // Small delay between rotations
  }
}

void rotate_front(bool ccw) {
  if(ccw){
    // if servo1State is 0 --> dc back then go to 90 --> dc front then go to 0
    if(servo1State == 0){
      move_dc_motor('B',1);
      servo1State += 90;
      servo1.write(servo1State);
      move_dc_motor('F',1); 
    }
     Serial.println("Rotating Front Face CCW...");
     servo1State-=90;
     servo1.write(servo1State);
  }
  else{
     // if servo1State is 180 --> dc back then go to 90 --> dc front then go to 180
    if(servo1State == 180){
      move_dc_motor('B',1);
      servo1State = 90;
      servo1.write(servo1State);
      move_dc_motor('F',1);
    }
  Serial.println("Rotating Front Face CW...");
  servo1.write(servo1State+90);
  servo1State+=90; 
   }
       delay(700);
    move_dc_motor('B',1);
    delay(500);
    servo1.write(90);
    servo1State=90; 
    delay(500);
    move_dc_motor('F',1);
}

void rotate_back(bool ccw) {
  if(ccw){
    // if servo4State is 0 --> dc back then go to 90 --> dc front then go to 0
    if(servo4State == 0){
      move_dc_motor('B',4);
      servo4State += 90;
      servo4.write(servo4State);
      move_dc_motor('F',4); 
    }
     Serial.println("Rotating Back Face CCW...");
     servo4State-=90;
     servo4.write(servo4State);
  }
  else{
     // if servo4State is 180 --> dc back then go to 90 --> dc front then go to 180
    if(servo4State == 180){
      move_dc_motor('B',4);
      servo4State = 90;
      servo4.write(servo4State);
      move_dc_motor('F',4);
    }
  Serial.println("Rotating Back Face CW...");
  servo4.write(servo4State+90);
  servo4State+=90; 
   }
       delay(700);
    move_dc_motor('B',4);
    delay(500);
    servo4.write(90);
    servo4State=90; 
    delay(500);
    move_dc_motor('F',4);
}

void rotate_left(bool ccw) {
  if(ccw){
  // if servo2State is 0 --> dc back then go to 90 --> dc front then go to 0
    if(servo2State == 0){
      move_dc_motor('B',2);
      servo2State += 90;
      delay(1000);
      servo2.write(servo2State);
      delay(1000);
      move_dc_motor('F',2); 
      delay(1000);
    }
     servo2State-=90;
     Serial.println(servo2State);
     Serial.println("Rotating Left Face CCW..." + servo2State);
     servo2.write(0);
    }
    else{
// if servo2State is 180 --> dc back then go to 90 --> dc front then go to 180
     if(servo2State == 180){
        move_dc_motor('B',2);
        servo2State = 90;
        servo2.write(servo2State);
        move_dc_motor('F',2);
     }
    Serial.println("Rotating Left Face CW...");
    servo2.write(servo2State+90);
    servo2State+=90; 
    }
    delay(700);
    move_dc_motor('B',2);
    delay(500);
    servo2.write(90);
    servo2State=90; 
    delay(500);
    move_dc_motor('F',2);
  }


void rotate_right(bool ccw) {

  if(ccw){
  // if servo3State is 0 --> dc back then go to 90 --> dc front then go to 0
    if(servo3State == 0){
      move_dc_motor('B',3);
      servo3State += 90;
      servo3.write(servo3State);
      move_dc_motor('F',3); 
    }
     Serial.println("Rotating Right Face CCW...");
     servo3State-=90;
     servo3.write(servo3State);
    }
    else{
// if servo3State is 180 --> dc back then go to 90 --> dc front then go to 180
     if(servo3State == 180){
        move_dc_motor('B',3);
        servo3State = 90;
        servo3.write(servo3State);
        move_dc_motor('F',3);
     }
    Serial.println("Rotating Right Face CW...");
    servo3.write(servo3State+90);
    servo3State+=90; 
    }
        delay(700);
    move_dc_motor('B',3);
    delay(500);
    servo3.write(90);
    servo3State=90; 
    delay(500);
    move_dc_motor('F',3);
}


void rotate_up(bool ccw) {
    
    int del = 1000;

    // move the dc 1 & 2 back to make the cube free
    move_dc_motor('B',1);
    move_dc_motor('B',4);

    delay(del);

    // Rotate the face left and right at the same time to make the cube rotate completely
    rotate_right(0);
    rotate_left(1);

    delay(del);

    // return the back dc to the cube again
    move_dc_motor('F',4);

    delay(del);
    // rotate the back servo as required in the UP face (cw / ccw)
    rotate_back(ccw);

    delay(del);

    // move the back dc back again
    move_dc_motor('B',4);

    delay(del);

    // Rotate the face left and right at the same time to make the cube rotate completely to return to the original position
    rotate_right(1);
    rotate_left(0);

    delay(del);

    //move the front and back dc front to return to the original position
    move_dc_motor('F',1);
    move_dc_motor('F',4);
    
    if(ccw){
      Serial.println("Rotating UP Face CCW...");
    }
    else{
      Serial.println("Rotating UP Face CW...");
    }
}

void rotate_down(bool ccw) {

    int del = 1000;

    // move the dc 1 & 2 back to make the cube free
    move_dc_motor('B',1);
    move_dc_motor('B',4);

    delay(del);

    // Rotate the face left and right at the same time to make the cube rotate completely
    rotate_right(1);
    rotate_left(0);

    delay(del);
    // return the back dc to the cube again
    move_dc_motor('F',4);

    delay(del);
    // rotate the back servo as required in the DOWN face (cw / ccw)
    rotate_back(ccw);

    delay(del);

    // move the back dc back again
    move_dc_motor('B',4);

    delay(del);

    // Rotate the face left and right at the same time to make the cube rotate completely to return to the original position
    rotate_right(0);
    rotate_left(1);

    delay(del);

    //move the front and back dc front to return to the original position
    move_dc_motor('F',1);
    move_dc_motor('F',4);
    
    if(ccw){
      Serial.println("Rotating DOWN Face CCW...");
    }
    else{
      Serial.println("Rotating DOWN Face CW...");
    }
  
}

