#include "heltec.h"
#include <string.h>
#include <stdio.h>
#include <SoftwareSerial.h>  //EspSoftwareSerial by dirk kaar ver:8.1.0
#include "esp_system.h"
#include "esp_task_wdt.h"
#define rxpin 16
#define txpin 17
int pin = 4;
int flag = 0;
#ifdef ARDUINO_SAMD_MKRWAN1300
#error "This example is not compatible with the Arduino MKR WAN 1300 board!"
#endif
#define BAND 868E6  //you can set band here directly,e.g. 868E6,915E6
char c;
String p;
String myString;
char* STRCMP1 = 0;
char* STRCMP2 = 0;
char* STRCMP3 = 0;
char* STRCMP4 = 0;
char data0[120] = { 0 };
char data1[120] = { 0 };
char data2[120] = { 0 };
int flag0 = 0;
String firstPart;
String secondPart;
String thirdPart;
int pipeIndex;
  int pipeIndex2;
  int pipeIndex3;
void setup() {
  Heltec.begin(true /*DisplayEnable Enable*/, true /*Heltec.LoRa Disable*/, true /*Serial Enable*/, true /*PABOOST Enable*/, BAND /*long BAND*/);
  Serial.begin(9600);
  esp_task_wdt_init(50, false);  // Set timeout to 50 seconds
  esp_task_wdt_add(NULL);
  while (!Serial)
    ;
  pinMode(pin, OUTPUT);
  Serial.println("LoRa Receiver Callback");
  digitalWrite(pin, LOW);
  LoRa.onReceive(onReceive);
  LoRa.receive();
}

void loop() {
  
  esp_task_wdt_reset();
  if (Serial.available()) {
    delay(200);
    memset(data0, 0, sizeof(data0));
    Serial.readBytesUntil('\n', data0, 100);
    Serial.println("PC Serial received data(" + String(data0) + ")");
    STRCMP1 = strstr(data0, "*");
    STRCMP2 = strstr(data0, "@");
    if (STRCMP1) {
      Serial.println("gostatus commend sending to controller");
      memset(data1, 0, sizeof(data1));
      // delay(100);
      strcpy(data1, data0);
      // Serial.println("Received commond sending to the cooling tower(" + String(data1) + ")");
      delay(200);
      LoRa.beginPacket();
      LoRa.print(data1);
      LoRa.endPacket();
      delay(400);
      memset(data1, 0, sizeof(data1));
      memset(data0, 0, sizeof(data0));
    }
    if (STRCMP2) {
      delay(200);
      Serial.println("goaction commend sending to controller");
      memset(data2, 0, sizeof(data2));
      // delay(100);
      strcpy(data2, data0);
      // Serial.println("Received commond sending to the cooling tower(" + String(data2) + ")");
      delay(300);
      LoRa.beginPacket();
      LoRa.print(data2);
      LoRa.endPacket();
      delay(400);
      memset(data2, 0, sizeof(data2));
      memset(data0, 0, sizeof(data0));
    }
    delay(400);
    LoRa.receive();
  }
  if (flag0 == 1) {
    delay(300);
    Serial.println("lora data received uart done");
    digitalWrite(pin, HIGH);
    delay(300);
    if (pipeIndex != -1) {
      Serial.println(firstPart);
    }
    if (pipeIndex2 != -1) {
      Serial.println(secondPart);
    }
    if (pipeIndex3 != -1) {
      Serial.println(thirdPart);
    }
    myString.remove(0, 100);
    delay(400);
    digitalWrite(pin, LOW);
    flag0 = 0;
    LoRa.receive();
  }
  delay(2000);
}

void onReceive(int packetSize) {
  if (packetSize) {
    while (LoRa.available()) {
      c = ((char)LoRa.read());
      myString.concat(c);
    }
    pipeIndex = myString.indexOf('|');
    pipeIndex2 = myString.indexOf('|', pipeIndex + 1);
    pipeIndex3 = myString.indexOf('|', pipeIndex2 + 1);
    String firstPart = myString.substring(0, pipeIndex + 1);
    String secondPart = myString.substring(pipeIndex + 1, pipeIndex2 + 1);
    String thirdPart = myString.substring(pipeIndex2 + 1);
    // int pipeIndex = myString.indexOf('|');
    // if (pipeIndex != -1) {
    //   firstPart = myString.substring(0, pipeIndex + 1);
    //   secondPart = myString.substring(pipeIndex + 1);
    // } else {
    //   //Serial.println(myString);
    // }
    if (sizeof(myString) > 0) {
      Serial.println("flag high");
      flag0 = 1;
    }
  }
}