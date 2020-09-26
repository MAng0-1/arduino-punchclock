//RFID
#define CS_RFID 10
#define RST_RFID A1

MFRC522 rfid(CS_RFID, RST_RFID);

//Sending information
String uidString;                  //String that holds the Chip-ID
boolean isButtonPressed = false;   //Is the Button in contdown mode?
boolean sendMessage = false;      //Is there a message to be sent?

//Button
const int button = A5;  //button pin

//Button/Timer
const int buttonUptime = 3000;// Countdown after button press in milliseconds
unsigned long buttonTime;
unsigned long interval;

//Networking
SoftwareSerial Serial1(8, 9); // RX, TX

String inputString = "";      //variables for receiving Serial messages
bool stringComplete = false;
unsigned long lastMillis = 0;


//LCD + Buzzer
LiquidCrystal lcd(2, 3, 4, 5, 6, 7); //LCD pins
const int buzzer = A0;
