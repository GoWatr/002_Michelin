#include <SPI.h>
#include <LoRa.h>
#include <string.h>
#include <stdio.h>
#include <SoftwareSerial.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
#define rxpin 16                                                                
#define txpin 17 
int pin = 4 ;
int flag = 0;
#ifdef ARDUINO_SAMD_MKRWAN1300
#error "This example is not compatible with the Arduino MKR WAN 1300 board!"
#endif
const int csPin = 18;          // LoRa radio chip select
const int resetPin = 14;       // LoRa radio reset
const int irqPin = 26;         // change for your board; must be a hardware interrupt pin
char c;
String p;
String myString;
char*STRCMP1 = 0;
char*STRCMP2 = 0;
char*STRCMP3 = 0;
char*STRCMP4 = 0;
char data0[120]={0};
char data1[120]={0};
char data2[120] = {0};
int flag0 = 0;
void setup() {
  Serial2.begin(9600);
  Serial.begin(115200);
  while (!Serial);
  pinMode(pin, OUTPUT);
  Serial.println("LoRa Receiver Callback");
  LoRa.setPins(csPin, resetPin, irqPin);
  if (!LoRa.begin(868E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }

  // Uncomment the next line to disable the default AGC and set LNA gain, values between 1 - 6 are supported
  // LoRa.setGain(6);
    digitalWrite(pin, LOW);
    lcd.begin(16,2);
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
  
   if(Serial2.available())                           //checking serial data 
    {  
      delay(200);    
      Serial2.readBytesUntil('\n',data0,100);
      Serial.println(data0); 
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("SERIAL DATA");
      lcd.setCursor(0,1);
      lcd.print("RECEIVED FROM PI");     
      STRCMP1 = strstr(data0,"gostatus");
      STRCMP2 = strstr(data0,"govalve");
      if(STRCMP1)                                  //If data received sending via lora
      {
        delay(300);
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("UPDATE STATUS");
        lcd.setCursor(0,1);
        lcd.print("RECEIVED FROM PI");
        Serial.println("STRCMP1");
        memset(data1,0,sizeof(data1));
        delay(100);
        strcpy(data1,data0);
        Serial.println("data is");
        Serial.println(data1);
        delay(200);
        LoRa.beginPacket();
        LoRa.print(data1);
        LoRa.endPacket();
        delay(400);
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("SERIAL DATA");
        lcd.setCursor(0,1);
        lcd.print("SENT VIA LORA");
        memset(data1,0,sizeof(data1));
        memset(data0,0,sizeof(data0));
     }
     if(STRCMP2)
     {
      delay(200);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("ACTION STATUS");
      lcd.setCursor(0,1);
      lcd.print("RECEIVED FROM PI");
      Serial.println("STRCMP2");
      memset(data2,0,sizeof(data2));
      delay(100);
      strcpy(data2,data0);
      delay(300);
      LoRa.beginPacket();
      LoRa.print(data2);
      LoRa.endPacket();
      delay(400);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("SERIAL DATA");
      lcd.setCursor(0,1);
      lcd.print("SENT VIA LORA");
      Serial.println("data is");
      Serial.println(data2);
      memset(data2,0,sizeof(data2));
      memset(data0,0,sizeof(data0));
     } 
     delay(400);
     lcd.clear();
     lcd.setCursor(0, 0);
     lcd.print("JUNK DATA");
     lcd.setCursor(0,1);
     lcd.print("RECEIVED FROM RPI");  
     LoRa.receive();
    }
    if(flag0 == 1)                               //If lora data received means sending data via serial
    {
      delay(300);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("LORA DATA");
      lcd.setCursor(0,1);
      lcd.print("RECEIVED");
      Serial.println("lora data received uart done");
      digitalWrite(pin, HIGH);
      delay(300);
      Serial2.println(myString);
      myString.remove(0, 100);
      //Serial.println("string removed");
      //Serial.println(myString);
      delay(400);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("LORA DATA SENT");
      lcd.setCursor(0,1);
      lcd.print("TO RPI VIA UART");
      digitalWrite(pin, LOW);
      flag0 = 0;
      LoRa.receive();

   }
   delay(2000);
   lcd.clear();
   lcd.setCursor(0, 0);
   lcd.print("WAITING FOR DATA");
   lcd.setCursor(0,1);
   lcd.print("FROM RPI AND HELTEC");
    
}

void onReceive(int packetSize) {                           //lora receive callback function 
  // received a packet
//  Serial.print("Received packet '");

  // read packet
  //myString.remove(0, 100);
  while(LoRa.available()) 
    {
      c = ((char)LoRa.read());
      myString.concat(c);
      //flag = 1;
      //Serial.print(myString);
    }
    Serial.println(myString);
    if(sizeof(myString)>0)
     {
       Serial.println("flag high");
       flag0 = 1;    
     }

    
  
}
