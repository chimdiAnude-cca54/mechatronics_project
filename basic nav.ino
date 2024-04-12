/*
Milestone 2: Basic Navigation 
Team 27
Team Members: Tyler Wisniewski, Ethan Sarpong, Chimdi Anude

HARDWARE CONNECTIONS:
PIN 3 & 4 -> Left H-Bridge Motor
PIN 5 & 6 -> Right H-Bridge Motor


*/

// pin set up 
DDRD = 0b01111000; //set pins 3,4,5,6 as outputs

//#include <stdio.h>

void main(){
    
    while(1){
    //move forward
    PORTD = 0b00000100; //pin 2 is HIGH
    PORTD = 0b00000100;
    delay(1000);
    
    //pause for one second
    PORTD = 0b00000000;
    _delay_ms(1000);
    
    //spin backwards
    PORTD = 0b10000000; //pin 7 is HIGH
    _delay_ms(1000);
    
    //pause for one second
    PORTD = 0b00000000;
    _delay_ms(1000);
   
  }

}