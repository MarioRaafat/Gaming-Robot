// Motor A connections
int enA = 3;
int in1 = 2;
int in2 = 4;
// Motor B connections
int enB = 5;
int in3 = 6;
int in4 = 7;
// Motor C connections
int enC = 9;
int in5 = 8;
int in6 = 10;
// Motor D connections
int enD = 11;
int in7 = 12;
int in8 = 13;
void setup() {
    Serial.begin(9600); // Start serial communication

  // Set all the motor control pins to outputs
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
  // Turn off motors - Initial state
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  digitalWrite(in5, LOW);
  digitalWrite(in6, LOW);
}
void loop() {
  if (Serial.available() > 0) {
    char command = Serial.read();
    Serial.println(command);
    directionControl(command);
  }
}

void directionControl(char command) {
  switch (command) {
    case 'F': moveForward(); break;
    case 'B': moveBackward(); break;
    case 'S': stopMotors(); break;
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
  stopMotors();
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
  stopMotors();
}
void stopMotors() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  digitalWrite(in5, LOW);
  digitalWrite(in6, LOW);
  digitalWrite(in7, LOW);
  digitalWrite(in8, LOW);
}
