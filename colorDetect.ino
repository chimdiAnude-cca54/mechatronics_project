/*
Milestone 2: Basic Navigation 
Team 27
Team Members: Tyler Wisniewski, Ethan Sarpong, Chimdi Anude

Last Edit (Author/Date): Ethan 04/12 

HARDWARE CONNECTIONS:
PIN A3 & A2 -> Left H-Bridge Motor 3 4
PIN A1 & A0 -> Right H-Bridge Motor 5 6 
PIN 0 -> 
PIN 1 -> 
PIN 2 -> 
PIN 3 -> Left QTI Sensor R / pin change
PIN 4 -> Right QTI Sensor R / pin change
PIN 5 ->
PIn 6 ->
PIN 7 -> Color Sensor output/ pin change 
PIN 8-11 -> S0-S3 on the Color sensor 
PIN 12 -> 
Pin 13 -> 

WIRE COLOR CODE FOR BOARD: 
Black - Vcc (6V Battery)
Yellow - Ground
Blue - Backward Signal
Green - Forward Signal

Note: The Left H-Bridge Green and Blue Wires were Flipped on the Bread Board
*/



//#include <stdio.h>

//Global Variables
  int forward = 0b00001010; // pin A3 & A1 are HIGH 3 5
  int backward = 0b00000101; // pin A0 & A2 HIGH 4 6 
  int right = 0b00001001; // PIN A3 & A0 HIGH (Right Wheel Backward - Left Wheel Forward) 3, 6
  int left = 0b00000110; // pin A1 & A2 high (Right Wheel Forward - Left Wheel Backward) 4, 5

  // "period" : stores the value of the output wave period in microseconds
  volatile int period;

  // "timer" : stores the value of TIMER1 
  volatile int color_timer;

  int threshold = 20; // boundary of yellow and blue

  char homeColor;

  ISR(PCINT2_vect)
  {	
    //Serial.println("1");
    // resets the timer to zero on a rising edge of sensor's output signal,
    // check if output signal (pin D7) is high
    if(PIND & 0b10000000){
      TCNT1 = 0x00;
      //Serial.println("2");
    } else { // and stores the timer value in a variable ("timer") on a falling edge (or vice versa).
      color_timer = TCNT1;
      //Serial.println("3");
    }

  }

  void navigation(){
    // pin set up 
    //DDRC = 0b00001111; //set pins A0-A3 as outputs

    // Move Forward
    PORTC = forward; 
    _delay_ms(2000);

    //Turn Right
    PORTC = right;
    _delay_ms(600);

    //Move Forward
    PORTC = forward; 
    _delay_ms(2000);

    //Turn Left
    PORTC = left;
    _delay_ms(600);

    // Move Backward
    PORTC = backward;
    _delay_ms(3500); 

    //Turn Left
    PORTC = left;
    _delay_ms(600);

    //Move Forward
    PORTC = forward; 
    _delay_ms(2000);

    PORTC = 0;

  }


  char getColor(){
    PCMSK2 = 0b10000000; // look at pin PD7
    //set the scaling for blue and Yellow and determine which one
    //Serial.println("getColor func");
    //_delay_ms(100);

    _delay_ms(8);
    
    //	Disable the specific bit for your pin change interrupt (to prevent further interrupts until you call getColor again)
    PCMSK2 = 0x00; //disable interrupt at pin 7
    
    // d.	Return the period in ms
    // get current count (half period) and divide by max counts (65536)
    // multiply by timer total time = 4.096*1000 us

    period = 2*color_timer*0.0625;

    Serial.print("Output wave:");
    Serial.println(period);

     if (period < threshold){
      Serial.println("got blue");
      _delay_ms(100);
      return 'B';

    } else {
      Serial.println("got yellow!");
      _delay_ms(100);

      return 'Y';

    }
    

  }

  void goBack(){
    PORTC = forward; 
    _delay_ms(2000);

    PORTC = 0;
  }

  void enableINTS(){
    // initialize pin chnage interrupts
    PCICR = 0b00000100; // enable pin interupts for color sensor

    //initialize timer for color sensor
    TCCR1B = 0b00000001; //set prescaler to 1
    
  }

int main(void){
  init();
  Serial.begin(9600);

  //set all GPIO pins (as labeled above)
  DDRC = 0b00001111; //set pins A0-A3 as outputs
  DDRD = 0b00000000; // pins 3,4 QTI sensor, pin 7 Color Sensor Ouput
  DDRB = 0b00001111; // pins 8-11 are outputs (sensors)
  PORTB = 0b00010001; //set 20% output frequency scaling factor (S0 high and S1 low)


  Serial.println("Pins set");
  _delay_ms(1000);

  enableINTS();
  
  //TIMSK1 = 0b00000001; //enable timer
  //_delay_ms(1000);

  Serial.println("interrupts");
  _delay_ms(100);

  sei();

  

  // Serial.println("interrupts set");
  // _delay_ms(200);

  homeColor = getColor(); // current reading from getColor()
  Serial.println(homeColor);
  _delay_ms(100);

  while(1){
    PORTC = forward; 
    _delay_ms(100);

    //Serial.println("moving!");
    _delay_ms(100);

    if (getColor() != homeColor){
      Serial.println("away!");
      _delay_ms(50);

      //PORTC = right;
      PORTC = 0;
      _delay_ms(400); // 180 degree turn

      PORTC = right;
      _delay_ms(1100);
      
      Serial.println("turn!");
      _delay_ms(10);

      goBack();
      break;
    }

    
}



}

