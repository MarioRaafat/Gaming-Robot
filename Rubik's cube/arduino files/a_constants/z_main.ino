void setup() {
  pwm.begin();
  pwm.setPWMFreq(60);
  //intializes servo positions
  servos_init();
  //Serial recieved data at baud rate 9600
  Serial.begin(9600); 
  // 2 seconds delay to give process time
  delay(2000);
  //Set intial colors;
  rubik.Init();
  // read cube colors
  // Wait for first signal to read the cube
  while(Serial.available() == 0) {} 
  Read_Cube();
  // print recieved colors
  rubik.Print();
  //servos_test();
  //Menu_Print();
}

void loop() {
  //Menu_Process();
  //servos_test();
  Serial.print(F("Solving the cube.")); delay(600);
  Serial.print(F(".")); delay(600);
  Serial.print(F(".")); delay(800); Serial.print(F("\n"));
  Serial.print(F("\n")); Serial.print(F("Moves to solve the cube: ")); Serial.print(F("\n"));
  rubik.SolveSequence();
  servos_init();
  rubik.Print();
  while(true){}
}
