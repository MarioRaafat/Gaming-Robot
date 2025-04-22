#include <Servo.h>

Servo bigAngleServo;
Servo babyAngleServo;
Servo rotationalServo;


// control the pump by using a motor driver L293D
const int pump_IN1 = 8;
const int pump_IN2 = 9;
const int pump_ENA = 10;
int nextCubepos = 0;
int CubesPlaces[5][2] = {
    {0, 0},
    {0, 1}, 
    {1, 0}, 
    {1, 1},
    {1, 1}
};
void GetNextCube() {
    if (nextCubepos >= 5) return;
    moveArm(CubesPlaces[nextCubepos][0],CubesPlaces[nextCubepos][1],0);
    pumpOn();
    nextCubepos++;
}

void setup() {
    Serial.begin(9600);
    bigAngleServo.attach(3);
    babyAngleServo.attach(5);
    rotationalServo.attach(6);

    pinMode(pump_IN1, OUTPUT);
    pinMode(pump_IN2, OUTPUT);
    pinMode(pump_ENA, OUTPUT);
}

void moveArm(int angle1, int angle2, int angle3) {
    rotationalServo.write(angle3);
    delay(1000);
    bigAngleServo.write(angle1);
    delay(1000);
    babyAngleServo.write(angle2);
    delay(1000);
}

void pumpOn() {
    digitalWrite(pump_IN1, HIGH);
    digitalWrite(pump_IN2, LOW);
    digitalWrite(pump_ENA, HIGH);
}

void pumpOff() {
    digitalWrite(pump_ENA, LOW);
}




void loop() {
    while(!Serial.available());
  
    String command = Serial.readStringUntil('\n');  // Read command
    command.trim();  // Remove spaces/newlines

    
    if (command == "top-left") {
      GetNextCube();
      moveArm(90, 90, 90);
      pumpOff();
    }
    else if (command == "top-center") {
      GetNextCube();
      moveArm(90, 90, 90);
      pumpOff();
    }
    else if (command == "top-right") {
      GetNextCube();
      moveArm(90, 90, 90);
      pumpOff();
    }
    else if (command == "middle-left") {
      GetNextCube();
      moveArm(90, 90, 90);
      pumpOff();
    }
    else if (command == "middle-center") {
      GetNextCube();
      moveArm(90, 90, 90);
      pumpOff();
    }
    else if (command == "middle-right") {
      GetNextCube();
      moveArm(90, 90, 90);
      pumpOff();
    }
    else if (command == "bottom-left") {
      GetNextCube();
      moveArm(90, 90, 90);
      pumpOff();
    }
    else if (command == "bottom-center") {
      GetNextCube();
      moveArm(90, 90, 90);
      pumpOff();
    }
    else if (command == "bottom-right") {
      GetNextCube();
      moveArm(90, 90, 90);
      pumpOff();
    }
}
