#include <Servo.h>

void setup() {
  Serial.begin(9600);
  // pwm.begin();
  // pwm.setPWMFreq(60);
  
  //intialize servo positions
  servos_init();

  //initialize dc motors
  init_dc_motors();
 
  // get_solution_string();
  const String solution_String= "LBRFR'L'F'B'";
  //
 // move_dc_motor('B',2);
 // delay(1000);
  //move_dc_motor('B',1);
    //delay(1000);
   // move_dc_motor('F',2);
   //   delay(1000);
  //move_dc_motor('F',1);
 // analyze_moves(solution_String);
}

void loop() {

}
