#include "heltec.h"
#include <SoftwareSerial.h>
#include "esp_system.h"
#include "esp_task_wdt.h"
#define BAND 868E6  //you can set band here directly,e.g. 868E6,915E6
#define rxpin 16    //lora serial rx pin
#define txpin 17    //lora serial tx pin
char value1, value2;
String myString, myString1, myString2;
char data0[120] = { 0 };
char data1[120] = { 0 };  //character buffer
char data2[120] = { 0 };
char data3[120] = { 0 };
char data4[120] = { 0 };
char data5[120] = { 0 };
char data6[120] = { 0 };
char data7[120] = { 0 };
char data8[120] = { 0 };
char* STRCMP1 = 0;  //character pointer
char* STRCMP2 = 0;
char* STRCMP3 = 0;
char* STRCMP4 = 0;
char* STRCMP5 = 0;
char* STRCMP6 = 0;
char* STRCMP7 = 0;
char* STRCMP8 = 0;
int flag0 = 0;
SoftwareSerial mySerial(rxpin, txpin);

void setup() {
  Heltec.begin(true /*DisplayEnable Enable*/, true /*Heltec.LoRa Disable*/, true /*Serial Enable*/, true /*PABOOST Enable*/, BAND /*long BAND*/);
  Serial.begin(9600);
  mySerial.begin(9600);
  esp_task_wdt_init(60, false);  // Set timeout to 5 seconds
  esp_task_wdt_add(NULL);
  Serial.println("lora sending");
  LoRa.onReceive(onReceive);
  LoRa.receive();
}

void loop() {
  esp_task_wdt_reset();      // Reset the watchdog timer
  delay(1000);
  if (mySerial.available())  //checking serial data from arduino
  {
    memset(data0, 0, sizeof(data0));
    Serial.println("inside serial check");
    mySerial.readBytesUntil('\n', data0, 120);  //if the serial data received from arduino stored in data0
    Serial.println(data0);
    delay(500);
    STRCMP1 = strstr(data0, "CT");   //Cooling tank level status - Controller -> Server
    STRCMP2 = strstr(data0, "&");    //Valve status - Controller -> Server
    STRCMP3 = strstr(data0, "*");    //Mode status - Server -> Controller
    STRCMP4 = strstr(data0, "FMA");  //FM status - Controller -> Server
    STRCMP5 = strstr(data0, "@");    //Valve status - Server -> Controller
    if (STRCMP1)                     //if data matched sending the received data from arduino to RPI HELTEC via RF communication same for all from STRCMP1 TO STRCMP8
    {
      Serial.println("STRCMP1");
      memset(data1, 0, sizeof(data1));
      strcpy(data1, data0);
      Serial.println("data is");
      Serial.println(data1);
      LoRa.setTxPower(14, RF_PACONFIG_PASELECT_PABOOST);
      LoRa.beginPacket();
      LoRa.print(data1);
      LoRa.endPacket();
      memset(data1, 0, sizeof(data1));
      memset(data0, 0, sizeof(data0));
    }
    if (STRCMP2) {
      Serial.println("STRCMP2");
      memset(data2, 0, sizeof(data2));
      strcpy(data2, data0);
      LoRa.setTxPower(14, RF_PACONFIG_PASELECT_PABOOST);
      LoRa.beginPacket();
      LoRa.print(data2);
      LoRa.endPacket();
      Serial.println("data is");
      Serial.println(data2);
      memset(data2, 0, sizeof(data2));
      memset(data0, 0, sizeof(data0));
    }
    if (STRCMP3) {
      Serial.println("STRCMP3");
      memset(data3, 0, sizeof(data3));
      strcpy(data3, data0);
      LoRa.setTxPower(14, RF_PACONFIG_PASELECT_PABOOST);
      LoRa.beginPacket();
      LoRa.print(data3);
      LoRa.endPacket();
      Serial.println("data is");
      Serial.println(data3);
      memset(data3, 0, sizeof(data3));
      memset(data0, 0, sizeof(data0));

      // flag2 =1;
    }
    if (STRCMP4) {
      Serial.println("STRCMP4");
      memset(data4, 0, sizeof(data4));
      strcpy(data4, data0);
      LoRa.setTxPower(14, RF_PACONFIG_PASELECT_PABOOST);
      LoRa.beginPacket();
      LoRa.print(data4);
      LoRa.endPacket();
      Serial.println("data is");
      Serial.println(data4);
      memset(data4, 0, sizeof(data4));
      memset(data0, 0, sizeof(data0));

      //flag3 =1;
    }
    if (STRCMP5) {
      Serial.println("STRCMP5");
      memset(data5, 0, sizeof(data5));
      strcpy(data5, data0);
      LoRa.setTxPower(14, RF_PACONFIG_PASELECT_PABOOST);
      LoRa.beginPacket();
      LoRa.print(data5);
      LoRa.endPacket();
      Serial.println("data is");
      Serial.println(data5);
      memset(data5, 0, sizeof(data5));
      memset(data0, 0, sizeof(data0));

      //flag3 =1;
    }
    if (STRCMP6) {
      Serial.println("STRCMP6");
      memset(data6, 0, sizeof(data6));
      strcpy(data6, data0);
      LoRa.setTxPower(14, RF_PACONFIG_PASELECT_PABOOST);
      LoRa.beginPacket();
      LoRa.print(data6);
      LoRa.endPacket();
      Serial.println("data is");
      Serial.println(data6);
      memset(data6, 0, sizeof(data6));
      memset(data0, 0, sizeof(data0));
    }
    if (STRCMP7) {
      Serial.println("STRCMP7");
      memset(data7, 0, sizeof(data7));
      strcpy(data7, data0);
      LoRa.setTxPower(14, RF_PACONFIG_PASELECT_PABOOST);
      LoRa.beginPacket();
      LoRa.print(data7);
      LoRa.endPacket();
      Serial.println("data is");
      Serial.println(data7);
      memset(data7, 0, sizeof(data7));
      memset(data0, 0, sizeof(data0));
    }
    if (STRCMP8) {
      Serial.println("STRCMP8");
      memset(data8, 0, sizeof(data8));
      strcpy(data8, data0);
      LoRa.setTxPower(14, RF_PACONFIG_PASELECT_PABOOST);
      LoRa.beginPacket();
      LoRa.print(data8);
      LoRa.endPacket();
      Serial.println("data is");
      Serial.println(data8);
      memset(data8, 0, sizeof(data8));
      memset(data0, 0, sizeof(data0));
    }
    LoRa.receive();
  }
  if (flag0 == 1) {
    Serial.println("uart done");  //if flag0 =1 means lora data received from RPI heltec we are sending the data via serial to arduino
    mySerial.println(myString1);
    myString1.remove(0, 100);
    Serial.println("string removed");
    Serial.println(myString1);
    flag0 = 0;
    LoRa.receive();
  }
  delay(500);
}


void onReceive(int packetSize) {
  // try to parse packet
  myString1.remove(0, 100);

  if (packetSize) {
    // received a packet
    Serial.print("Received packet ");
    // read packet
    while (LoRa.available()) {
      value2 = ((char)LoRa.read());
      myString1.concat(value2);
    }
    Serial.println(myString1);
    if (sizeof(myString1) > 0) {
      Serial.println("flag high");
      flag0 = 1;
    }
  }
}