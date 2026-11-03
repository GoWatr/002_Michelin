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
void setup() {
  Heltec.begin(true /*DisplayEnable Enable*/, true /*Heltec.LoRa Disable*/, true /*Serial Enable*/, true /*PABOOST Enable*/, BAND /*long BAND*/);
  Serial.begin(9600);
  esp_task_wdt_init(50, false);  // Set timeout to 50 seconds
  esp_task_wdt_add(NULL);
}

void loop() {
  esp_task_wdt_reset();
  delay(2000);
  String value = "123|33456|1234|";
  myString.concat(value);
  // c = ((char)value);
  // myString.concat(c);
  int pipeIndex = myString.indexOf('|');
  int pipeIndex2 = myString.indexOf('|', pipeIndex + 1);
  int pipeIndex3 = myString.indexOf('|', pipeIndex2 + 1);
  String firstPart = myString.substring(0, pipeIndex + 1);
  String secondPart = myString.substring(pipeIndex + 1, pipeIndex2 + 1);
  String thirdPart = myString.substring(pipeIndex2 + 1);
  if (sizeof(myString) > 0) {
    Serial.println("flag high");
    flag0 = 1;
  }

  if (flag0 == 1) {
    delay(300);
    Serial.println("lora data received uart done");
    digitalWrite(pin, HIGH);
    delay(300);
    Serial.println(firstPart);
    Serial.println(secondPart);
    Serial.println(thirdPart);
    myString.remove(0, 100);
    delay(400);
    digitalWrite(pin, LOW);
    flag0 = 0;
    // LoRa.receive();
  }
}