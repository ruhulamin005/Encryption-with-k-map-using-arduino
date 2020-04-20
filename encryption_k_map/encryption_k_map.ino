/*
 * Truth Table:
 * ---------------------------------
 *    Inputs       |       Outputs
 * I3 I2 I1 I0     |     O3 O2 O1 O0
 *  0  0  0  0     |      0  1  0  1
 *  1  0  0  0     |      1  1  0  0
 *  0  1  0  0     |      1  1  1  0
 *  1  1  0  0     |      0  0  0  1
 * ---------------------------------
 *  0  0  1  0     |      0  1  1  1
 *  1  0  1  0     |      0  0  1  0
 *  0  1  1  0     |      0  1  1  0
 *  1  1  1  0     |      0  1  0  0
 * ---------------------------------
 *  0  0  0  1     |      1  1  0  0
 *  1  0  0  1     |      0  0  0  0
 *  0  1  0  1     |      0  1  1  0
 *  1  1  0  1     |      1  0  1  1
 * ---------------------------------
 *  0  0  1  1     |      0  0  0  0
 *  1  0  1  1     |      0  0  1  1
 *  0  1  1  1     |      1  0  1  1
 *  1  1  1  1     |      0  0  1  1
 *  --------------------------------
 *  
 *  Circuit connection:
 *  A resistor will be connected from the 5V terminal
 *  to the ground terminal.  This connection will
 *  provide a high input when the switch is closed and
 *  a low input when the switch is open.
 *  Between the switch and the arduino pins, a resistor to
 *  ground will be connected to prevent the fluctuation
 *  of the input being sensed by the microcontroller of
 *  the electricity being induced from the emf from the
 *  the environment.
 *  Voltage divider not needed to limit current flow since
 *  Arduino digital pins when configured as an input, which
 *  is the default behavior, has a high input impedance.
 *  
 *  Input:
 *  The switch is connected between the 5V terminal and
 *  the resistor, which will provide the input to the digital
 *  pins being used as input.
 *  LEDs are connected to the digital terminals configured as 
 *  output with a single resistor being shared among the LEDs 
 *  before connecting to ground.
 */

/*
 * Note:
 * Dots (.) denote AND operation.
 * Single quote (') denote low state.
 * 
 * K-Map results:
 * OUT3 = IO’I1’I2’I3+I0’I1’I2I3’+I0I1I2I3’+I0I1’I2’I3’+I0I1’I2I3
 * OUT2 = I0’I1’I2’+I0’I1I2+I0’I3’+I1’I3’
 * OUT1 = I0’I1I2’+I1I2’I3+I0I2+I2I3’
 * OUT0 = I0’I2’I3’+I0I1I3+I1’I2I3+I0I1I2
 */

/*
 * Constants defined so the variables defined for
 * the purpose of controlling the input and output
 * pins are not changed.
 */
// Built-in LED
const int builtInLED = 13;
// Digital pins for input
const int IN3=12; // pin 12 for I3
const int IN2=11; // pin 11 for I2
const int IN1=10; // pin 10 for I1
const int IN0=9;  // pin 9 for I0

// Digital pins for output
const int OUT3=7;  // pin 7 for O3
const int OUT2=6;  // pin 6 for O2
const int OUT1=5;  // pin 5 for O1
const int OUT0=4;  // pin 4 for O0

void setup() {
  // turn off built-in LED
  pinMode(builtInLED, OUTPUT);
  digitalWrite(13,LOW);

  // defining digital pins 9 to 12 as input
  pinMode(IN3, INPUT);
  pinMode(IN2, INPUT);
  pinMode(IN1, INPUT);
  pinMode(IN0, INPUT);

  //defining digital pins 4 to 7 as output
  pinMode(OUT3, OUTPUT);
  pinMode(OUT2, OUTPUT);
  pinMode(OUT1, OUTPUT);
  pinMode(OUT0, OUTPUT);

}

void loop() {
  // Reading digital input from input pins
  bool input3 = digitalRead(IN3);
  bool input2 = digitalRead(IN2);
  bool input1 = digitalRead(IN1);
  bool input0 = digitalRead(IN0);

  // OUT3 status
  if((input0==LOW&&input1==LOW&&input2==LOW&&input3==HIGH)|| // breaking long conditional statement into multiple lines
  (input0==LOW&&input1==LOW&&input2==HIGH&&input3==LOW)||
  (input0==HIGH&&input1==HIGH&&input2==HIGH&&input3==LOW)||
  (input0==HIGH&&input1==LOW&&input2==LOW&&input3==LOW)||
  (input0==HIGH&&input1==LOW&&input2==HIGH&&input3==HIGH)){
    digitalWrite(OUT3, HIGH); // OUT3 set to high
  }else{
    digitalWrite(OUT3, LOW); // OUT3 set to low
  }

  // OUT2 status
  if((input0==LOW&&input1==LOW&&input2==LOW)|| // breaking long conditional statement into multiple lines
  (input0==LOW&&input1==HIGH&&input2==HIGH)||
  (input0==LOW&&input3==LOW)||
  (input1==LOW&&input3==LOW)){
    digitalWrite(OUT2, HIGH); // OUT2 set to high
  }else{
    digitalWrite(OUT2, LOW); // OUT2 set to low
  }

  // OUT1 status
  if((input0==LOW&&input1==HIGH&&input2==LOW)||      // breaking long conditional statement into multiple lines
  (input1==HIGH&&input2==LOW&&input3==HIGH)||
  (input0==HIGH&&input2==HIGH)||
  (input2==HIGH&&input3==LOW)){
    digitalWrite(OUT1, HIGH); // OUT1 set to high
  }else{
    digitalWrite(OUT1, LOW); // OUT1 set to low
  }

  // OUT0 status
  if((input0==LOW&&input2==LOW&&input3==LOW)||       // breaking long conditional statement into multiple lines
  (input0==HIGH&&input1==HIGH&&input3==HIGH)||
  (input1==LOW&&input2==HIGH&&input3==HIGH)||
  (input0==HIGH&&input1==HIGH&&input2==HIGH)){
    digitalWrite(OUT0, HIGH); // OUT0 set to high
  }else{
    digitalWrite(OUT0, LOW); // OUT0 set to low
  }

  // adding delay to idle the arduino
  // and also for stability to allow the LEDs to discharge
  delay(50);

}
