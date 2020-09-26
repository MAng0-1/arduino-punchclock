#include <LiquidCrystal.h>

LiquidCrystal lcd(3, 2, 4, 5, 6, 7);
int attendanceState = 0;
const int buzzer = A0;


void setup(){

  Serial.begin(9600);

  //LCD
  lcd.begin(16, 2);
  lcd.print("Display ONLINE");
  delay(1000);
  lcd.clear();
  
  //Buzzer
  pinMode (buzzer, OUTPUT);
  tone (buzzer, 1046);
  delay (100);
  noTone (buzzer);
}

void loop() {

  giveFeedback();//LCD/Buzzer/Replies for change in attendance
  delay(1000);
  lcd.clear();
  attendanceState = attendanceState+1;
  if(attendanceState > 5){
    attendanceState = 0;
  }

}

void giveFeedback() {
  // (0=void, 1=StartWork, 2=PauseWork, 3=ResumeWork, 4=EndWork, 5=Error)
  switch (attendanceState) {

    case 0:
      lcd.print("Idle");
      break;

    case 1:
      tone(buzzer, 1174);
      delay(100);
      noTone(buzzer);
      delay(50);
      lcd.print ("Guten Morgen!");
      break;

    case 2:
      tone(buzzer, 1318);
      delay(100);
      noTone(buzzer);
      delay(50);
      lcd.print ("Mahlzeit!");
      break;

    case 3:
      tone(buzzer, 1760);
      delay(100);
      noTone(buzzer);
      delay(50);
      lcd.print ("Weiter gehts!");
      break;

    case 4:
      tone(buzzer, 1975);
      delay(100);
      noTone(buzzer);
      delay(50);
      lcd.print ("Bis Bald!");
      break;

    case 5:
      tone(buzzer, 2093);
      delay(100);
      noTone(buzzer);
      delay(50);
      lcd.print ("ERROR");
      lcd.setCursor(0, 1);
      lcd.print ("Erneut versuchen");
      break;
  }


}
