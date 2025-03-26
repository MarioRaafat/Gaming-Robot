const int ledPin = 13;  // Built-in LED to simulate card flipping

void setup() {
    Serial.begin(9600);  // Start serial communication
    pinMode(ledPin, OUTPUT);
    Serial.println("Arduino Ready");
}

void loop() {
    if (Serial.available() > 0) {
        String command = Serial.readStringUntil('\n');  // Read incoming command
        command.trim();  // Remove any extra whitespace

        if (command.startsWith("FLIP")) {
            int pos = command.substring(5).toInt();  // Extract position number
            Serial.print("Flipping card at position: ");
            Serial.println(pos);
            digitalWrite(ledPin, HIGH);  // Simulate flipping
            delay(500);
            digitalWrite(ledPin, LOW);
            Serial.println("DONE");  // Notify Python
        } 
        else if (command.startsWith("Remove Cards at positions")) {
            Serial.println("Removing matched cards");
            // Simulate removing cards
            Serial.println("DONE");  // Notify Python
        } 
        else if (command.startsWith("UNFLIP")) {
            Serial.println("Unflipping cards");
            digitalWrite(ledPin, LOW); // Simulate unflipping
            Serial.println("DONE");  // Notify Python
        } 
        else {
            Serial.print("Unknown command: ");
            Serial.println(command);
            Serial.println("DONE");  // Avoid Python getting stuck
        }
    }
}
