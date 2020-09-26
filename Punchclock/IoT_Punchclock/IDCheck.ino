#include <MFRC522.h>
#include <SPI.h>


void setupIDCheck() {

  //RFID
  SPI.begin();
  rfid.PCD_Init();

  //Button
  pinMode(A2, INPUT);
}


void loopIDCheck() {

  if (rfid.PICC_IsNewCardPresent()) {
    sendMessage = readRFID(uidString); 
  }

  checkButton(&isButtonPressed); 
  
  interval =  millis() - checkButton(&isButtonPressed);
  //If the button is pressed, reset after <interval> seconds
  if (isButtonPressed == "1" && interval >= buttonUptime) {
    isButtonPressed = endButton();
  }

}

boolean readRFID(String targetString) {
  rfid.PICC_ReadCardSerial();
  Serial.print("Tag UID: ");
  targetString = String(rfid.uid.uidByte[0]) + String(rfid.uid.uidByte[1]);
  Serial.println(targetString);
  tone (buzzer, 1975, 200);
  return true;
}

// Gives signal that button is pressed and starts countdown
unsigned long checkButton(bool* isButtonPressed) {
  if (analogRead(button) > 1000) {
    if (interval >= buttonUptime) {
      *isButtonPressed = true;
      tone (buzzer, 1046);
      delay (100);
      noTone (buzzer);
      return millis();
    }
  }
}

//End timer, reset button
boolean endButton() {
  tone (buzzer, 2093);
  delay (100);
  noTone (buzzer);
  return false;
}
