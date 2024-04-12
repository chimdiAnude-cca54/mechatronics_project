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
    PORTD = 0b00101000; //left and right motor forward
    _delay_ms(1000);
    
    //turn 90 degress right 
    PORTD = 0b00001000; // right motor stops while left motor moves forwards 
    _delay_ms(1000);

    //move forward
    PORTD = 0b00101000; //left and right motor forward
    _delay_ms(1000);

    //turn 90 degress left 
    PORTD = 0b00100000; // left motor stops while right motor moves forwards 
    _delay_ms(1000);

    //move forward (half the distance)
    PORTD = 0b00101000; //left and right motor forward
    _delay_ms(500);
    
    //move backwards for a longer distance
    PORTD = 0b01010000; //left and right motor backwards
    _delay_ms(1500);

    //turn 90 degress left 
    PORTD = 0b00100000; // left motor stops while right motor moves forwards 
    _delay_ms(1000);

    //move forward
    PORTD = 0b00101000; //left and right motor forward
    _delay_ms(1000);
    
    //pause for one second
    PORTD = 0b00000000;
    _delay_ms(1000);
   
  }

}