#include <avr/pgmspace.h>

#define ProgStrArray_Index(prog_str_array, i)  (char*)pgm_read_word(&(prog_str_array[i]))

class Cubo {
  public:
    Cubo() {
      
    }
    void Init() {
      int face;
      int i;
      // loop on all faces, intialize each face with it's colors as it is already solved
      for (face = 0; face < RF_TOTAL_FACES; face ++) {
        for (i = 0; i < 9; i++) {
            // get corresponding face color
            int color = Rubik_FaceToColorLUT[face];
            Rubik[face][i] = color;
        }
      }
    }

    void Print();

    
void Rubik_Rotate(char rot, bool motorsMove) {
 // static char storeMove;
  bool MotorRotate = motorsMove;
  switch(rot) {
    case 'f':  
      RotateFrontCCW();  
      if(MotorRotate == true){
        ServosCube_Movex();
        ServosFace_BackCCW();
        ServosCube_MoveX();
      } 
      Serial.print(F("F'"));
      break;
    case 'F':  
      RotateFrontCW();
      if(MotorRotate == true){
        ServosCube_Movex();
        ServosFace_BackCW();
        ServosCube_MoveX(); 
      }   
      Serial.print(F("F")); 
      break;
    case 'r':  
      RotateRightCCW();
      if(MotorRotate == true){ 
        ServosFace_RightCCW();  
      }  
      Serial.print(F("R'"));
      break;
    case 'R':  
      RotateRightCW(); 
      if(MotorRotate == true){
        ServosFace_RightCW();  
      }  
      Serial.print(F("R"));  
      break;
    case 'u':  
      RotateUpCCW();
      if(MotorRotate == true){     
        ServosFace_FrontCW();
      }
      Serial.print(F("U'"));
      break;
    case 'U': 
      RotateUpCW(); 
      if(MotorRotate == true){     
        ServosFace_FrontCCW(); 
      }   
      Serial.print(F("U")); 
      break;
    case 'l':  
      RotateLeftCCW(); 
      if(MotorRotate == true){ 
        ServosFace_LeftCW();  
      }   
      Serial.print(F("L'"));
      break;
    case 'L':  
      RotateLeftCW();
      if(MotorRotate == true){
        ServosFace_LeftCCW();     
      }   
      Serial.print(F("L"));
      break;
    case 'd':  
      RotateDownCCW(); 
      if(MotorRotate == true){
        ServosFace_BackCCW();  
      }  
      Serial.print(F("D'")); 
      break;
    case 'D':  
      RotateDownCW(); 
      if(MotorRotate == true){ 
        ServosFace_BackCW();    
      }  
      Serial.print(F("D"));
      break;
    case 'b':  
      RotateBackCCW();  
      if(MotorRotate == true){
        ServosCube_Movex();
        ServosFace_FrontCW();
        ServosCube_MoveX();
      }  
      Serial.print(F("B'")); 
      break;
    case 'B':  
      RotateBackCW();  
      if(MotorRotate == true){  
        ServosCube_Movex();
        ServosFace_FrontCCW();
        ServosCube_MoveX();
      }   
      Serial.print(F("B")); 
      break;
    case 'Y':  
      RotateY();
      if(MotorRotate == true){  
        ServosCube_MoveZ();
      }  
      if((HTM > 0) && (QTM > 0)) {
        HTM--;  QTM--;
      }  
      break;
  }
  if(MotorRotate == true){  
    Print();
  }
}


  void RotateStr(String sequence) {
  
    for (int i = 0; i < sequence.length(); i++) {
      Rubik_Rotate(sequence.charAt(i), false);
      resolutionStr += sequence.charAt(i);
    }
  }

  void RotateStr_Progmem(char *sequence) {
    static char buff[30];
    
    strcpy_P(buff, sequence);
    int len = strlen(buff);
  
    
    for (int i = 0; i < len; i++) {
      Rubik_Rotate(buff[i], false);
      resolutionStr += buff[i];
    }
  }
  // handles the Solution-string to cancels rotations that are reversed 
    void ProcessStr(int caze = 0) {
      bool flag = true;
      while(flag == true) {
        flag = false;
        for(int i = 0; i < resolutionStr.length(); i++) {
          switch(caze) {
            case 0:
              if(resolutionStr[i] == 'r' && resolutionStr[i + 1] == 'R' || resolutionStr[i] == 'R' && resolutionStr[i + 1] == 'r' ||
                resolutionStr[i] == 'l' && resolutionStr[i + 1] == 'L'  || resolutionStr[i] == 'L' && resolutionStr[i + 1] == 'l' ||
                resolutionStr[i] == 'f' && resolutionStr[i + 1] == 'F'  || resolutionStr[i] == 'F' && resolutionStr[i + 1] == 'f' ||
                resolutionStr[i] == 'b' && resolutionStr[i + 1] == 'B'  || resolutionStr[i] == 'B' && resolutionStr[i + 1] == 'b' ||
                resolutionStr[i] == 'u' && resolutionStr[i + 1] == 'U'  || resolutionStr[i] == 'U' && resolutionStr[i + 1] == 'u' ||
                resolutionStr[i] == 'd' && resolutionStr[i + 1] == 'D'  || resolutionStr[i] == 'D' && resolutionStr[i + 1] == 'd') {
                  resolutionStr.remove(i, 2);
                  i++;
                  flag = true;
                  //Serial.print("  C1  "); 
              } else if((resolutionStr[i] == resolutionStr[i + 1]) && (resolutionStr[i] == resolutionStr[i + 2])) {
                  if(isUpperCase(resolutionStr[i])) {
                    resolutionStr[i] = toLowerCase(resolutionStr[i]);
                  } else {
                    resolutionStr[i] = toUpperCase(resolutionStr[i]);
                  }
                  resolutionStr.remove(i + 1, 2);
                  i++;
                  flag = true;
                  //Serial.print("  C2  "); 
              } else if((resolutionStr[i] == resolutionStr[i + 1]) &&  (resolutionStr[i] == resolutionStr[i + 2]) && (resolutionStr[i] == resolutionStr[i + 3])) {
                resolutionStr.remove(i, 4);
                i++;
                flag = true;
                //Serial.print("  C3  "); 
              }
              break;
            case 1:
              if(resolutionStr[i] == 'r' && resolutionStr[i + 1] == 'r' || resolutionStr[i] == 'R' && resolutionStr[i + 1] == 'R' ||
                resolutionStr[i] == 'l' && resolutionStr[i + 1] == 'l'  || resolutionStr[i] == 'L' && resolutionStr[i + 1] == 'L' ||
                resolutionStr[i] == 'f' && resolutionStr[i + 1] == 'F'  || resolutionStr[i] == 'F' && resolutionStr[i + 1] == 'F' ||
                resolutionStr[i] == 'b' && resolutionStr[i + 1] == 'b'  || resolutionStr[i] == 'B' && resolutionStr[i + 1] == 'B' ||
                resolutionStr[i] == 'u' && resolutionStr[i + 1] == 'u'  || resolutionStr[i] == 'U' && resolutionStr[i + 1] == 'U' ||
                resolutionStr[i] == 'd' && resolutionStr[i + 1] == 'd'  || resolutionStr[i] == 'D' && resolutionStr[i + 1] == 'D') {
                  resolutionStr[i + 1] = '2';
                  i++;
                  flag = true;
                  //Serial.print("  C4  "); 
              } 
              break;
            case 2:
              return;
              break;
            }
          }
          //Serial.print("\nResolução = ");  Serial.print(resolutionStr);  Serial.print(F("\n")); 
       }
       
       //Rubik_ProcessStr(caze + 1);
    }
  
    void SolveSequence() {
      CopyCube(Rubik, Rubik_ToSolve);
      Print();
      delay(1000);
      // solve white cross
      Solve_WhiteCross_1 ();
      Solve_WhiteCross_2 ();
      Solve_WhiteCross_3 ();
      Solve_WhiteCross_4 ();
      Solve_WhiteCross_5 ();
      Solve_WhiteCross_6 ();
      SolveF2L();
      Solve_OLL();
      Solve_PLL();
      ProcessStr();
      CopyCube(Rubik_ToSolve, Rubik);
      for(int i = 0; i < resolutionStr.length(); i++) {
        Rubik_Rotate(resolutionStr.charAt(i), true);
      }
      Serial.print("\nResolution String = ");  Serial.print(resolutionStr);  
      Serial.print(F("\n")); 
      Serial.print("  (HTM = ");  Serial.print(HTM);  Serial.print(F(")")); 
      Serial.print("  (QTM = ");  Serial.print(QTM);  Serial.print(F(")"));  
      Serial.print(F("\n"));
      Print();
    }
  
    void Sramble(int rotations_count) {
      static const char rotations[] = {'f', 'F', 'r', 'R', 'u', 'U', 'l', 'L', 'd', 'D', 'b', 'B'};
      randomSeed(millis()); // Initialize the pseudo-random number generator with a seed based on the current time

      for (int i = 0; i < rotations_count; i++) {
        char i_rot = random(sizeof(rotations)); // Generate a random number between 0 and the number of rotation options (size of the rotations array - 12)
        Rubik_Rotate(rotations[i_rot], false); // Perform the randomly selected rotation on the Rubik's Cube
      }
      Serial.println(F("\n")); // Print a newline for formatting purposes
    }

    void CopyCube(unsigned char de[][9], unsigned char para[][9]) {

      Serial.print(F("A")); 
      for (int face = 0; face < RF_TOTAL_FACES; face ++) {
        for (int i = 0; i < 9; i++) {
            para[face][i] = de[face][i];
        }
      }
    }
    
  private:
    //unsigned char Rubik[RF_TOTAL_FACES][9];
    unsigned char Rubik_Backup[RF_TOTAL_FACES][9];
    unsigned char Rubik_ToSolve[RF_TOTAL_FACES][9];

    String resolutionStr = "";
    
    int QTM;
    int HTM;

  public:
    void RotateRightCW();
    void RotateRightCCW();
    void RotateLeftCW();
    void RotateLeftCCW();
    void RotateUpCW();
    void RotateUpCCW();
    void RotateDownCW();
    void RotateDownCCW();
    void RotateFrontCW();
    void RotateFrontCCW();
    void RotateBackCW();
    void RotateBackCCW();
    void RotateY();

  private:
  // creates a backup version 
    void MakeBackup() {
      int face , i;
      for (face = 0; face < RF_TOTAL_FACES; face++) {
        for (i = 0; i < 9; i++) {
            Rubik_Backup [face][i] = Rubik [face][i];
        }
      }
    }
};

Cubo rubik;

// altering small squares if front is CCW
void Cubo::RotateFrontCCW () {
  MakeBackup(); // Save the current state of the cube to a backup

  // Rotate the corners of the front face counter-clockwise
  Rubik[RF_FRONT][0] = Rubik_Backup[RF_FRONT][6]; // Move bottom-left corner to top-left
  Rubik[RF_FRONT][2] = Rubik_Backup[RF_FRONT][0]; // Move top-left corner to top-right
  Rubik[RF_FRONT][8] = Rubik_Backup[RF_FRONT][2]; // Move top-right corner to bottom-right
  Rubik[RF_FRONT][6] = Rubik_Backup[RF_FRONT][8]; // Move bottom-right corner to bottom-left

  // Rotate the edges of the front face counter-clockwise
  Rubik[RF_FRONT][1] = Rubik_Backup[RF_FRONT][3]; // Move left edge to top edge
  Rubik[RF_FRONT][5] = Rubik_Backup[RF_FRONT][1]; // Move top edge to right edge
  Rubik[RF_FRONT][7] = Rubik_Backup[RF_FRONT][5]; // Move right edge to bottom edge
  Rubik[RF_FRONT][3] = Rubik_Backup[RF_FRONT][7]; // Move bottom edge to left edge

  // Move 3 pieces from the top face to the right face
  Rubik[RF_UP][0] = Rubik_Backup[RF_RIGHT][6]; // Move right bottom-left to top-left
  Rubik[RF_UP][1] = Rubik_Backup[RF_RIGHT][3]; // Move right middle-left to top-middle
  Rubik[RF_UP][2] = Rubik_Backup[RF_RIGHT][0]; // Move right top-left to top-right

  // Move 3 pieces from the right face to the bottom face
  Rubik[RF_RIGHT][6] = Rubik_Backup[RF_DOWN][8]; // Move bottom-right to right bottom-left
  Rubik[RF_RIGHT][3] = Rubik_Backup[RF_DOWN][7]; // Move bottom-middle to right middle-left
  Rubik[RF_RIGHT][0] = Rubik_Backup[RF_DOWN][6]; // Move bottom-left to right top-left

  // Move 3 pieces from the bottom face to the left face
  Rubik[RF_DOWN][8] = Rubik_Backup[RF_LEFT][2]; // Move left top-right to bottom-right
  Rubik[RF_DOWN][7] = Rubik_Backup[RF_LEFT][5]; // Move left middle-right to bottom-middle
  Rubik[RF_DOWN][6] = Rubik_Backup[RF_LEFT][8]; // Move left bottom-right to bottom-left

  // Move 3 pieces from the left face to the top face
  Rubik[RF_LEFT][2] = Rubik_Backup[RF_UP][0]; // Move top-left to left top-right
  Rubik[RF_LEFT][5] = Rubik_Backup[RF_UP][1]; // Move top-middle to left middle-right
  Rubik[RF_LEFT][8] = Rubik_Backup[RF_UP][2]; // Move top-right to left bottom-right
}

void Cubo::RotateFrontCW () {
  MakeBackup(); // Save the current state of the cube to a backup

  // Rotate the corners of the front face clockwise
  Rubik[RF_FRONT][0] = Rubik_Backup[RF_FRONT][2]; // Move top-right corner to top-left
  Rubik[RF_FRONT][2] = Rubik_Backup[RF_FRONT][8]; // Move bottom-right corner to top-right
  Rubik[RF_FRONT][8] = Rubik_Backup[RF_FRONT][6]; // Move bottom-left corner to bottom-right
  Rubik[RF_FRONT][6] = Rubik_Backup[RF_FRONT][0]; // Move top-left corner to bottom-left

  // Rotate the edges of the front face clockwise
  Rubik[RF_FRONT][1] = Rubik_Backup[RF_FRONT][5]; // Move right edge to top edge
  Rubik[RF_FRONT][5] = Rubik_Backup[RF_FRONT][7]; // Move bottom edge to right edge
  Rubik[RF_FRONT][7] = Rubik_Backup[RF_FRONT][3]; // Move left edge to bottom edge
  Rubik[RF_FRONT][3] = Rubik_Backup[RF_FRONT][1]; // Move top edge to left edge

  // Move 3 pieces from the top face to the left face
  Rubik[RF_UP][0] = Rubik_Backup[RF_LEFT][2]; // Move left top-right to top-left
  Rubik[RF_UP][1] = Rubik_Backup[RF_LEFT][5]; // Move left middle-right to top-middle
  Rubik[RF_UP][2] = Rubik_Backup[RF_LEFT][8]; // Move left bottom-right to top-right

  // Move 3 pieces from the left face to the bottom face
  Rubik[RF_LEFT][2] = Rubik_Backup[RF_DOWN][8]; // Move bottom-right to left top-right
  Rubik[RF_LEFT][5] = Rubik_Backup[RF_DOWN][7]; // Move bottom-middle to left middle-right
  Rubik[RF_LEFT][8] = Rubik_Backup[RF_DOWN][6]; // Move bottom-left to left bottom-right

  // Move 3 pieces from the bottom face to the right face
  Rubik[RF_DOWN][8] = Rubik_Backup[RF_RIGHT][6]; // Move right bottom-left to bottom-right
  Rubik[RF_DOWN][7] = Rubik_Backup[RF_RIGHT][3]; // Move right middle-left to bottom-middle
  Rubik[RF_DOWN][6] = Rubik_Backup[RF_RIGHT][0]; // Move right top-left to bottom-left

  // Move 3 pieces from the right face to the top face
  Rubik[RF_RIGHT][6] = Rubik_Backup[RF_UP][0]; // Move top-left to right bottom-left
  Rubik[RF_RIGHT][3] = Rubik_Backup[RF_UP][1]; // Move top-middle to right middle-left
  Rubik[RF_RIGHT][0] = Rubik_Backup[RF_UP][2]; // Move top-right to right top-left
}

// Right face rotations
//________________________________________________________________
void Cubo::RotateRightCW () {
  MakeBackup(); // Save the current state of the cube to a backup

  // Rotate the corners of the right face clockwise
  Rubik[RF_RIGHT][0] = Rubik_Backup[RF_RIGHT][2]; // Move top-right corner to top-left
  Rubik[RF_RIGHT][2] = Rubik_Backup[RF_RIGHT][8]; // Move bottom-right corner to top-right
  Rubik[RF_RIGHT][8] = Rubik_Backup[RF_RIGHT][6]; // Move bottom-left corner to bottom-right
  Rubik[RF_RIGHT][6] = Rubik_Backup[RF_RIGHT][0]; // Move top-left corner to bottom-left

  // Rotate the edges of the right face clockwise
  Rubik[RF_RIGHT][1] = Rubik_Backup[RF_RIGHT][5]; // Move right edge to top edge
  Rubik[RF_RIGHT][5] = Rubik_Backup[RF_RIGHT][7]; // Move bottom edge to right edge
  Rubik[RF_RIGHT][7] = Rubik_Backup[RF_RIGHT][3]; // Move left edge to bottom edge
  Rubik[RF_RIGHT][3] = Rubik_Backup[RF_RIGHT][1]; // Move top edge to left edge

  // Move 3 pieces from the top face to the back face
  Rubik[RF_UP][2] = Rubik_Backup[RF_FRONT][2]; // Move front top-left to top-left
  Rubik[RF_UP][5] = Rubik_Backup[RF_FRONT][5]; // Move front middle-right to top-middle
  Rubik[RF_UP][8] = Rubik_Backup[RF_FRONT][8]; // Move front top-right to top-right

  // Move 3 pieces from the back face to the bottom face
  Rubik[RF_BACK][6] = Rubik_Backup[RF_UP][2]; // Move top-left to back bottom-right
  Rubik[RF_BACK][3] = Rubik_Backup[RF_UP][5]; // Move top-middle to back middle-right
  Rubik[RF_BACK][0] = Rubik_Backup[RF_UP][8]; // Move top-right to back top-right

  // Move 3 pieces from the bottom face to the front face
  Rubik[RF_DOWN][2] = Rubik_Backup[RF_BACK][6]; // Move back bottom-right to bottom-left
  Rubik[RF_DOWN][5] = Rubik_Backup[RF_BACK][3]; // Move back middle-right to bottom-middle
  Rubik[RF_DOWN][8] = Rubik_Backup[RF_BACK][0]; // Move back top-right to bottom-right

  // Move 3 pieces from the front face to the top face
  Rubik[RF_FRONT][2] = Rubik_Backup[RF_DOWN][2]; // Move bottom-left to front top-left
  Rubik[RF_FRONT][5] = Rubik_Backup[RF_DOWN][5]; // Move bottom-middle to front middle-right
  Rubik[RF_FRONT][8] = Rubik_Backup[RF_DOWN][8]; // Move bottom-right to front top-right
}

void Cubo::RotateRightCCW () {
  MakeBackup(); // Save the current state of the cube to a backup

  // Rotate the corners of the right face counter-clockwise
  Rubik[RF_RIGHT][0] = Rubik_Backup[RF_RIGHT][6]; // Move bottom-left corner to top-left
  Rubik[RF_RIGHT][2] = Rubik_Backup[RF_RIGHT][0]; // Move top-left corner to top-right
  Rubik[RF_RIGHT][8] = Rubik_Backup[RF_RIGHT][2]; // Move top-right corner to bottom-right
  Rubik[RF_RIGHT][6] = Rubik_Backup[RF_RIGHT][8]; // Move bottom-right corner to bottom-left

  // Rotate the edges of the right face counter-clockwise
  Rubik[RF_RIGHT][1] = Rubik_Backup[RF_RIGHT][3]; // Move left edge to top edge
  Rubik[RF_RIGHT][5] = Rubik_Backup[RF_RIGHT][1]; // Move top edge to right edge
  Rubik[RF_RIGHT][7] = Rubik_Backup[RF_RIGHT][5]; // Move right edge to bottom edge
  Rubik[RF_RIGHT][3] = Rubik_Backup[RF_RIGHT][7]; // Move bottom edge to left edge

  // Move 3 pieces from the top face to the front face
  Rubik[RF_UP][8] = Rubik_Backup[RF_BACK][0]; // Move back top-right to top-right
  Rubik[RF_UP][5] = Rubik_Backup[RF_BACK][3]; // Move back middle-right to top-middle
  Rubik[RF_UP][2] = Rubik_Backup[RF_BACK][6]; // Move back bottom-right to top-left

  // Move 3 pieces from the front face to the bottom face
  Rubik[RF_FRONT][8] = Rubik_Backup[RF_UP][8]; // Move top-right to front top-right
  Rubik[RF_FRONT][5] = Rubik_Backup[RF_UP][5]; // Move top-middle to front middle-right
  Rubik[RF_FRONT][2] = Rubik_Backup[RF_UP][2]; // Move top-left to front bottom-right

  // Move 3 pieces from the bottom face to the back face
  Rubik[RF_DOWN][8] = Rubik_Backup[RF_FRONT][8]; // Move front top-right to bottom-right
  Rubik[RF_DOWN][5] = Rubik_Backup[RF_FRONT][5]; // Move front middle-right to bottom-middle
  Rubik[RF_DOWN][2] = Rubik_Backup[RF_FRONT][2]; // Move front bottom-right to bottom-left

  // Move 3 pieces from the back face to the top face
  Rubik[RF_BACK][0] = Rubik_Backup[RF_DOWN][8]; // Move bottom-right to back top-right
  Rubik[RF_BACK][3] = Rubik_Backup[RF_DOWN][5]; // Move bottom-middle to back middle-right
  Rubik[RF_BACK][6] = Rubik_Backup[RF_DOWN][2]; // Move bottom-left to back bottom-right
}


// Up faces rotations
//________________________________________________________________
void Cubo::RotateUpCW () {
  MakeBackup(); // Save the current state of the cube to a backup

  // Rotate the corners of the top face clockwise
  Rubik[RF_UP][0] = Rubik_Backup[RF_UP][2]; // Move top-right corner to top-left
  Rubik[RF_UP][2] = Rubik_Backup[RF_UP][8]; // Move bottom-right corner to top-right
  Rubik[RF_UP][8] = Rubik_Backup[RF_UP][6]; // Move bottom-left corner to bottom-right
  Rubik[RF_UP][6] = Rubik_Backup[RF_UP][0]; // Move top-left corner to bottom-left

  // Rotate the edges of the top face clockwise
  Rubik[RF_UP][1] = Rubik_Backup[RF_UP][5]; // Move right edge to top edge
  Rubik[RF_UP][5] = Rubik_Backup[RF_UP][7]; // Move bottom edge to right edge
  Rubik[RF_UP][7] = Rubik_Backup[RF_UP][3]; // Move left edge to bottom edge
  Rubik[RF_UP][3] = Rubik_Backup[RF_UP][1]; // Move top edge to left edge

  // Move 3 pieces from the back face to the right face
  Rubik[RF_BACK][8] = Rubik_Backup[RF_LEFT][8]; // Move left top-right to back top-right
  Rubik[RF_BACK][7] = Rubik_Backup[RF_LEFT][7]; // Move left middle-right to back middle-right
  Rubik[RF_BACK][6] = Rubik_Backup[RF_LEFT][6]; // Move left bottom-right to back bottom-right

  // Move 3 pieces from the right face to the front face
  Rubik[RF_RIGHT][8] = Rubik_Backup[RF_BACK][8]; // Move back top-right to right top-right
  Rubik[RF_RIGHT][7] = Rubik_Backup[RF_BACK][7]; // Move back middle-right to right middle-right
  Rubik[RF_RIGHT][6] = Rubik_Backup[RF_BACK][6]; // Move back bottom-right to right bottom-right

  // Move 3 pieces from the front face to the left face
  Rubik[RF_FRONT][8] = Rubik_Backup[RF_RIGHT][8]; // Move right top-right to front top-right
  Rubik[RF_FRONT][7] = Rubik_Backup[RF_RIGHT][7]; // Move right middle-right to front middle-right
  Rubik[RF_FRONT][6] = Rubik_Backup[RF_RIGHT][6]; // Move right bottom-right to front bottom-right

  // Move 3 pieces from the left face to the back face
  Rubik[RF_LEFT][8] = Rubik_Backup[RF_FRONT][8]; // Move front top-right to left top-right
  Rubik[RF_LEFT][7] = Rubik_Backup[RF_FRONT][7]; // Move front middle-right to left middle-right
  Rubik[RF_LEFT][6] = Rubik_Backup[RF_FRONT][6]; // Move front bottom-right to left bottom-right
}

void Cubo::RotateUpCCW () {
  MakeBackup(); // Save the current state of the cube to a backup

  // Rotate the corners of the top face counter-clockwise
  Rubik[RF_UP][0] = Rubik_Backup[RF_UP][6]; // Move bottom-left corner to top-left
  Rubik[RF_UP][2] = Rubik_Backup[RF_UP][0]; // Move top-left corner to top-right
  Rubik[RF_UP][8] = Rubik_Backup[RF_UP][2]; // Move top-right corner to bottom-right
  Rubik[RF_UP][6] = Rubik_Backup[RF_UP][8]; // Move bottom-right corner to bottom-left

  // Rotate the edges of the top face counter-clockwise
  Rubik[RF_UP][1] = Rubik_Backup[RF_UP][3]; // Move left edge to top edge
  Rubik[RF_UP][5] = Rubik_Backup[RF_UP][1]; // Move top edge to right edge
  Rubik[RF_UP][7] = Rubik_Backup[RF_UP][5]; // Move right edge to bottom edge
  Rubik[RF_UP][3] = Rubik_Backup[RF_UP][7]; // Move bottom edge to left edge

  // Move 3 pieces from the back face to the left face
  Rubik[RF_BACK][6] = Rubik_Backup[RF_RIGHT][6]; // Move right bottom-right to back bottom-right
  Rubik[RF_BACK][7] = Rubik_Backup[RF_RIGHT][7]; // Move right middle-right to back middle-right
  Rubik[RF_BACK][8] = Rubik_Backup[RF_RIGHT][8]; // Move right top-right to back top-right

  // Move 3 pieces from the left face to the front face
  Rubik[RF_LEFT][6] = Rubik_Backup[RF_BACK][6]; // Move back bottom-right to left bottom-right
  Rubik[RF_LEFT][7] = Rubik_Backup[RF_BACK][7]; // Move back middle-right to left middle-right
  Rubik[RF_LEFT][8] = Rubik_Backup[RF_BACK][8]; // Move back top-right to left top-right

  // Move 3 pieces from the front face to the right face
  Rubik[RF_FRONT][6] = Rubik_Backup[RF_LEFT][6]; // Move left bottom-right to front bottom-right
  Rubik[RF_FRONT][7] = Rubik_Backup[RF_LEFT][7]; // Move left middle-right to front middle-right
  Rubik[RF_FRONT][8] = Rubik_Backup[RF_LEFT][8]; // Move left top-right to front top-right

  // Move 3 pieces from the right face to the back face
  Rubik[RF_RIGHT][6] = Rubik_Backup[RF_FRONT][6]; // Move front bottom-right to right bottom-right
  Rubik[RF_RIGHT][7] = Rubik_Backup[RF_FRONT][7]; // Move front middle-right to right middle-right
  Rubik[RF_RIGHT][8] = Rubik_Backup[RF_FRONT][8]; // Move front top-right to right top-right
}

// Left face rotations
//________________________________________________________________
void Cubo::RotateLeftCW () {
  MakeBackup(); // Save the current state of the cube to a backup

  // Rotate the corners of the left face clockwise
  Rubik[RF_LEFT][0] = Rubik_Backup[RF_LEFT][2]; // Move top-right corner to top-left
  Rubik[RF_LEFT][2] = Rubik_Backup[RF_LEFT][8]; // Move bottom-right corner to top-right
  Rubik[RF_LEFT][8] = Rubik_Backup[RF_LEFT][6]; // Move bottom-left corner to bottom-right
  Rubik[RF_LEFT][6] = Rubik_Backup[RF_LEFT][0]; // Move top-left corner to bottom-left

  // Rotate the edges of the left face clockwise
  Rubik[RF_LEFT][3] = Rubik_Backup[RF_LEFT][1]; // Move top edge to left edge
  Rubik[RF_LEFT][1] = Rubik_Backup[RF_LEFT][5]; // Move right edge to top edge
  Rubik[RF_LEFT][5] = Rubik_Backup[RF_LEFT][7]; // Move bottom edge to right edge
  Rubik[RF_LEFT][7] = Rubik_Backup[RF_LEFT][3]; // Move left edge to bottom edge

  // Move 3 pieces from the top face to the front face
  Rubik[RF_UP][6] = Rubik_Backup[RF_BACK][2]; // Move back top-left to top-left
  Rubik[RF_UP][3] = Rubik_Backup[RF_BACK][5]; // Move back middle-left to top-middle
  Rubik[RF_UP][0] = Rubik_Backup[RF_BACK][8]; // Move back bottom-left to top-right

  // Move 3 pieces from the front face to the bottom face
  Rubik[RF_FRONT][6] = Rubik_Backup[RF_UP][6]; // Move top-left to front top-left
  Rubik[RF_FRONT][3] = Rubik_Backup[RF_UP][3]; // Move top-middle to front middle-left
  Rubik[RF_FRONT][0] = Rubik_Backup[RF_UP][0]; // Move top-right to front bottom-left

  // Move 3 pieces from the bottom face to the back face
  Rubik[RF_DOWN][6] = Rubik_Backup[RF_FRONT][6]; // Move front top-left to bottom-left
  Rubik[RF_DOWN][3] = Rubik_Backup[RF_FRONT][3]; // Move front middle-left to bottom-middle
  Rubik[RF_DOWN][0] = Rubik_Backup[RF_FRONT][0]; // Move front bottom-left to bottom-right

  // Move 3 pieces from the back face to the top face
  Rubik[RF_BACK][2] = Rubik_Backup[RF_DOWN][6]; // Move bottom-left to back top-left
  Rubik[RF_BACK][5] = Rubik_Backup[RF_DOWN][3]; // Move bottom-middle to back middle-left
  Rubik[RF_BACK][8] = Rubik_Backup[RF_DOWN][0]; // Move bottom-right to back bottom-left
}

void Cubo::RotateLeftCCW () {
  MakeBackup(); // Save the current state of the cube to a backup

  // Rotate the corners of the left face counter-clockwise
  Rubik[RF_LEFT][0] = Rubik_Backup[RF_LEFT][6]; // Move bottom-left corner to top-left
  Rubik[RF_LEFT][2] = Rubik_Backup[RF_LEFT][0]; // Move top-left corner to top-right
  Rubik[RF_LEFT][8] = Rubik_Backup[RF_LEFT][2]; // Move top-right corner to bottom-right
  Rubik[RF_LEFT][6] = Rubik_Backup[RF_LEFT][8]; // Move bottom-right corner to bottom-left

  // Rotate the edges of the left face counter-clockwise
  Rubik[RF_LEFT][1] = Rubik_Backup[RF_LEFT][3]; // Move left edge to top edge
  Rubik[RF_LEFT][5] = Rubik_Backup[RF_LEFT][1]; // Move top edge to right edge
  Rubik[RF_LEFT][7] = Rubik_Backup[RF_LEFT][5]; // Move right edge to bottom edge
  Rubik[RF_LEFT][3] = Rubik_Backup[RF_LEFT][7]; // Move bottom edge to left edge

  // Move 3 pieces from the top face to the back face
  Rubik[RF_UP][0] = Rubik_Backup[RF_FRONT][0]; // Move front top-right to top-right
  Rubik[RF_UP][3] = Rubik_Backup[RF_FRONT][3]; // Move front middle-right to top-middle
  Rubik[RF_UP][6] = Rubik_Backup[RF_FRONT][6]; // Move front bottom-right to top-left

  // Move 3 pieces from the back face to the bottom face
  Rubik[RF_BACK][8] = Rubik_Backup[RF_UP][0]; // Move top-right to back bottom-right
  Rubik[RF_BACK][5] = Rubik_Backup[RF_UP][3]; // Move top-middle to back middle-right
  Rubik[RF_BACK][2] = Rubik_Backup[RF_UP][6]; // Move top-left to back top-right

  // Move 3 pieces from the bottom face to the front face
  Rubik[RF_DOWN][0] = Rubik_Backup[RF_BACK][8]; // Move back bottom-right to bottom-right
  Rubik[RF_DOWN][3] = Rubik_Backup[RF_BACK][5]; // Move back middle-right to bottom-middle
  Rubik[RF_DOWN][6] = Rubik_Backup[RF_BACK][2]; // Move back top-right to bottom-left

  // Move 3 pieces from the front face to the top face
  Rubik[RF_FRONT][0] = Rubik_Backup[RF_DOWN][0]; // Move bottom-right to front top-right
  Rubik[RF_FRONT][3] = Rubik_Backup[RF_DOWN][3]; // Move bottom-middle to front middle-right
  Rubik[RF_FRONT][6] = Rubik_Backup[RF_DOWN][6]; // Move bottom-left to front bottom-right
}

// Rotation of the bottom face
//________________________________________________________________
void Cubo::RotateDownCW () {
  MakeBackup(); // Save the current state of the cube to a backup

  // Rotate the corners of the bottom face clockwise
  Rubik[RF_DOWN][6] = Rubik_Backup[RF_DOWN][0]; // Move top-left corner to bottom-left
  Rubik[RF_DOWN][8] = Rubik_Backup[RF_DOWN][6]; // Move bottom-left corner to bottom-right
  Rubik[RF_DOWN][2] = Rubik_Backup[RF_DOWN][8]; // Move bottom-right corner to top-right
  Rubik[RF_DOWN][0] = Rubik_Backup[RF_DOWN][2]; // Move top-right corner to top-left

  // Rotate the edges of the bottom face clockwise
  Rubik[RF_DOWN][7] = Rubik_Backup[RF_DOWN][3]; // Move left edge to bottom edge
  Rubik[RF_DOWN][5] = Rubik_Backup[RF_DOWN][7]; // Move bottom edge to right edge
  Rubik[RF_DOWN][1] = Rubik_Backup[RF_DOWN][5]; // Move right edge to top edge
  Rubik[RF_DOWN][3] = Rubik_Backup[RF_DOWN][1]; // Move top edge to left edge

  // Move 3 pieces from the front face to the right face
  Rubik[RF_FRONT][0] = Rubik_Backup[RF_LEFT][0]; // Move left top-left to front top-left
  Rubik[RF_FRONT][1] = Rubik_Backup[RF_LEFT][1]; // Move left middle-left to front middle-left
  Rubik[RF_FRONT][2] = Rubik_Backup[RF_LEFT][2]; // Move left bottom-left to front bottom-left

  // Move 3 pieces from the right face to the back face
  Rubik[RF_RIGHT][0] = Rubik_Backup[RF_FRONT][0]; // Move front top-left to right top-left
  Rubik[RF_RIGHT][1] = Rubik_Backup[RF_FRONT][1]; // Move front middle-left to right middle-left
  Rubik[RF_RIGHT][2] = Rubik_Backup[RF_FRONT][2]; // Move front bottom-left to right bottom-left

  // Move 3 pieces from the back face to the left face
  Rubik[RF_BACK][0] = Rubik_Backup[RF_RIGHT][0]; // Move right top-left to back top-left
  Rubik[RF_BACK][1] = Rubik_Backup[RF_RIGHT][1]; // Move right middle-left to back middle-left
  Rubik[RF_BACK][2] = Rubik_Backup[RF_RIGHT][2]; // Move right bottom-left to back bottom-left

  // Move 3 pieces from the left face to the front face
  Rubik[RF_LEFT][0] = Rubik_Backup[RF_BACK][0]; // Move back top-left to left top-left
  Rubik[RF_LEFT][1] = Rubik_Backup[RF_BACK][1]; // Move back middle-left to left middle-left
  Rubik[RF_LEFT][2] = Rubik_Backup[RF_BACK][2]; // Move back bottom-left to left bottom-left
}
void Cubo::RotateDownCCW () {
  MakeBackup(); // Save the current state of the cube to a backup

  // Rotate the corners of the bottom face counter-clockwise
  Rubik[RF_DOWN][6] = Rubik_Backup[RF_DOWN][8]; // Move bottom-right corner to bottom-left
  Rubik[RF_DOWN][0] = Rubik_Backup[RF_DOWN][6]; // Move bottom-left corner to top-left
  Rubik[RF_DOWN][2] = Rubik_Backup[RF_DOWN][0]; // Move top-left corner to top-right
  Rubik[RF_DOWN][8] = Rubik_Backup[RF_DOWN][2]; // Move top-right corner to bottom-right

  // Rotate the edges of the bottom face counter-clockwise
  Rubik[RF_DOWN][7] = Rubik_Backup[RF_DOWN][5]; // Move right edge to bottom edge
  Rubik[RF_DOWN][3] = Rubik_Backup[RF_DOWN][7]; // Move bottom edge to left edge
  Rubik[RF_DOWN][1] = Rubik_Backup[RF_DOWN][3]; // Move left edge to top edge
  Rubik[RF_DOWN][5] = Rubik_Backup[RF_DOWN][1]; // Move top edge to right edge

  // Move 3 pieces from the front face to the left face
  Rubik[RF_FRONT][2] = Rubik_Backup[RF_RIGHT][2]; // Move right bottom-right to front bottom-right
  Rubik[RF_FRONT][1] = Rubik_Backup[RF_RIGHT][1]; // Move right middle-right to front middle-right
  Rubik[RF_FRONT][0] = Rubik_Backup[RF_RIGHT][0]; // Move right top-right to front top-right

  // Move 3 pieces from the left face to the back face
  Rubik[RF_LEFT][2] = Rubik_Backup[RF_FRONT][2]; // Move front bottom-right to left bottom-right
  Rubik[RF_LEFT][1] = Rubik_Backup[RF_FRONT][1]; // Move front middle-right to left middle-right
  Rubik[RF_LEFT][0] = Rubik_Backup[RF_FRONT][0]; // Move front top-right to left top-right

  // Move 3 pieces from the back face to the right face
  Rubik[RF_BACK][2] = Rubik_Backup[RF_LEFT][2]; // Move left bottom-right to back bottom-right
  Rubik[RF_BACK][1] = Rubik_Backup[RF_LEFT][1]; // Move left middle-right to back middle-right
  Rubik[RF_BACK][0] = Rubik_Backup[RF_LEFT][0]; // Move left top-right to back top-right

  // Move 3 pieces from the right face to the front face
  Rubik[RF_RIGHT][2] = Rubik_Backup[RF_BACK][2]; // Move back bottom-right to right bottom-right
  Rubik[RF_RIGHT][1] = Rubik_Backup[RF_BACK][1]; // Move back middle-right to right middle-right
  Rubik[RF_RIGHT][0] = Rubik_Backup[RF_BACK][0]; // Move back top-right to right top-right
}

// Rotation of the back face
//________________________________________________________________
void Cubo::RotateBackCW () {
  MakeBackup(); // Save the current state of the cube to a backup

  // Rotate the corners of the back face clockwise
  Rubik[RF_BACK][0] = Rubik_Backup[RF_BACK][2]; // Move top-right corner to top-left
  Rubik[RF_BACK][6] = Rubik_Backup[RF_BACK][0]; // Move top-left corner to bottom-left
  Rubik[RF_BACK][8] = Rubik_Backup[RF_BACK][6]; // Move bottom-left corner to bottom-right
  Rubik[RF_BACK][2] = Rubik_Backup[RF_BACK][8]; // Move bottom-right corner to top-right

  // Rotate the edges of the back face clockwise
  Rubik[RF_BACK][1] = Rubik_Backup[RF_BACK][5]; // Move right edge to top edge
  Rubik[RF_BACK][3] = Rubik_Backup[RF_BACK][1]; // Move top edge to left edge
  Rubik[RF_BACK][7] = Rubik_Backup[RF_BACK][3]; // Move left edge to bottom edge
  Rubik[RF_BACK][5] = Rubik_Backup[RF_BACK][7]; // Move bottom edge to right edge

  // Move 3 pieces from the top face to the right face
  Rubik[RF_UP][8] = Rubik_Backup[RF_RIGHT][2]; // Move right top-right to top-right
  Rubik[RF_UP][7] = Rubik_Backup[RF_RIGHT][5]; // Move right middle-right to top-middle
  Rubik[RF_UP][6] = Rubik_Backup[RF_RIGHT][8]; // Move right bottom-right to top-left

  // Move 3 pieces from the right face to the bottom face
  Rubik[RF_LEFT][6] = Rubik_Backup[RF_UP][8]; // Move top-right to left bottom-right
  Rubik[RF_LEFT][3] = Rubik_Backup[RF_UP][7]; // Move top-middle to left middle-right
  Rubik[RF_LEFT][0] = Rubik_Backup[RF_UP][6]; // Move top-left to left top-right

  // Move 3 pieces from the bottom face to the left face
  Rubik[RF_DOWN][0] = Rubik_Backup[RF_LEFT][6]; // Move left bottom-right to bottom-left
  Rubik[RF_DOWN][1] = Rubik_Backup[RF_LEFT][3]; // Move left middle-right to bottom-middle
  Rubik[RF_DOWN][2] = Rubik_Backup[RF_LEFT][0]; // Move left top-right to bottom-right

  // Move 3 pieces from the left face to the top face
  Rubik[RF_RIGHT][2] = Rubik_Backup[RF_DOWN][0]; // Move bottom-left to right top-right
  Rubik[RF_RIGHT][5] = Rubik_Backup[RF_DOWN][1]; // Move bottom-middle to right middle-right
  Rubik[RF_RIGHT][8] = Rubik_Backup[RF_DOWN][2]; // Move bottom-right to right bottom-right
}

void Cubo::RotateBackCCW () {
  MakeBackup(); // Save the current state of the cube to a backup

  // Rotate the corners of the back face counter-clockwise
  Rubik[RF_BACK][0] = Rubik_Backup[RF_BACK][6]; // Move bottom-left corner to top-left
  Rubik[RF_BACK][2] = Rubik_Backup[RF_BACK][0]; // Move top-left corner to top-right
  Rubik[RF_BACK][8] = Rubik_Backup[RF_BACK][2]; // Move top-right corner to bottom-right
  Rubik[RF_BACK][6] = Rubik_Backup[RF_BACK][8]; // Move bottom-right corner to bottom-left

  // Rotate the edges of the back face counter-clockwise
  Rubik[RF_BACK][1] = Rubik_Backup[RF_BACK][3]; // Move left edge to top edge
  Rubik[RF_BACK][5] = Rubik_Backup[RF_BACK][1]; // Move top edge to right edge
  Rubik[RF_BACK][7] = Rubik_Backup[RF_BACK][5]; // Move right edge to bottom edge
  Rubik[RF_BACK][3] = Rubik_Backup[RF_BACK][7]; // Move bottom edge to left edge

  // Move 3 pieces from the top face to the left face
  Rubik[RF_UP][6] = Rubik_Backup[RF_LEFT][0]; // Move left top-right to top-left
  Rubik[RF_UP][7] = Rubik_Backup[RF_LEFT][3]; // Move left middle-right to top-middle
  Rubik[RF_UP][8] = Rubik_Backup[RF_LEFT][6]; // Move left bottom-right to top-right

  // Move 3 pieces from the left face to the bottom face
  Rubik[RF_RIGHT][8] = Rubik_Backup[RF_UP][6]; // Move top-left to right bottom-right
  Rubik[RF_RIGHT][5] = Rubik_Backup[RF_UP][7]; // Move top-middle to right middle-right
  Rubik[RF_RIGHT][2] = Rubik_Backup[RF_UP][8]; // Move top-right to right top-right

  // Move 3 pieces from the bottom face to the right face
  Rubik[RF_DOWN][2] = Rubik_Backup[RF_RIGHT][8]; // Move right bottom-right to bottom-right
  Rubik[RF_DOWN][1] = Rubik_Backup[RF_RIGHT][5]; // Move right middle-right to bottom-middle
  Rubik[RF_DOWN][0] = Rubik_Backup[RF_RIGHT][2]; // Move right top-right to bottom-left

  // Move 3 pieces from the right face to the top face
  Rubik[RF_LEFT][0] = Rubik_Backup[RF_DOWN][2]; // Move bottom-right to left top-right
  Rubik[RF_LEFT][3] = Rubik_Backup[RF_DOWN][1]; // Move bottom-middle to left middle-right
  Rubik[RF_LEFT][6] = Rubik_Backup[RF_DOWN][0]; // Move bottom-left to left bottom-right
}

void Cubo::RotateY() {
  RotateUpCCW (); // Rotate the top face counter-clockwise
  RotateDownCW (); // Rotate the bottom face clockwise
  MakeBackup(); // Save the current state of the cube to a backup

  // Move the entire middle layer of the cube
  Rubik[RF_FRONT][5] = Rubik_Backup[RF_LEFT][5]; // Move left middle-right to front middle-right
  Rubik[RF_FRONT][4] = Rubik_Backup[RF_LEFT][4]; // Move left middle-center to front middle-center
  Rubik[RF_FRONT][3] = Rubik_Backup[RF_LEFT][3]; // Move left middle-left to front middle-left
  Rubik[RF_LEFT][5] = Rubik_Backup[RF_BACK][5]; // Move back middle-right to left middle-right
  Rubik[RF_LEFT][4] = Rubik_Backup[RF_BACK][4]; // Move back middle-center to left middle-center
  Rubik[RF_LEFT][3] = Rubik_Backup[RF_BACK][3]; // Move back middle-left to left middle-left
  Rubik[RF_BACK][5] = Rubik_Backup[RF_RIGHT][5]; // Move right middle-right to back middle-right
  Rubik[RF_BACK][4] = Rubik_Backup[RF_RIGHT][4]; // Move right middle-center to back middle-center
  Rubik[RF_BACK][3] = Rubik_Backup[RF_RIGHT][3]; // Move right middle-left to back middle-left
  Rubik[RF_RIGHT][5] = Rubik_Backup[RF_FRONT][5]; // Move front middle-right to right middle-right
  Rubik[RF_RIGHT][4] = Rubik_Backup[RF_FRONT][4]; // Move front middle-center to right middle-center
  Rubik[RF_RIGHT][3] = Rubik_Backup[RF_FRONT][3]; // Move front middle-left to right middle-left
}
 
  
