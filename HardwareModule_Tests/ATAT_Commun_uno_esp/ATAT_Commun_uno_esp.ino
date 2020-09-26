#include <SoftwareSerial.h>
SoftwareSerial Serial1 (2, 3);
String abc = "123123";
String inputString = "";         // a String to hold incoming data
bool stringComplete = false;
unsigned long lastMillis = 0;

void setup() {

  Serial.begin(115200);
  Serial1.begin(115200);
  inputString.reserve(8);

}

void loop() {
  
  if (Serial1.available() > 0) {
    serialEvent1();
  }

  if (stringComplete) {
    String temp = inputString;
    Serial.println(temp);
    inputString = "";
    stringComplete = false;
   
  }
    if (millis() - lastMillis > 1000) {
    lastMillis = millis();

    Serial1.print("1");
    Serial1.println("_123");
    Serial.flush();
    }
}

void serialEvent1() {
  while (Serial1.available()) {
    // get the new byte:
    char inChar = (char)Serial1.read();
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag so the main loop can
    // do something about it:
    if (inChar == '\n') {
      stringComplete = true;

    }
  }
}
