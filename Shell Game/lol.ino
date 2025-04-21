#include <Servo.h>

Servo bigAngleServo;
Servo babyAngleServo;
Servo rotationalServo;



const int pump_IN1 = 8;
const int pump_IN2 = 9;
const int pump_ENA = 10;


const int leftAngle1[] = {0,0};
const int centerAngle1[] = {0,0};
const int rightAngle1[] = {0,0};

const int leftAngle2[] = {0,0};
const int centerAngle2[] = {0,0};
const int rightAngle2[] = {0,0};

const int leftAngle3[] = {0,0};
const int centerAngle3[] = {0,0};
const int rightAngle3[] = {0,0};


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
    delay(500);
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
  
    String command = Serial.readStringUntil('\n');  
    command.trim(); 

    if (command == "LEFT") {
      moveArm(leftAngle1[0],leftAngle2[0],leftAngle3[0]);
      delay(500);
      pumpOn();
      moveArm(leftAngle1[1],leftAngle2[1],leftAngle3[1]);
      delay(500);
      pumpOff();
    }
    else if (command == "RIGHT") {
      moveArm(rightAngle1[0],rightAngle2[0],rightAngle3[0]);
      delay(500);
      pumpOn();
      moveArm(rightAngle1[1],rightAngle2[1],rightAngle3[1]);
      delay(500);
      pumpOff();
    }
    else if (command == "CENTER") {
      moveArm(centerAngle1[0],centerAngle2[0],centerAngle3[0]);
      delay(500);
      pumpOn();
      moveArm(centerAngle1[1],centerAngle2[1],centerAngle3[1]);
      delay(500);
      pumpOff();
    }

    moveArm(0,0,0);


}