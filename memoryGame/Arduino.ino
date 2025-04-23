#include <Servo.h>

Servo bigAngleServo;
Servo babyAngleServo;
Servo rotationalServo;
Servo flipingServo;

// control the pump by using a motor driver L293D
const int pump_IN1 = 8;
const int pump_IN2 = 9;
const int pump_ENA = 10;


void setup() {
    Serial.begin(9600);
    bigAngleServo.attach(3);
    babyAngleServo.attach(5);
    rotationalServo.attach(6);
    flipingServo.attach(9);

    flipingServo.write(0); // Initialize fliping servo to 0 degrees to avoid flipping at startup

    pinMode(pump_IN1, OUTPUT);
    pinMode(pump_IN2, OUTPUT);
    pinMode(pump_ENA, OUTPUT);
}

// Function to read numbers from the command string, I know this is not the best way but it works and fuck arduino
void ReadNumbers(const char* command, int* angle1, int* angle2, int* angle3) {
    int i = 0;

    while (command[i] && !isdigit(command[i])) {
        i++;
    }

    // Parse first number
    *angle1 = 0;
    while (isdigit(command[i])) {
        *angle1 = (*angle1 * 10) + (command[i] - '0');
        i++;
    }

    // Skip spaces
    while (command[i] && !isdigit(command[i])) {
        i++;
    }

    // Parse second number
    *angle2 = 0;
    while (isdigit(command[i])) {
        *angle2 = (*angle2 * 10) + (command[i] - '0');
        i++;
    }

    // Skip spaces
    while (command[i] && !isdigit(command[i])) {
        i++;
    }

    // Parse third number
    *angle3 = 0;
    while (isdigit(command[i])) {
        *angle3 = (*angle3 * 10) + (command[i] - '0');
        i++;
    }
}

void flip() {
    for (int pos = 0; pos <= 90; pos++) {
        flipingServo.write(pos);
        delay(30);
    }
    delay(500);
    flipingServo.write(180);
    delay(500);

    flipingServo.write(0);
    Serial.println("DONE");  // Notify Python when done
}

void moveArm(int angle1, int angle2, int angle3) {
    rotationalServo.write(angle3);
    delay(1000);
    bigAngleServo.write(angle1);
    delay(1000);
    babyAngleServo.write(angle2);
    delay(500);
    Serial.println("DONE");  // Notify Python
}

void verticalMove(int direction) {
    if (direction > 0) {
        babyAngleServo.write(80);
    } else if (direction < 0) {
        for (int pos = 50; pos >= 20; pos--) {
            babyAngleServo.write(pos);
            delay(40);
        }
    }

    delay(500);
    Serial.println("DONE");  // Notify Python
}

void pumpOn() {
    digitalWrite(pump_IN1, HIGH);
    digitalWrite(pump_IN2, LOW);
    digitalWrite(pump_ENA, HIGH);

    Serial.println("DONE");  // Notify Python
}

void pumpOff() {
    digitalWrite(pump_ENA, LOW);

    Serial.println("DONE");  // Notify Python
}

void loop() {
    while(!Serial.available());
  
    String command = Serial.readStringUntil('\n');  // Read command
    command.trim();  // Remove spaces/newlines

    if (command.startsWith("MOVE ")) {
        int angle1, angle2, angle3;
        ReadNumbers(command.c_str(),&angle1,&angle2,&angle3);   
        moveArm(angle1, angle2, angle3);
    } else if (command == "UP") {
        verticalMove(1);
    } else if (command == "DOWN") {
        verticalMove(-1);
    } else if (command == "FLIP") {
        flip();
    } else if (command == "ACTIVE") {
        pumpOn();  
    } else if (command == "DEACTIVATE") {
        pumpOff();
    }
}
