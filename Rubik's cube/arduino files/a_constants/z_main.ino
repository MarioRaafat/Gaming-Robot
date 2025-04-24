#include <Servo.h>

void setup() {
  Serial.begin(9600);
  // pwm.begin();
  // pwm.setPWMFreq(60);
  
  //intialize servo positions
  servos_init();

  //initialize dc motors
  init_dc_motors();
// putTheCube();
// delay(20000);
// CatchTheCube();
  // get_solution_string();
  const String solution_String= "RR'FF'LL'BB'";
  //
 // move_dc_motor('B',2);
 // delay(1000);
  //move_dc_motor('B',1);
    //delay(1000);
   // move_dc_motor('F',2);
   //   delay(1000);
  //move_dc_motor('F',1);
  analyze_moves(solution_String);
}

void loop() {

}
void putTheCube(){
    move_dc_motor('B',1);
  delay(1000);
  move_dc_motor('B',2);
   delay(1000);
   move_dc_motor('B',3);
  delay(1000);
  move_dc_motor('B',4);
  }
void CatchTheCube(){
    move_dc_motor('F',1);
  delay(1000);
  move_dc_motor('F',2);
   delay(1000);
   move_dc_motor('F',3);
  delay(1000);
  move_dc_motor('F',4);
  }
