#include<ESP8266WiFi.h>
#include<PubSubClient.h>
extern "C" {
#include "user_interface.h"
}

const char* ssid = "Centigrade-Legacy";
const char* password = "Gufbmc92YVzkmvsF";
const char* mqttServer = "mqtt.intranet.centigrade.de";
const int mqttPort = 1883;
const char* mqttID = "ATAT_MUN";
const char* mqttUser = "";
const char* mqttPassword = "";
char inputChar[8];

String inputString = "";         // a String to hold incoming data
bool stringComplete = false;

WiFiClient espClient;
PubSubClient client(mqttServer, mqttPort, espClient);

void setup()
{
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print("Connecting to WiFi...");
  }

  client.setCallback(callback);
  Serial.println("Connected to the WiFi network");

  while (!client.connected()) {
    Serial.println("Connecting to MQTT...");

    if (client.connect("ATAT_MUN", mqttUser, mqttPassword )) {

      Serial.println("connected");

    } else {

      Serial.print("failed with state ");
      Serial.print(client.state());
      delay(2000);

    }
    if (client.subscribe("punchClock/caseState")) {
      Serial.println("subscribed");
    }
    else
    {
      Serial.println("could not subscribe");
    }
  }
    wifi_set_sleep_type(LIGHT_SLEEP_T);

    inputString.reserve(8);

  }


  void loop()
  {
    if (!client.connected())
    {
      re_connect();
    }
    client.loop();

    if (Serial.available() > 0){
      serialEvent();
    }
    
    if (stringComplete) {
      inputString.toCharArray(inputChar, 8);
      client.publish("punchClock/", inputChar);
      inputString = "";
      stringComplete = false;
    }
    delay(10);

  }

  void re_connect() {

    WiFi.persistent(false);   // daten nicht in Flash speichern
    WiFi.mode(WIFI_STA);
    Serial.printf("Connecting to %s ", ssid);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED)
    {
      delay(500);
      Serial.print(".");
    }
    Serial.println(" connected");
    Serial.print("local IP:");
    Serial.println(WiFi.localIP());
    Serial.println("Connecting to MQTT...");
    if (client.connect(mqttID, mqttUser, mqttPassword))
    {
      Serial.println("connected");
    }
    else
    {
      Serial.print("failed with state ");
      Serial.print(client.state());
      delay(2000);
    }
  }


  void serialEvent() {
    while (Serial.available()) {
      // get the new byte:
      char inChar = (char)Serial.read();
      // add it to the inputString:
      inputString += inChar;
      // if the incoming character is a newline, set a flag so the main loop can
      // do something about it:
      if (inChar == '\n') {
        stringComplete = true;
      }
    }
  }

  void callback(char* topic, byte * payload, unsigned int length) {

  //  Serial.print("Message arrived in topic: ");
//    Serial.println(topic);

    // Serial.println(0);
    //while (Serial.read() ==! 48)

 //   Serial.print("Message:");
    for (int i = 0; i < length; i++) {
      Serial.print((char)payload[i]);
    }

  //  Serial.println();
 //   Serial.println("-----------------------");


    delay(10);

  }
