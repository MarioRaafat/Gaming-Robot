//#define DELAY_BETWEEN_STEPS1 (500) 
//#define APERTO (4)

/*
static void clearVision() {
  // Move the right and left down motors to their designated positions
  Down_Right.rmove(place[3]); // Move the right down motor to position stored in place[3]
  Down_Left.rmove(place[3]);  // Move the left down motor to position stored in place[3]
  delay(DELAY_BETWEEN_STEPS1); // Wait for a short delay to allow the motors to complete the movement

  // Move the front and back down motors to their designated positions with an additional offset (APERTO)
  Down_Front.rmove(place[1] + APERTO); // Move the front down motor to position stored in place[1] plus APERTO
  Down_Back.rmove(place[1] + APERTO);  // Move the back down motor to position stored in place[1] plus APERTO
  delay(DELAY_BETWEEN_STEPS1); // Wait for a short delay to allow the motors to complete the movement

  // Rotate the up motors to their designated positions
  Up_Back.Rotate(0);   // Rotate the back up motor to 0 degrees
  Up_Front.Rotate(180); // Rotate the front up motor to 180 degrees
}
*/
void get_solution_string() {
   Serial.println("Now I can recieve ya baby");
   while(Serial.available() == 0){
    }
   solution_String = Serial. readStringUntil('\n');
   solution_String.trim();
   Serial.print("Arduino Received ya baby: ");
   Serial.println(solution_String);
   delay(100);
 //  clearVision(); // 1 sec delay
  //face 0 = right , delay to second face is about 0 seconds
   
 //  Up_Back.Rotate(180);
 //  Up_Front.Rotate(0);
   //face 1 = left , delay to 3rd face is about 1.5 second
   
 /*
   Up_Front.Rotate(90);
   Up_Back.Rotate(90);
   Down_Front.rmove(place[1]);
   Down_Back.rmove(place[1]);
   delay(DELAY_BETWEEN_STEPS1);
   Down_Right.rmove(place[1] + APERTO);
   Down_Left.rmove(place[1] + APERTO);
   delay(DELAY_BETWEEN_STEPS1);
   Down_Front.rmove(place[3]);
   Down_Back.rmove(place[3]);
   delay(DELAY_BETWEEN_STEPS1);
   Up_Right.Rotate(0);
   Up_Left.Rotate(180);
   */
   //face 2 = Up , delay to 4th face is about 0 seconds
  // Up_Right.Rotate(180);
  // Up_Left.Rotate(0);
   //face 3 = Down , delay to 5th face is about 2 seconds
   /*
   Up_Right.Rotate(90);
   Up_Left.Rotate(90);
   Down_Right.rmove(place[1]);
   Down_Left.rmove(place[1]);
   delay(DELAY_BETWEEN_STEPS1); // 0.5 sec delay
   Down_Back.rmove(place[1]);
   Down_Front.rmove(place[1]);
   delay(DELAY_BETWEEN_STEPS1); // 0.5 sec delay
   ServosCube_MoveZ();
   clearVision(); // 1 sec delay
   */
  //face 4 = front , delay to 6th face is about 0 seconds
 //  Up_Back.Rotate(180);
 //  Up_Front.Rotate(0);
   //face 5 = back , final face
   /*
   Up_Back.Rotate(90);
   Up_Front.Rotate(90);
   Down_Front.rmove(place[1]);
   Down_Back.rmove(place[1]);
   delay(DELAY_BETWEEN_STEPS1);
   Down_Left.rmove(place[1]);
   Down_Right.rmove(place[1]);
   delay(DELAY_BETWEEN_STEPS1);
   ServosCube_Movez();
   delay(DELAY_BETWEEN_STEPS1);
   */
}
