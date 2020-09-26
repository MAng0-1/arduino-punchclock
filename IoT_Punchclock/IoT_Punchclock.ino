#include <SPI.h>
#include <MFRC522.h>
#include <LiquidCrystal.h>
#include <SoftwareSerial.h>
#include "Config.h"


void setup()
{
  setupIDCheck();
  setupNetwork();
  setupPeripheral();
}

void loop()
{
  loopIDCheck();
  loopNetwork();
}
