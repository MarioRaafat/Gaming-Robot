#include <Servo.h>

void setup() {
  Serial.begin(9600);
  // pwm.begin();
  // pwm.setPWMFreq(60);
  
  //intializes servo positions
  servos_init();
 
  get_solution_string();

  analyze_moves(solution_String);
}

void loop() {

}
