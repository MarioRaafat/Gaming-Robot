void AUF();

void Solve_PLL() {
  int state = -1;
  // PLL Skip________________________________________________________________
  // Check if all edges are already solved (PLL skip case)
  if((Rubik[RF_FRONT][6] == Rubik[RF_FRONT][7]) && (Rubik[RF_FRONT][7] == Rubik[RF_FRONT][8]) &&
     (Rubik[RF_LEFT][6] == Rubik[RF_LEFT][7]) && (Rubik[RF_LEFT][7] == Rubik[RF_LEFT][8]) &&
     (Rubik[RF_BACK][6] == Rubik[RF_BACK][7]) && (Rubik[RF_BACK][7] == Rubik[RF_BACK][8]) && 
     (Rubik[RF_RIGHT][6] == Rubik[RF_RIGHT][7]) && (Rubik[RF_RIGHT][7] == Rubik[RF_RIGHT][8])){
        state = 0; // PLL skip, no need to execute any algorithm
  } else {
    // Iterate through 4 rotations to check for PLL cases
    for(int i = 0; i < 4; i++){
      // Cases with headlights on the left (most cases)___________________________________
      if(Rubik[RF_LEFT][6] == Rubik[RF_LEFT][8] &&
         Rubik[RF_FRONT][6] != Rubik[RF_FRONT][8]){
        // T Permutation:
        if(Rubik[RF_FRONT][6] == Rubik[RF_FRONT][7] &&
           Rubik[RF_BACK][7] == Rubik[RF_BACK][8]){
            rubik.RotateStr("RUrurFRRuruRUrf"); 
            state = 1;
            break; 
        } 
        // F Permutation:
        else if(Rubik[RF_LEFT][7] == Rubik[RF_LEFT][6] &&
               (Rubik[RF_FRONT][8] == Rubik[RF_BACK][6]) && (Rubik[RF_BACK][6] == Rubik[RF_RIGHT][7])){
                  rubik.RotateStr("rufRUrurFRRuruRUrUR");  
                  state = 2;
                  break;
        }
        // A Permutation (Clockwise):
        else if(Rubik[RF_FRONT][7] == Rubik[RF_FRONT][8] &&
                Rubik[RF_RIGHT][6] == Rubik[RF_RIGHT][7]){
                  rubik.RotateStr("UrFrBBRfrBBrr"); 
                  state = 3;
                  break;
        }
        // A Permutation (Counter-Clockwise):
        else if(Rubik[RF_RIGHT][7] == Rubik[RF_RIGHT][8] &&
                Rubik[RF_BACK][6] == Rubik[RF_BACK][7]){
                  rubik.RotateStr("uRbRffrBRffRR");
                  state = 4;
                  break;
        }
        // Ra Permutation:
        else if(Rubik[RF_FRONT][6] == Rubik[RF_FRONT][7] &&
               (Rubik[RF_FRONT][8] == Rubik[RF_BACK][6]) && (Rubik[RF_BACK][6] == Rubik[RF_RIGHT][7])){
                  rubik.RotateStr("RUrfRUUrUUrFRURuur"); 
                  state = 5;
                  break;
        }
        // Rb Permutation:
        else if(Rubik[RF_BACK][7] == Rubik[RF_BACK][8] &&
               (Rubik[RF_FRONT][8] == Rubik[RF_BACK][6]) && (Rubik[RF_BACK][6] == Rubik[RF_RIGHT][7])){
                  rubik.RotateStr("urUUrdRurDRURuruR");  
                  state = 6;
                  break;
        }
        // Ja Permutation:
        else if(Rubik[RF_FRONT][6] == Rubik[RF_FRONT][7] &&
                Rubik[RF_RIGHT][6] == Rubik[RF_RIGHT][7] &&
                Rubik[RF_BACK][6] == Rubik[RF_BACK][7] &&
                Rubik[RF_LEFT][6] == Rubik[RF_LEFT][8]){
                  rubik.RotateStr("UUluLFluLULfllUL"); 
                  state = 7;
                  break;
        }
        // Jb Permutation:
        else if(Rubik[RF_FRONT][7] == Rubik[RF_FRONT][8] &&
                Rubik[RF_RIGHT][7] == Rubik[RF_RIGHT][8] &&
                Rubik[RF_BACK][7] == Rubik[RF_BACK][8] &&
                Rubik[RF_LEFT][6] == Rubik[RF_LEFT][8]){
                  rubik.RotateStr("RUUruRUUlUruL"); 
                  state = 8;
                  break;
        }
        // G1 Permutation:
        else if(Rubik[RF_FRONT][7] == Rubik[RF_FRONT][8]){
                  rubik.RotateStr("dRRUrUruRuRRuDrUR");  
                  state = 9;
                  break;
        }
        // G2 Permutation:
        else if(Rubik[RF_BACK][6] == Rubik[RF_BACK][7]){
                  rubik.RotateStr("DRRuRuRUrUrrUdRur");  
                  state = 10;
                  break;
        }
        // G3 Permutation:
        else if(Rubik[RF_RIGHT][6] == Rubik[RF_RIGHT][7]){
                  rubik.RotateStr("RUruDRRuRurUrUrrd");  
                  state = 11;
                  break;
        }
        // G4 Permutation:
        else if(Rubik[RF_RIGHT][7] == Rubik[RF_RIGHT][8]){
                  rubik.RotateStr("DruRUdRRUrURuRurr");  
                  state = 12;
                  break;
        }
      }
      // Cases without headlights:___________________________________________________
      // Y Permutation:
      if(Rubik[RF_FRONT][6] == Rubik[RF_FRONT][7] &&
         Rubik[RF_RIGHT][7] == Rubik[RF_RIGHT][8] &&
         Rubik[RF_FRONT][8] == Rubik[RF_BACK][6]){
           rubik.RotateStr("FUfrrFufuRRUrrURR");
            state = 13;
           break;       
      } 
      // V Permutation:
      else if(Rubik[RF_FRONT][6] == Rubik[RF_FRONT][7] &&
              Rubik[RF_LEFT][7] == Rubik[RF_LEFT][8]   &&
              Rubik[RF_FRONT][8] == Rubik[RF_BACK][6] &&
              Rubik[RF_RIGHT][6] != Rubik[RF_RIGHT][7]){
                rubik.RotateStr("rUURuuLurUlULuRUl"); 
                state = 14;
                break; 
      } 
      // E Permutation:
      else if((Rubik[RF_FRONT][7] == RC_RED)   && (Rubik[RF_LEFT][7] == RC_BLUE)   &&
              (Rubik[RF_BACK][7] == RC_ORANGE) && (Rubik[RF_RIGHT][7] == RC_GREEN) &&
              (Rubik[RF_FRONT][8] == Rubik[RF_BACK][6])){
                rubik.RotateStr("rUlddLuRlUrDDRuL"); 
                state = 15;
                break; 
      }
      // Rare Case 1:
      else if(Rubik[RF_LEFT][7] == Rubik[RF_LEFT][8]    &&
              Rubik[RF_BACK][7] == Rubik[RF_BACK][8]   &&
              Rubik[RF_RIGHT][7] == Rubik[RF_RIGHT][8] &&
              Rubik[RF_FRONT][7] == Rubik[RF_FRONT][8] &&
              Rubik[RF_RIGHT][6] != Rubik[RF_RIGHT][8] &&
              Rubik[RF_FRONT][6] != Rubik[RF_FRONT][8] &&
              Rubik[RF_BACK][6] != Rubik[RF_BACK][8] &&
              Rubik[RF_LEFT][6] != Rubik[RF_LEFT][8]){
                rubik.RotateStr("LuRUUlUrLuRuulUr");
                state = 16;
                break; 
      } 
      // Rare Case 2:
      else if(Rubik[RF_LEFT][6] == Rubik[RF_LEFT][7]    &&
              Rubik[RF_BACK][6] == Rubik[RF_BACK][7]   &&
              Rubik[RF_RIGHT][6] == Rubik[RF_RIGHT][7] &&
              Rubik[RF_FRONT][6] == Rubik[RF_FRONT][7] &&
              Rubik[RF_RIGHT][6] != Rubik[RF_RIGHT][8] &&
              Rubik[RF_FRONT][6] != Rubik[RF_FRONT][8] &&
              Rubik[RF_BACK][6] != Rubik[RF_BACK][8] &&
              Rubik[RF_LEFT][6] != Rubik[RF_LEFT][8]){
                rubik.RotateStr("lUrUULuRlUrUULuR"); 
                state = 17;
                break; 
      }
      // Cases with headlights on all faces________________________________________
      if(Rubik[RF_LEFT][6] == Rubik[RF_LEFT][8]   &&
         Rubik[RF_BACK][6] == Rubik[RF_BACK][8]   &&
         Rubik[RF_RIGHT][6] == Rubik[RF_RIGHT][8] &&
         Rubik[RF_FRONT][6] == Rubik[RF_FRONT][8]){
        // U Permutation (Clockwise):
        if(Rubik[RF_FRONT][7] == Rubik[RF_FRONT][6] &&
           Rubik[RF_LEFT][7] == Rubik[RF_BACK][8]){
            rubik.RotateStr("rUrururURUrr"); 
            state = 18;
            break; 
        }
        // U Permutation (Counter-Clockwise):
        else if(Rubik[RF_FRONT][7] == Rubik[RF_FRONT][6] &&
                Rubik[RF_LEFT][7] == Rubik[RF_RIGHT][8]){
            rubik.RotateStr("LuLULULuluLL"); 
            state = 19;
            break; 
        }
        // H Permutation:
        else if(Rubik[RF_FRONT][7] == Rubik[RF_BACK][6] &&
                Rubik[RF_LEFT][7] == Rubik[RF_RIGHT][6]){
                  rubik.RotateStr("rrUURuuRRuuRRuuRUUrr"); 
                  state = 20;
                  break; 
        }
        // Z Permutation:
        else if(Rubik[RF_FRONT][7] == Rubik[RF_RIGHT][6] &&
                Rubik[RF_LEFT][7] == Rubik[RF_BACK][6]){
                  rubik.RotateStr("RUrUrurURuruRRUR");  
                  state = 21;
                  break; 
        }
      } 
      // Rotate the cube to check the next side
      rubik.RotateStr("u");
    }
  }
//  Serial.println  state);
//  Serial.flush();

  // Adjust the Up Face (AUF) to align the cube correctly
  AUF();
}


void AUF() {               // A.U.F. (Adjust Up Face)
  // Align the front face with the correct color
  switch(Rubik[RF_FRONT][7]){
    case RC_RED:    
      rubik.RotateStr(""); // No rotation needed
      break;
    case RC_BLUE:   
      rubik.RotateStr("U");  // Rotate once
      break;
    case RC_ORANGE: 
      rubik.RotateStr("uu");   // Rotate twice
      break;
    case RC_GREEN:  
      rubik.RotateStr("u");  // Rotate counter-clockwise
      break;
  }
}