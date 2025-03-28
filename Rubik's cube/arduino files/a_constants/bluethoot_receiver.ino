#define S2 2
#define S3 3
#define COLOR_IN1 4
#define COLOR_IN2 5
#define LED1 6
#define LED2 7

unsigned long redFrequency = 0;
unsigned long greenFrequency = 0;
unsigned long blueFrequency = 0;

String Cube_Colors = "null";

void getBit(int currentFace) {  //TODO change where this function is called as get all faces
  
  int sticker = 0;
  if(Cube_Colors == "null"){
    if(Serial.available() > 0)  {
      Cube_Colors = Serial. readStringUntil('\n');
      Cube_Colors.trim();
      Serial.print("Arduino Received ya baby: ");
      Serial.println(Cube_Colors);
      delay(100);
    }
  }  

  if(Cube_Colors != "null"){

    while(sticker < 9) {
      int color = 0;
      switch(Cube_Colors[currentFace*9 + sticker]) {
        case 'G':
          color = RC_GREEN;
          break;
        case 'R':
          color = RC_RED;
          break;
        case 'B':
          color = RC_BLUE;
          break;
        case 'Y':
          color = RC_YELLOW;
          break;
        case 'W':
          color = RC_WHITE;
          break;
        case 'O':
          color = RC_ORANGE;
          break;
        default:
          //Serial.print("Erro + \'");
          //Serial.print(Cube_Colors);
          Serial.print("\'");
      }
      if(Cube_Colors == 'G') {
        color = RC_GREEN;
      }
      Rubik[currentFace][sticker++] = color;
    }      
  }
}

void lightAnimation() {
  
  for(int i = 0; i < 8; i++) {
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, LOW);
    delay(200);
    digitalWrite(LED1, HIGH);
    digitalWrite(LED2, HIGH);
    delay(200);
  }
}
