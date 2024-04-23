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

//  COLOR SENSOR CODE ========================================================================================
// Timer
volatile unsigned int color;

/**
 * Listen for interrupts on PCINT2 space
 */
ISR(PCINT2_vect) {
    // Detect rising edge by looking for a non-zero
    // input signal when the interrupt is triggered
    if (PIND & 0b10000000) {
        // Reset the timer count
        TCNT1 = 0;
    } else {
        // Store the timer count
        color = TCNT1;
    }
}

/**
 * Initialize pins, interrupts, and timer
 */
void initColor() {
    // Enable interrupts globally
    sei();

    // Initialize interrupts
    PCICR |= 0b100;

    // Initialize the timer
    TCCR1A = 0b00; // normal mode
    TCCR1B = 0b01; // prescaler = 1
    TCNT1 = 0; // reset timer
}



/**
 * Limit a number to a specified set of bounds.
 */
int limit(int x, int min, int max) {
    if (x < min) {
        return min;
    }

    if (x > max) {
        return max;
    }

    return x;
}

/**
 * Fit a number into a new range.
 */
float range(float x, float in_min, float in_max, float out_min, float out_max) {
    return (x - in_min) / (in_max - in_min) * (out_max - out_min) + out_min;
}

// END OF COLOR SENSOR CODE =====================================================================================================

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
  char location;


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


  int getColor() {
    // Set interrupt pin
    PCMSK2 |= 0b10000000;

    _delay_ms(5);

    // Divide the step count by 16 to convert from clock ticks
    // to microseconds, then multiply by 2 to get to full period
    int us = color / 8; // (1/16) * 2

    // Reset interrupt pin
    PCMSK2 &= ~0b10000000;

    return us;
}



  void goBack(){
    PORTC = forward; 
    _delay_ms(2000);

    PORTC = 0;
  }


char where_am_i_color (){
         // PORTB = 0b000001;

        // Read red color and map to 0-255 range
        int red = getColor();
        //int R = limit(range(red, 25.0, 435.0, 255.0, 0), 0, 255);
        //Serial.print("red:");
        //Serial.println(red);
       // _delay_ms(10);
        if (red>370){
            // on black
            return ('K');
        }
        else if (red<320 && red>150){
          //on blue
          return ('B');
        }
        else if (red<100 && red>1){
          //on yellow
          return ('Y');
        }
        else{
          //unknown color
          //turn slightly
          return ('U');
        }

}

int count=0;

int main(void){
  init();
  Serial.begin(9600);

  //set all GPIO pins (as labeled above)
  DDRC = 0b00001111; //set pins A0-A3 as outputs
  DDRD = 0b00000000; // pins 3,4 QTI sensor, pin 7 Color Sensor Ouput
  DDRB = 0b001111; // pins 8-11 are outputs (sensors)
  PORTB = 0b000001; //set 20% output frequency scaling factor (S0 high and S1 low)


  //Serial.println("Pins set");
  //_delay_ms(1000);

initColor();
  
  //TIMSK1 = 0b00000001; //enable timer
  //_delay_ms(1000);

  //Serial.println("interrupts");
  //_delay_ms(100);

  sei();

  

  // Serial.println("interrupts set");
  // _delay_ms(200);



       // _delay_ms(5);
      /*
        // Set green filter
        PORTB = 0b00001101;

        // Read green color and map to 0-255 range
        int green = getColor();
        int G = limit(range(green, 27.0, 501.0, 255.0, 0), 0, 255);

        _delay_ms(5);

        // Set blue filter
        PORTB = 0b00001001;

        // Read blue color and map to 0-255 range
        int blue = getColor();
        int B = limit(range(blue, 21.0, 373.0, 255.0, 0), 0, 255);

        */


 homeColor = where_am_i_color(); // current reading from getColor()
 //Serial.println(homeColor);
  _delay_ms(10);



  while(1){
    PORTC = forward; 
    _delay_ms(10);

    //Serial.println("moving!");
    //_delay_ms(100);
    location=where_am_i_color();
    
      if (count >4){
        PORTC=0;
      break;
    }
    Serial.print(location);    
    
    if (where_am_i_color() != homeColor){
      // Serial.println("away!");
      // _delay_ms(50);

      //PORTC = right;
      PORTC = 0;
      _delay_ms(100); // 180 degree turn

      PORTC = left;
      _delay_ms(600);
      
      // Serial.println("turn!");
      // _delay_ms(10);

      //goBack();
      count= count+1;
      
    }


}


}