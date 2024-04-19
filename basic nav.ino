/*
Milestone 2: Basic Navigation 
Team 27
Team Members: Tyler Wisniewski, Ethan Sarpong, Chimdi Anude

Last Edit (Author/Date): Ethan 04/12 

HARDWARE CONNECTIONS:
PIN A0 & A1 -> Left H-Bridge Motor
PIN A2 & A3 -> Right H-Bridge Motor
PIN 0 -> Timer Interrupt
PIN 1 -> Left QTI Sensor 
PIN 2 -> External Interuppt
PIN 3 -> External Interrupt 
PIN 4 -> Right QTI Sensor 
PIN 5 & 6 -> Pin Change Interrupts for Border
PIN 7 -> Color Sensor output
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
  int forward = 0b00000101; // pin A0 & A2 are HIGH
  int backward =0b00001010; // pin A1 & A3 HIGH
  int right = 0b00001001; // PIN A0 & A3 HIGH (Right Wheel Backward - Left Wheel Forward)
  int left = 0b00000110; // pin A1 & A2 high (Right Wheel Forward - Left Wheel Backward)

  // "period" : stores the value of the output wave period in microseconds
  volatile int period;

  // "timer" : stores the value of TIMER1 
  volatile int timer;

  int threshold = 45000; // 45 seconds 

  enum Color (
    BLUE 0,
    YELLOW 1
  );

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

  ISR(TIMER1_COMPA_vect){

  }

  void borderDetection(){

    int PIN_QTI_LEFT = 0b01000000; // pin 12
    int PIN_QTI_RIGHT = 0b10000000; // pin 13

    bool edge_left = PINB & PIN_QTI_LEFT;
    bool edge_right = PINB & PIN_QTI_RIGHT;


  }

  int getColor(){
    //set the scaling for blue and Yellow and determine which one
    // if in yellow range(), return False homeColor = Yellow
    // if in blue range, return True
    

  }

  void goBack(){

    // go back to home color when time is up
  }

  void countDown(){
    TCCR1B = 0b00001101; //set prescaler to 1024
    TIMSK1 = 0b00000001; //enable timer
    TCNT1 = 0;
    OCR1A = 15624; // 1 second

    TIMSK1 |= (1<<1);
  }
int main(void){
  //set all GPIO pins (as labeled above)
  DDRC = 0b00001111; //set pins A0-A3 as outputs
  DDRD = 0b10010010; // pins 1, 4, 7 is an output,pins 5,6 are inputs
  DDRB = 0b00001111; // pins 8-11 are outputs (sensors)
  
  
  PCICR = 0b00000100; // enable pin interupts for QTI sensors
  PCMSK2 = 0b00001100; // look at pins 2 & 3 as pin interrupts



  sei();
  if (){
    homeCo
  }
  homeColor =; // current reading from getColor()
  // move forward
  // if 

  navigation();



}

// Future Steps: Make Functions for each command (i.e forward, backward) with an input of time. 

// void main(){
    
//     while(1){
//     //move forward
//     PORTD = 0b00000100; //pin 2 is HIGH
//     PORTD = 0b00000100;
//     delay(1000);
    
//     //pause for one second
//     PORTD = 0b00000000;
//     _delay_ms(1000);
    
//     //spin backwards
//     PORTD = 0b10000000; //pin 7 is HIGH
//     _delay_ms(1000);
    
//     //pause for one second
//     PORTD = 0b00000000;
//     _delay_ms(1000);
   
//   }

// }
