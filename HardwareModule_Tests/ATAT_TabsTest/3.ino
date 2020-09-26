void setup1() {
 // set the digital pin as output:
 pinMode(ledPin, OUTPUT);      
}

void loop1()
{
  // check to see if it's time to blink the LED; that is, if the
 // difference between the current time and last time you blinked
 // the LED is bigger than the interval at which you want to
 // blink the LED.
 unsigned long currentMillis = millis();

 if(currentMillis - previousMillis > interval) {
   // save the last time you blinked the LED
   previousMillis = currentMillis;  

   // if the LED is off turn it on and vice-versa:
   if (ledState == LOW)
     ledState = HIGH;
   else
     ledState = LOW;

   // set the LED with the ledState of the variable:
   digitalWrite(ledPin, ledState);
 }
}
