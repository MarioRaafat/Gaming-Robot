#include <Servo.h>

enum Rubik_Faces {
    RF_FRONT,   //0 BLUE
    RF_UP,      //1 WHITE
    RF_LEFT,    //2 ORANGE
    RF_RIGHT,   //3 RED
    RF_DOWN,    //4 YELLOW
    RF_BACK,    //5 GREEN
    RF_TOTAL_FACES, //6 (Total number of faces)
};

String solution_String = "null";
