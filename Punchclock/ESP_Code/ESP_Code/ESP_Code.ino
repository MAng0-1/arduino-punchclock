#include <ESP8266WiFi.h>
#include <MQTT.h>
//extern "C" {
//#include "user_interface.h"
//}

WiFiClient net;
MQTTClient client;

String inputString = "";
bool serialMessageEndIsReached = false;

//Constants
//WIFI
const char ssid[] = "Generic-Wifi-ID";
const char pass[] = "G3N3R1CPW";

//mqtt
const char mqttID[] = "ATAT_Destroyer";
const char mqttServer[] = "mqtt.server.de";
const int mqttPort = 1883;
const char mqttUN[] = "";
const char mqttPW[] = "";

//mqtt topics
const String TOPIC_Case = "punchClock/caseState/";
const String TOPIC_UID = "punchClock/uidButtonState/";


void connectWifiAndMQTT() {

  // Wifi
  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
  }

  // MQTT
  while (!client.connect(mqttID, mqttUN, mqttPW)) {
    delay(100);
  }
}

//Reads publishes and sends them via Serial
void messageReceived(String & topic, String & payload) {
  Serial.println(payload);
  Serial.flush();
  }

// Handler for serial input events.
void serialAction() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag so the main loop can
    // do something about it:
    if (inChar == '\n') {
      serialMessageEndIsReached = true;
    }
  }
}

//basic methods of program
void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, pass);
  client.begin(mqttServer, net);
  client.onMessage(messageReceived);
//wifi_set_sleep_type(LIGHT_SLEEP_T);
  inputString.reserve(8);

  connectWifiAndMQTT();
  client.subscribe(TOPIC_Case);
  Serial.println("6"); //confirms setup completion to user
}

void loop() {
  client.loop();
  delay(10);  // fixes some issues with WiFi stability

  // Reconnect if conncetion is lost while the system is running
  if (!client.connected()) {
    connectWifiAndMQTT();
    client.subscribe(TOPIC_Case);
  }


  if (Serial.available() > 0) {
    serialAction();
  }

  // is triggered by the serialEvent method
  if (serialMessageEndIsReached) {
    if(!client.publish(TOPIC_UID, inputString)){
      Serial.println("7"); //Communicates MQTT error
    }
    inputString = "";
    serialMessageEndIsReached = false;
  }
}
