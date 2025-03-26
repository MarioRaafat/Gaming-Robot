#include <Servo.h>

Servo myServo1;
Servo myServo2;
Servo myServo3;
Servo myServo4;
void flip() {
  for (int pos = 0; pos <= 90; pos++) {
    myServo4.write(pos);
    delay(30);
  }

  delay(500);

  myServo1.write(180);
  delay(500);
}

void moveArm(int angle1 ,int angle2 , int angle3)
{
 myServo1.write(angle1);
 myServo2.write(angle2);
 myServo3.write(angle3);
}


void setup() {
  Serial.begin(9600);
}

void loop() {
  if (Serial.available() > 0) {
    String message = Serial.readString();
    Serial.println(message);  
 }
}
