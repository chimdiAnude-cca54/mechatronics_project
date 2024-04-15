/*
Milestone 2: Basic Navigation 
Team 27
Team Members: Tyler Wisniewski, Ethan Sarpong, Chimdi Anude

Last Edit (Author/Date): Ethan 04/12 

HARDWARE CONNECTIONS:
Pin 0 -> Timer Interrupt
PIN 1 -> Border Interrupt 
PIN 2 -> Color Sensor Output
PIN 3 & 4 -> Left H-Bridge Motor
PIN 5 & 6 -> Right H-Bridge Motor
PIN 7-10 -> S0-S3 on the Color sensor 
PINS 11-13 -> QTI Sensors

WIRE COLOR CODE FOR BOARD: 
Black - Vcc (6V Battery)
Yellow - Ground
Blue - Backward Signal
Green - Forward Signal

Note: The Left H-Bridge Green and Blue Wires were Flipped on the Bread Board
*/



//#include <stdio.h>

//Global Variables
  int forward = 0b00101000; // pin 3 & 5 are HIGH
  int backward =0b01010000; // pin 4 & 6 HIGH
  int right = 0b01001000; // PIN 3 & 6 HIGH (Right Wheel Backward - Left Wheel Forward)
  int left = 0b00110000; // pin 5 & 4 high (Right Wheel Forward - Left Wheel Backward)

int main(void){
  // pin set up 
  DDRD = 0b01111000; //set pins 3,4,5,6 as outputs

  // Move Forward
  PORTD = forward; 
  _delay_ms(2000);

  //Turn Right
  PORTD = right;
  _delay_ms(600);

  //Move Forward
  PORTD = forward; 
  _delay_ms(2000);

  //Turn Left
  PORTD = left;
  _delay_ms(600);

  // Move Backward
  PORTD = backward;
  _delay_ms(3500); 

  //Turn Left
  PORTD = left;
  _delay_ms(600);

  //Move Forward
  PORTD = forward; 
  _delay_ms(2000);

  PORTD = 0;


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
