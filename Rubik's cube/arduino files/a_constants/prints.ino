#define PRINT_WITH_COLORS (false)

/*
void Rubik_PrintColor (int color) {
  if(PRINT_WITH_COLORS) {
    switch (color) {
      case RC_RED:    Serial.print("\e[0;31m"); break;
      case RC_YELLOW: Serial.print("\e[1;33m"); break;
      case RC_BLUE:   Serial.print("\e[0;34m"); break;
      case RC_GREEN:  Serial.print("\e[0;32m"); break;
      case RC_WHITE:  Serial.print("\e[0;37m"); break;
      case RC_ORANGE: Serial.print("\e[0;35m"); break;
    }
    Serial.print("# ");
    Serial.print("\e[0m");
  } else {
      switch (color) {
        case RC_RED:    Serial.print("R"); break;
        case RC_YELLOW: Serial.print("Y"); break;
        case RC_BLUE:   Serial.print("B"); break;
        case RC_GREEN:  Serial.print("G"); break;
        case RC_WHITE:  Serial.print("W"); break;
        case RC_ORANGE: Serial.print("O"); break;
    }
  }
  Serial.flush();
}

void Rubik_PrintSpace () {
  Serial.print("   ");
}

void Rubik_PrintLineFeed () {
  Serial.write("\n");
}

void Cubo::Print() {

  Serial.print("Saved colors from cube:");
  for (int face = 0; face < RF_TOTAL_FACES; face ++) {
    for (int i = 0; i < 9; i++) {
        // get corresponding face color
        int color = Rubik_FaceToColorLUT[face];
        Serial.print(Rubik[face][i]);
    }
  }
}
*/
