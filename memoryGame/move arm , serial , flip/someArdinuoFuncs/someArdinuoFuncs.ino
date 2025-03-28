#include <Servo.h>

Servo myServo1;
Servo myServo2;
Servo myServo3;
Servo myServo4;

void setup() {
  Serial.begin(9600);  // Start serial communication
  myServo1.attach(3);  // Attach servos to pins
  myServo2.attach(5);
  myServo3.attach(6);
  myServo4.attach(9);
}

void flip() {
  for (int pos = 0; pos <= 90; pos++) {
    myServo4.write(pos);
    delay(30);
  }
  delay(500);
  myServo4.write(180);
  delay(500);
  Serial.println("DONE");  // Notify Python when done
}

void moveArm(int angle1, int angle2, int angle3) {
  myServo1.write(angle1);
  delay(30);
  myServo2.write(angle2);
  delay(30);
  myServo3.write(angle3);
  delay(500);  // Simulate movement delay
  Serial.println("DONE");  // Notify Python
}

void detect() {
  moveArm(10, 20, 30);  // Arbitrary angles for detection
}

void removeCard(int angle1, int angle2, int angle3) {
  // Move to card position
  myServo1.write(angle1);
  delay(30);
  myServo2.write(angle2);
  delay(30);
  myServo3.write(angle3);
  delay(500);  // Simulate movement delay

  // Arbitrary angles for removal position
  myServo1.write(angle1);
  delay(30);
  myServo2.write(angle2);
  delay(30);
  myServo3.write(angle3);
  delay(500);  // Simulate movement delay

  Serial.println("DONE");  // Notify Python
}

void loop() {
  if (Serial.available() > 0) {
    String command = Serial.readStringUntil('\n');  // Read command
    command.trim();  // Remove spaces/newlines

    if (command.startsWith("MOVE ")) {
      int angle1, angle2, angle3;
      sscanf(command.c_str(), "MOVE %d,%d,%d", &angle1, &angle2, &angle3);
      moveArm(angle1, angle2, angle3);
    } 
    else if (command == "DETECT") {
      detect();
    } 
    else if (command == "FLIP") {
      flip();
    } 
    else if (command.startsWith("REMOVE ")) {
      int angle1, angle2, angle3;
      sscanf(command.c_str(), "REMOVE %d,%d,%d", &angle1, &angle2, &angle3);
      removeCard(angle1, angle2, angle3);
    }

   // Serial.println("DONE");  // Send completion message for any command
  }
}
