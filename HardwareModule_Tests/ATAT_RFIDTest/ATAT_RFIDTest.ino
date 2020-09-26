#include <MFRC522.h>
#include <SPI.h>
#include <LiquidCrystal.h>

#define CS_RFID 10
#define RST_RFID A2

LiquidCrystal lcd(2, 3, 4, 5, 6, 7);

const int buzzer = A0;


MFRC522 rfid(CS_RFID, RST_RFID);

String uidString;  //UID FOR SENDING
char uidTopic;

//Button
bool isButtonPressed = false;
const int button = A5;

//Button/Timer
int buttonTimer = 6000;// Time after button press in milliseconds
int systemTime;
int buttonTime;
int interval;


void setup() {
  Serial.begin(9600);

  //RFID
  SPI.begin();
  rfid.PCD_Init();

  //Button
  pinMode(button, INPUT);

    //LCD
  lcd.begin(16, 2);
  lcd.print("Display ONLINE");
  delay(1000);
  lcd.clear();




}

void loop() {

  //RFID/
  if (rfid.PICC_IsNewCardPresent()) {
    readRFID();
  }

  //BUTTON/
  checkButton();

  if (isButtonPressed == true && interval >= -300 && interval <= 300) {
    endButton();
  }

  systemTime = millis();
  interval = systemTime - buttonTime;
  delay(20);
}

void readRFID() {
  rfid.PICC_ReadCardSerial();
  Serial.print("Tag UID: ");
  uidString = String(rfid.uid.uidByte[0]) + " " + String(rfid.uid.uidByte[1]) + " " +
              String (rfid.uid.uidByte[2]) + " " + String(rfid.uid.uidByte[3]);
  Serial.println(uidString);
  Serial.print("Grandmaster, did you press the button (Is the button pressed:)? ");
  Serial.println(isButtonPressed);
  
  if(isButtonPressed==false){
    lcd.print("Please, press");
    lcd.setCursor(0, 1);
    lcd.print("the button first");
  }
  if(isButtonPressed==true){
    lcd.print("Commencing");
    lcd.setCursor(0, 1);
    lcd.print("NUCLEAR LAUNCH");
  }
  tone (buzzer, 1975, 150);
  delay(1200);
  lcd.clear();
}

//3s Countdown after Buttonpress
void checkButton() {

  if (analogRead(button) > 1000) {
    if (interval < 300 || interval > 300) {
      isButtonPressed = true;
      tone (buzzer, 1046);
      delay (100);
      noTone (buzzer);
      buttonTime = systemTime + buttonTimer;
    }
  }
}

void endButton() {
  tone (buzzer, 2093);
  delay (100);
  noTone (buzzer);
  isButtonPressed = false;
}
