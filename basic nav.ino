/*
Milestone 2: Basic Navigation 
Team 27
Team Members: Tyler Wisniewski, Ethan Sarpong, Chimdi Anude

Last Edit (Author/Date): Ethan 04/12 

HARDWARE CONNECTIONS:
PIN A3 & A2 -> Left H-Bridge Motor 3 4
PIN A1 & A0 -> Right H-Bridge Motor 5 6 
PIN 0 -> Timer Interrupt for Countdown
PIN 1 -> Left QTI Sensor 
PIN 2 -> 
PIN 3 -> 
PIN 4 -> Right QTI Sensor 
PIN 5 & 6 -> Pin Change Interrupts for Border
PIN 7 -> Color Sensor output
PIN 8-11 -> S0-S3 on the Color sensor 
PIN 12 -> Pin Change for Color Sensor
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
  int backward = 0b00000101; // pin A0 & A2 HIGH 4 5 
  int right = 0b00001001; // PIN A3 & A0 HIGH (Right Wheel Backward - Left Wheel Forward) 3, 6
  int left = 0b00000110; // pin A1 & A2 high (Right Wheel Forward - Left Wheel Backward) 4, 5

  // "period" : stores the value of the output wave period in microseconds
  volatile int period;

  // "timer" : stores the value of TIMER1 
  volatile int timer;

  int threshold = 300; // boundary of yellow and blue

  char homeColor;

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

    PORTD = 0;

  }

  ISR(PCINT2_vect){ // pin change interrupt for borders
    if(edge_left){
      //Turn Right
      PORTC = right;
      _delay_ms(600);
      }
    elif (edge_right){
      // Turn Left
        PORTC = left;
      _delay_ms(600);
    }
  }

  ISR(PCINT1_vect){
    // resets the timer to zero on a rising edge of sensor's output signal,
  // check if output signal (pin D12) is high
    if(PINB &= 0b00100000){
      TCNT1 = 0x00;
    } else { // and stores the timer value in a variable ("timer") on a falling edge (or vice versa).
      timer = TCNT1;
    }
  }
  /*ISR(TIMER1_COMPA_vect){

  }*/

  void borderDetection(){
    PCMSK2 = 0b00001100; // look at pins 2 & 3 as pin interrupts
    int PIN_QTI_LEFT = 0b00000010; // pin 1
    int PIN_QTI_RIGHT = 0b0001000; // pin 4

    bool edge_left = PINB & PIN_QTI_LEFT;
    bool edge_right = PINB & PIN_QTI_RIGHT;


  }

  char getColor(){
    PORTD = 0b00000100;
    PCMSK1 = 0b00100000; // look at pin 12
    //set the scaling for blue and Yellow and determine which one

    _delay_ms(8);

    //	Disable the specific bit for your pin change interrupt (to prevent further interrupts until you call getColor again)
    PCMSK1 = 0x00; //disable interrupt at pin 12
    
    // d.	Return the period in ms
    // get current count (half period) and divide by max counts (65536)
    // multiply by timer total time = 4.096*1000 us
    period = (timer*2)*(4.096*1000/65536);

     if (period > threshold){
      return 'B';
    } else {
      return 'Y';
    }
    

  }

  void goBack(){
    PORTC = forward; 
    _delay_ms(2000);

    PORTD = 0;
  }

  /*void countDown(){
    TCCR1B = 0b00001101; //set prescaler to 1024
    TIMSK1 = 0b00000001; //enable timer
    TCNT1 = 0;
    OCR1A = 15624; // 1 second

    TIMSK1 |= (1<<1);
  }*/

  void enableINTS(){
    // initialize pin chnage interrupts
    PCICR = 0b00000110; // enable pin interupts for QTI sensors and for color sensor

    //initialize timer for color sensor
    TCCR1B = 0b00000001; //set prescaler to 1
    TIMSK1 = 0b00000001; //enable timer
    sei();
  }
int main(void){
  //set all GPIO pins (as labeled above)
  DDRC = 0b00001111; //set pins A0-A3 as outputs
  DDRD = 0b10010010; // pins 1, 4, 7 is an output,pins 5,6 are inputs
  DDRB = 0b00001111; // pins 8-11 are outputs (sensors)

  enableINTS();

  homeColor = getColor(); // current reading from getColor()
  PORTC = forward; 
  _delay_ms(2000);

  if (getColor() != homeColor){
    PORTC = right;
    _delay_ms(2000);
  }

  goBack();



}

