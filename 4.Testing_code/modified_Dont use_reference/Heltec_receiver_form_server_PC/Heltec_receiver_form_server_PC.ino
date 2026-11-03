/* 
  Check the new incoming messages, and print via serialin 115200 baud rate.
  
  by Aaron.Lee from HelTec AutoMation, ChengDu, China
  成都惠利特自动化科技有限公司
  www.heltec.cn
  
  this project also realess in GitHub:
  https://github.com/Heltec-Aaron-Lee/WiFi_Kit_series
*/

#include "heltec.h"
#include <string.h>
#include <stdio.h>
#include <SoftwareSerial.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
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
void setup() {
  //WIFI Kit series V1 not support Vext control
  Heltec.begin(true /*DisplayEnable Enable*/, true /*Heltec.LoRa Disable*/, true /*Serial Enable*/, true /*PABOOST Enable*/, BAND /*long BAND*/);
  Serial.begin(9600);
  while (!Serial)
    ;
  pinMode(pin, OUTPUT);
  Serial.println("LoRa Receiver Callback");
  digitalWrite(pin, LOW);
  lcd.begin(16, 2);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("MICHELIN LEVEL");
  lcd.setCursor(0, 1);
  lcd.print("MONITOR SYSTEM");
  LoRa.onReceive(onReceive);

  // put the radio into receive mode
  LoRa.receive();
}

void loop() {

  if (Serial.available())  //checking serial data
  {
    delay(200);
    memset(data0, 0, sizeof(data0));
    Serial.readBytesUntil('\n', data0, 100);
    Serial.println("PC Serial received data(" + String(data0) + ")");
    // Serial.print(data0);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("SERIAL DATA");
    lcd.setCursor(0, 1);
    lcd.print("RECEIVED FROM PI");
    STRCMP1 = strstr(data0, "*");
    STRCMP2 = strstr(data0, "@");
    if (STRCMP1)  //If data received sending via lora
    {
      delay(300);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("UPDATE STATUS");
      lcd.setCursor(0, 1);
      lcd.print("RECEIVED FROM PI");
      Serial.println("STRCMP1 Format matched");
      memset(data1, 0, sizeof(data1));
      delay(100);
      strcpy(data1, data0);
      Serial.println("Received commond sending to the cooling tower(" + String(data1) + ")");
      // Serial.println(data1);
      delay(200);
      LoRa.beginPacket();
      LoRa.print(data1);
      LoRa.endPacket();
      delay(400);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("SERIAL DATA");
      lcd.setCursor(0, 1);
      lcd.print("SENT VIA LORA");
      memset(data1, 0, sizeof(data1));
      memset(data0, 0, sizeof(data0));
    }
    if (STRCMP2) {
      delay(200);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("ACTION STATUS");
      lcd.setCursor(0, 1);
      lcd.print("RECEIVED FROM PI");
      Serial.println("STRCMP2 Format matched");
      memset(data2, 0, sizeof(data2));
      delay(100);
      strcpy(data2, data0);
      Serial.println("Received commond sending to the cooling tower(" + String(data2) + ")");
      delay(300);
      LoRa.beginPacket();
      LoRa.print(data2);
      LoRa.endPacket();
      delay(400);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("SERIAL DATA");
      lcd.setCursor(0, 1);
      lcd.print("SENT VIA LORA");
      // Serial.println(data2);
      memset(data2, 0, sizeof(data2));
      memset(data0, 0, sizeof(data0));
    }
    delay(400);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("JUNK DATA");
    lcd.setCursor(0, 1);
    lcd.print("RECEIVED FROM RPI");
    LoRa.receive();
  }
  if (flag0 == 1)  //If lora data received means sending data via serial
  {
    delay(300);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("LORA DATA");
    lcd.setCursor(0, 1);
    lcd.print("RECEIVED");
    Serial.println("lora data received uart done");
    digitalWrite(pin, HIGH);
    delay(300);
    //Serial.println(myString);
    Serial.println(firstPart);
    Serial.println(secondPart);
    // Serial.println(thirdPart);
    myString.remove(0, 100);
    //Serial.println("string removed");
    //Serial.println(myString);
    delay(400);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("LORA DATA SENT");
    lcd.setCursor(0, 1);
    lcd.print("TO RPI VIA UART");
    digitalWrite(pin, LOW);
    flag0 = 0;
    LoRa.receive();
  }
  delay(2000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("WAITING FOR DATA");
  lcd.setCursor(0, 1);
  lcd.print("FROM RPI AND HELTEC");
}

void onReceive(int packetSize) {
  if (packetSize) {
    // read packet
    while (LoRa.available()) {
      c = ((char)LoRa.read());
      myString.concat(c);
    }

    int pipeIndex = myString.indexOf('|');
    if (pipeIndex != -1) {
      firstPart = myString.substring(0, pipeIndex + 1);
      secondPart = myString.substring(pipeIndex + 1);
      // thirdPart = myString.substring(pipeIndex + 1);

      //Serial.println(firstPart);
      //Serial.println(secondPart);
    } else {
      //Serial.println(myString);
    }
    //Serial.println(myString);
    if (sizeof(myString) > 0) {
      Serial.println("flag high");
      flag0 = 1;
    }
  }
}
/*
void onReceive(int packetSize) {
  if (packetSize) {
    // read packet
    while (LoRa.available()) {
      c = ((char)LoRa.read());
      myString.concat(c);
    }

    int pipeIndex1 = myString.indexOf('|');
    if (pipeIndex1 != -1) {
      firstPart = myString.substring(0, pipeIndex1);
      int pipeIndex2 = myString.indexOf('|', pipeIndex1 + 1);
      if (pipeIndex2 != -1) {
        secondPart = myString.substring(pipeIndex1 + 1, pipeIndex2);
        int pipeIndex3 = myString.indexOf('|', pipeIndex2 + 1);
        if (pipeIndex3 != -1) {
          thirdPart = myString.substring(pipeIndex2 + 1, pipeIndex3);
        } else {
          thirdPart = myString.substring(pipeIndex2 + 1);
        }
      } else {
        secondPart = myString.substring(pipeIndex1 + 1);
      }
    } else {
      firstPart = myString;
    }

    if (firstPart.length() > 0 || secondPart.length() > 0 || thirdPart.length() > 0) {
      Serial.println("flag high");
      flag0 = 1;
    }
  }
}*/