// Motor A connections
const int in1 = 22;
const int in2 = 23;

// Motor B connections
const int in3 = 24;
const int in4 = 25;

// Motor C connections
const int in5 = 26;
const int in6 = 27;

// Motor D connections
const int in7 = 28;
const int in8 = 29;

void set_dc_motors_pins(){
  // pinMode(enA, OUTPUT);
  // pinMode(enB, OUTPUT);
  // pinMode(enC, OUTPUT);
  // pinMode(enD, OUTPUT);
  
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(in5, OUTPUT);
  pinMode(in6, OUTPUT);
  pinMode(in7, OUTPUT);
  pinMode(in8, OUTPUT);
}

void turn_off_dc_motors(){
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  digitalWrite(in5, LOW);
  digitalWrite(in6, LOW);
  digitalWrite(in7, LOW);
  digitalWrite(in8, LOW); 
}

void init_dc_motors(){
  set_dc_motors_pins();
  turn_off_dc_motors();
}

void move_dc_motor(char command, int motor_number) {
  switch (motor_number) {
    case 1:
      if (command == 'F') move_forward_dc_motor1();
      else if (command == 'B') move_backward_dc_motor1();
      break;
    case 2:
      if (command == 'F') move_forward_dc_motor2();
      else if (command == 'B') move_backward_dc_motor2();
      break;
    case 3:
      if (command == 'F') move_forward_dc_motor3();
      else if (command == 'B') move_backward_dc_motor3();
      break;
    case 4:
      if (command == 'F') move_forward_dc_motor4();
      else if (command == 'B') move_backward_dc_motor4();
      break;
    default:
      Serial.println("Invalid Motor Number");
  }
  // switch (command) {
  //   case 'F': moveForward(); break;
  //   case 'B': moveBackward(); break;
  //   case 'S': turn_off_dc_motors(); break;
  //   default: Serial.println("Invalid Command");
  // }
}

void move_forward_dc_motor1(){
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  delay(100);
  turn_off_dc_motors();
}
void move_backward_dc_motor1(){
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  delay(90);
  turn_off_dc_motors();
}

void move_backward_dc_motor2(){
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  delay(170);
  turn_off_dc_motors();
}


void move_forward_dc_motor2(){
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  delay(170);
  turn_off_dc_motors();
}
void move_forward_dc_motor3(){
  digitalWrite(in5, HIGH);
  digitalWrite(in6, LOW);
  delay(200);
  turn_off_dc_motors();
}
void move_forward_dc_motor4(){
  digitalWrite(in7, HIGH);
  digitalWrite(in8, LOW);
  delay(170);
  turn_off_dc_motors();
}

void move_backward_dc_motor3(){
  digitalWrite(in5, LOW);
  digitalWrite(in6, HIGH);
  delay(200);
  turn_off_dc_motors();
}

void move_backward_dc_motor4(){
  digitalWrite(in7, LOW);
  digitalWrite(in8, HIGH);
  delay(170);
  turn_off_dc_motors();
}

void moveForward() {
  // analogWrite(enA, 170);
  // analogWrite(enB, 170);
  // analogWrite(enC, 255);
  // analogWrite(enD, 255);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  digitalWrite(in5, HIGH);
  digitalWrite(in6, LOW);
  digitalWrite(in7, HIGH);
  digitalWrite(in8, LOW);
  delay(170);
  turn_off_dc_motors();
}

void moveBackward() {
  // analogWrite(enA, 170);
  // analogWrite(enB, 170);
  // analogWrite(enC, 255);
  // analogWrite(enD, 255);
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  digitalWrite(in2, HIGH);
  digitalWrite(in5, LOW);
  digitalWrite(in6, HIGH);
  digitalWrite(in7, LOW);
  digitalWrite(in8, HIGH);
    delay(170);
  turn_off_dc_motors();
}
