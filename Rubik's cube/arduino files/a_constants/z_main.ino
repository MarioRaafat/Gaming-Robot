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
  const String solution_String= "LL'";
  //
  
  analyze_moves(solution_String);
}

void loop() {

}
