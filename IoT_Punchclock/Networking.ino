

void setupNetwork() {

//  Serial.begin(9600);
  Serial1.begin(115200);
  inputString.reserve(8);

}

void loopNetwork() {

  if (Serial1.available() > 0) {
    giveFeedback(serialAction());
  }

  //If there is data, sends it to ESP
  if (sendMessage == true && stringComplete == false) {
    Serial1.print(isButtonPressed + "_");
    Serial1.println(uidString);
    sendMessage = false;
  }
}


//Stores incoming Serial data in inputString
String serialAction() {
  int* result;
  *result = (int)Serial1.read();
  return result;
}
