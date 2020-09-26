/* Blink without Delay

This example code is in the public domain.
http://www.arduino.cc/en/Tutorial/BlinkWithoutDelay
*/

/*
* Global variables
*/
int ledPin =  13;      // the number of the LED pin
int ledState = LOW;             // ledState used to set the LED
long previousMillis = 0;        // will store last time LED was updated
long interval = 1000;           // interval at which to blink (milliseconds)


/*
* Function prototypes
*/
void setup(){
setup1();
setup2();
}
void loop(){
loop1();
}

/*
* Actual code
*/
