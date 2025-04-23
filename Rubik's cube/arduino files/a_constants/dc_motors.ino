// Motor A connections
const int in1 = 2;
const int in2 = 4;

// Motor B connections
const int in3 = 6;
const int in4 = 7;

// Motor C connections
const int in5 = 8;
const int in6 = 10;

// Motor D connections
const int in7 = 12;
const int in8 = 13;

void set_dc_motors_pins(){
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(enC, OUTPUT);
  pinMode(enD, OUTPUT);
  
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

void move_dc_motor(char command) {
  switch (command) {
    case 'F': moveForward(); break;
    case 'B': moveBackward(); break;
    case 'S': turn_off_dc_motors(); break;
    default: Serial.println("Invalid Command");
  }
}

void moveForward() {
  analogWrite(enA, 170);
  analogWrite(enB, 170);
  analogWrite(enC, 255);
  analogWrite(enD, 255);
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
  analogWrite(enA, 170);
  analogWrite(enB, 170);
  analogWrite(enC, 255);
  analogWrite(enD, 255);
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