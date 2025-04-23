#define SPR 200  // Steps per revolution
Stepper motor(SPR, 8, 9, 10, 11);

const int potPin = A0;    // Potentiometer pin
const int switchPin = 7;  // Tact switch pin

int speedValue, steps, direction;

void setup() {
    Serial.begin(9600);
    pinMode(switchPin, INPUT_PULLUP); // Enable pull-up resistor
    Serial.println("Enter Speed (10-99): ");
    
    while (Serial.available() == 0) {} // Wait for input
    speedValue = Serial.parseInt(); // Read speed
    motor.setSpeed(speedValue);
}

void loop() {
    direction = digitalRead(switchPin); // Read direction
    steps = map(analogRead(potPin), 0, 1023, 0, 255); // Scale steps

    if (direction == HIGH) {
        motor.step(steps);  // Clockwise
    } else {
        motor.step(-steps); // Counterclockwise
    }

    Serial.print("Speed: "); Serial.print(speedValue);
    Serial.print(" | Direction: "); Serial.print(direction ? "CW" : "CCW");
    Serial.print(" | Steps: "); Serial.println(steps);

    delay(500); // Delay for smooth movement
}
