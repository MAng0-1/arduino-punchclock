#include <LiquidCrystal.h>

void setupPeripheral() {

  //LCD
  lcd.begin(16, 2);
  lcd.print("Display ONLINE");
  delay(1000);
  lcd.clear();

  //Buzzer
  tone (buzzer, 2000);
  delay (500);
  noTone (buzzer);
}

void feedbackSound(){
      tone(buzzer, 3000);
      delay(100);
      noTone(buzzer);
      delay(50);
}

void lcdOff(){
  delay(1000);
  lcd.clear();
  lcd.noDisplay();
}

void giveFeedback(int* result) {
  // (0=void, 1=StartWork, 2=PauseWork, 3=ResumeWork, 
  // 4=EndWork, 5=EmbraceError, 6=WiFi online, 7=MQTTError)
  switch (*result) {

    case 0:
      lcdOff();
      break;

    case 1:
      lcd.display();
      feedbackSound();
      lcd.print ("Guten Morgen!");
      lcdOff();
      break;

    case 2:
      lcd.display();
      feedbackSound();
      lcd.print ("Mahlzeit!");
      lcdOff();
      break;

    case 3:
      lcd.display();
      feedbackSound();
      lcd.print ("Weiter gehts!");
      lcdOff();
      break;

    case 4:
      lcd.display();
      feedbackSound();
      lcd.print ("Bis Bald!");
      lcdOff();
      break;

    case 5:
      lcd.display();
      feedbackSound();
      lcd.print ("ERROR_01");
      lcd.setCursor(0, 1);
      lcd.print ("Erneut versuchen");
      lcdOff();
      break;

    case 6:
      lcd.display();
      feedbackSound();
      lcd.print("WIFI ONLINE");
      lcdOff();
      break;

    case 7:
      lcd.display();
      feedbackSound();
      lcd.print("ERROR_02");
      lcd.setCursor(0,1);
      lcd.print ("Erneut versuchen");
      lcdOff();
      break;
  }
 
}
