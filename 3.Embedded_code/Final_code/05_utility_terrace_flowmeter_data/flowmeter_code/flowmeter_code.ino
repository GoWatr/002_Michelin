#include "heltec.h"
#include "images.h"
#define BAND 433E6       //you can set band here directly,e.g. 868E6,915E6
#include "flowmeter.h"  //.h library with flowmeter functions

String rssi = "RSSI --";
String packSize = "--";
String packet;

String ID1 = "!FMA01T:";
String ID2 = ",!FMA01F:";
String Flowmeter_Flow;
String Flowmeter_Tot;

int counter_DS, counter_FM = 0;

void logo() {
  Heltec.display->clear();
  Heltec.display->drawXbm(0, 5, logo_width, logo_height, logo_bits);
  Heltec.display->display();
}

void setup() {
  Heltec.begin(true /*DisplayEnable Enable*/, true /*Heltec.Heltec.Heltec.LoRa Disable*/, true /*Serial Enable*/, true /*PABOOST Enable*/, BAND /*long BAND*/);
  Serial.begin(9600);
  mod.begin(9600);
  delay(30);
  mod.flush();
  delay(1000);

  Heltec.display->init();
  Heltec.display->flipScreenVertically();
  Heltec.display->setFont(ArialMT_Plain_10);
  logo();
  delay(1500);
  Heltec.display->clear();

  Heltec.display->drawString(0, 0, "Heltec.LoRa Initial success!");
  Heltec.display->display();
  delay(1000);
}

void loop() {
  delay(1000);
  MODBUS();  //modbus function called to read flowmeter data
  delay(1000);
  Flowmeter_Tot = ID1 + String(Tot);
  Flowmeter_Flow = ID2 + String(Flow);

  Heltec.display->clear();
  Heltec.display->setTextAlignment(TEXT_ALIGN_LEFT);
  Heltec.display->setFont(ArialMT_Plain_10);

  Heltec.display->drawString(0, 12, "(Flow)  " + String(Flow));
  Heltec.display->drawString(0, 24, "(Tot)  " + String(Tot));
  Heltec.display->display();

  counter_DS++;
  delay(1000);
  if (counter_DS == 11) {
    counter_DS = 0;
    if ((values[0] == 1) && (values[1] == 3)) {
      Heltec.display->display();
      LoRa.beginPacket();
      LoRa.setTxPower(14, RF_PACONFIG_PASELECT_PABOOST);
      LoRa.print(Flowmeter_Tot);
      delay(100);
      LoRa.print(Flowmeter_Flow);
      delay(100);
      LoRa.print(String("|"));
      LoRa.endPacket();
      delay(500);
      Serial.println(Flowmeter_Tot + Flowmeter_Flow + String("|"));
      Serial.println("*****************data sent*****************");
      Serial.println(" ");
      digitalWrite(LED, HIGH);  // turn the LED on (HIGH is the voltage level)
      delay(1000);              // wait for a second
      digitalWrite(LED, LOW);   // turn the LED off by making the voltage LOW
      delay(1000);
    } else if ((values[1] == 1) && (values[2] == 3)) {
      Heltec.display->display();
      LoRa.beginPacket();
      LoRa.setTxPower(14, RF_PACONFIG_PASELECT_PABOOST);
      LoRa.print(Flowmeter_Tot);
      delay(100);
      LoRa.print(Flowmeter_Flow);
      delay(100);
      LoRa.print(String("|"));
      LoRa.endPacket();
      delay(500);
      Serial.println(Flowmeter_Tot + Flowmeter_Flow + String("|"));
      Serial.println("*****************data sent*****************");
      Serial.println(" ");
      digitalWrite(LED, HIGH);  // turn the LED on (HIGH is the voltage level)
      delay(1000);              // wait for a second
      digitalWrite(LED, LOW);   // turn the LED off by making the voltage LOW
      delay(1000);
    } else if ((values[2] == 1) && (values[3] == 3)) {
      Heltec.display->display();
      LoRa.beginPacket();
      LoRa.setTxPower(14, RF_PACONFIG_PASELECT_PABOOST);
      LoRa.print(Flowmeter_Tot);
      delay(100);
      LoRa.print(Flowmeter_Flow);
      delay(100);
      LoRa.print(String("|"));
      LoRa.endPacket();
      delay(500);
      Serial.println(Flowmeter_Tot + Flowmeter_Flow + String("|"));
      Serial.println("*****************data sent*****************");
      Serial.println(" ");
      digitalWrite(LED, HIGH);  // turn the LED on (HIGH is the voltage level)
      delay(1000);              // wait for a second
      digitalWrite(LED, LOW);   // turn the LED off by making the voltage LOW
      delay(1000);
    } else {
      Serial.println("values[0]" + String(values[0]));
      Serial.println("values[1]" + String(values[1]));
      Serial.println("Modbus1... Conduction not matched... Data not sending...");
    }
  }
}
