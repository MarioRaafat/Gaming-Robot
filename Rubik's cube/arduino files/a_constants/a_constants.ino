enum Rubik_Faces {
    RF_FRONT,   //0
    RF_UP,      //1
    RF_LEFT,    //2
    RF_RIGHT,   //3
    RF_DOWN,    //4
    RF_BACK,    //5
    RF_TOTAL_FACES, //6 (Total number of faces)
};

enum Rubik_Colors {
    RC_RED, // idx 0
    RC_YELLOW,  // idx 1
    RC_BLUE,  // idx 2
    RC_GREEN, // idx 3
    RC_WHITE, // idx 4
    RC_ORANGE,  // idx 5
    RC_TOTAL_COLORS,  // number of colors
};

// array of colors , where each face corresponds to a color
int Rubik_FaceToColorLUT[] = {
    RC_RED, // Front --> Red
    RC_YELLOW,  // UP --> Yellow
    RC_BLUE,  // Left -- > Blue
    RC_GREEN, // Right --> Green
    RC_WHITE, // Down --> White
    RC_ORANGE,// Back --> Orange
};

// 2D-array of 6 faces * 9 colors per face
unsigned char Rubik[RF_TOTAL_FACES][9];
String Cube_Colors = "null";
