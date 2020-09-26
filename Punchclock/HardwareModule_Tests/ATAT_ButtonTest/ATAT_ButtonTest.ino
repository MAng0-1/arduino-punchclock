int buttonTimer = 3000;// Time after button press in milliseconds
int systemTime;
int buttonTime;
int interval;



char isButtonPressed = 0;
const int button = A2;
const int buzzer = A1;

void setup() {
  Serial.begin(9600);

  //Button
  pinMode(button, INPUT);
  



}

void loop() {

  checkButton();
  
  if (isButtonPressed == 1 && interval >= -500 && interval <= 500){
    endButton();
  }

  systemTime = millis();
  interval = systemTime - buttonTime;
  Serial.println(interval);
  
  delay(10);
}

//5s Countdown after Buttonpress
void checkButton(){

  if (analogRead(button) > 1000){
    isButtonPressed = 1;
    tone (buzzer, 1046);
    delay (100);
    noTone (buzzer);
    buttonTime = systemTime + buttonTimer;
    Serial.println(buttonTime);
    delay(500);

  }
}
void endButton(){
    tone (buzzer, 2093);
    delay (100);
    noTone (buzzer);
    isButtonPressed = 0;
}
