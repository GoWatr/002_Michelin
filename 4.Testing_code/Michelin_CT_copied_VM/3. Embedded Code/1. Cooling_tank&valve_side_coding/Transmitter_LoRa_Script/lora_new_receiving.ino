
#include <SPI.h>
#include <LoRa.h>
#include <SoftwareSerial.h>
#include "images.h"
//#include "heltec.h"

#define rxpin 16                //lora serial rx pin                                                   
#define txpin 17                //lora serial tx pin
char value1,value2;
String myString,myString1,myString2;
const int csPin = 18;          // LoRa radio chip select
const int resetPin = 14;       // LoRa radio reset
const int irqPin = 26;         // change for your board; must be a hardware interrupt pin
char data0[120]={0};
char data1[120]={0};           //character buffer
char data2[120] = {0};
char data3[120] = {0};
char data4[120] = {0};
char data5[120] = {0};
char data6[120] = {0};
char data7[120] = {0};
char data8[120] = {0};
char*STRCMP1 = 0;              //character pointer
char*STRCMP2 = 0;
char*STRCMP3 = 0;
char*STRCMP4 = 0;
char*STRCMP5 = 0;
char*STRCMP6 = 0;
char*STRCMP7 = 0;
char*STRCMP8 = 0;
int flag0 = 0;
SoftwareSerial mySerial(rxpin,txpin);

void setup() 
{
  Serial.begin(115200);       
  mySerial.begin(9600);
  Serial.println("lora sending");
  //mySerial.println("lora sending");
  //Serial2.println("lora sender"); 
  //mySerial.println("Receiver"); 
  LoRa.setPins(csPin, resetPin, irqPin);
  if (!LoRa.begin(868E6)) {
    Serial2.println("Starting LoRa failed!");
    while (1);
  }
    LoRa.onReceive(onReceive);

  // put the radio into receive mode
  LoRa.receive();
  
}

void loop()
  {
   if (mySerial.available())                             //checking serial data from arduino
   {
    
    mySerial.readBytesUntil('\n',data0,120);            //if the serial data received from arduino stored in data0
    Serial.println(data0);
    delay(500);
    STRCMP1 = strstr(data0,"GOWATRONE");                //comparing the serial received data in data0 with ID
    STRCMP2 = strstr(data0,"GOWATRTWO");
    STRCMP3 = strstr(data0,"GOWATRTHR");
    STRCMP4 = strstr(data0,"GOWATRFOUR");
    STRCMP5 = strstr(data0,"GOWATRFIVE");
    STRCMP6 = strstr(data0,"gostatus");
    STRCMP7 = strstr(data0,"govalve");
    STRCMP8 = strstr(data0,"GOWATRSIX");
    if(STRCMP1)                                        //if data matched sending the received data from arduino to RPI HELTEC via RF communication same for all from STRCMP1 TO STRCMP8
     {
     Serial.println("STRCMP1");                        
     memset(data1,0,sizeof(data1));
      strcpy(data1,data0);
      Serial.println("data is");
      Serial.println(data1);
      LoRa.beginPacket();
      LoRa.print(data1);
      LoRa.endPacket();
      memset(data1,0,sizeof(data1));
      memset(data0,0,sizeof(data0));
      //LoRa.receive();
      //flag0 = 1;
     }
     if(STRCMP2)
     {
      Serial.println("STRCMP2");
      memset(data2,0,sizeof(data2));
      strcpy(data2,data0);
      LoRa.beginPacket();
      LoRa.print(data2);
      LoRa.endPacket();
      Serial.println("data is");
      Serial.println(data2);
      memset(data2,0,sizeof(data2));
      memset(data0,0,sizeof(data0));
     // LoRa.receive();
      //flag1 =1;
     }
     if(STRCMP3)
     {
      Serial.println("STRCMP3");
      memset(data3,0,sizeof(data3));
      strcpy(data3,data0);
      LoRa.beginPacket();
      LoRa.print(data3);
      LoRa.endPacket();
      Serial.println("data is");
      Serial.println(data3);
      memset(data3,0,sizeof(data3));
      memset(data0,0,sizeof(data0));
      
     // flag2 =1;
     }
     if(STRCMP4)
     {
      Serial.println("STRCMP4");
      memset(data4,0,sizeof(data4));
      strcpy(data4,data0);
      LoRa.beginPacket();
      LoRa.print(data4);
      LoRa.endPacket();
      Serial.println("data is");
      Serial.println(data4);
      memset(data4,0,sizeof(data4));
      memset(data0,0,sizeof(data0));
      
      //flag3 =1;
     }
     if(STRCMP5)
     {
      Serial.println("STRCMP5");
      memset(data5,0,sizeof(data5));
      strcpy(data5,data0);
      LoRa.beginPacket();
      LoRa.print(data5);
      LoRa.endPacket();
      Serial.println("data is");
      Serial.println(data5);
      memset(data5,0,sizeof(data5));
      memset(data0,0,sizeof(data0));
      
      //flag3 =1;
     }
     if(STRCMP6)
     {
      Serial.println("STRCMP6");
      memset(data6,0,sizeof(data6));
      strcpy(data6,data0);
      LoRa.beginPacket();
      LoRa.print(data6);
      LoRa.endPacket();
      Serial.println("data is");
      Serial.println(data6);
      memset(data6,0,sizeof(data6));
      memset(data0,0,sizeof(data0));
     }
     if(STRCMP7)
     {
      Serial.println("STRCMP7");
      memset(data7,0,sizeof(data7));
      strcpy(data7,data0);
      LoRa.beginPacket();
      LoRa.print(data7);
      LoRa.endPacket();
      Serial.println("data is");
      Serial.println(data7);
      memset(data7,0,sizeof(data7));
      memset(data0,0,sizeof(data0));
     }  
     if(STRCMP8)
     {
      Serial.println("STRCMP8");
      memset(data8,0,sizeof(data8));
      strcpy(data8,data0);
      LoRa.beginPacket();
      LoRa.print(data8);
      LoRa.endPacket();
      Serial.println("data is");
      Serial.println(data8);
      memset(data8,0,sizeof(data8));
      memset(data0,0,sizeof(data0));
     }        
    LoRa.receive();
   }
   if(flag0 == 1)
   {
    Serial.println("uart done");                                                       //if flag0 =1 means lora data received from RPI heltec we are sending the data via serial to arduino
    mySerial.println(myString1);
    myString1.remove(0, 100);
    Serial.println("string removed");
    Serial.println(myString1);
    flag0 = 0;
    LoRa.receive();
      
   }
   delay(500);
}
  
  
void onReceive(int packetSize) {                            //Lora onReceive function here we are concatenating the data and stored in string variable
  // received a packet
  myString1.remove(0, 100);
  Serial.print("Received packet '");

  // read packet
  while(LoRa.available()) 
    {
      value2 = ((char)LoRa.read());
      myString1.concat(value2);
      
      //Serial.print(myString);
    }
  Serial.println(myString1);  
  if(sizeof(myString1)>0)
  {
    Serial.println("flag high");
    flag0 = 1;                                                 //If we add anything inside interrupt function error occurredso to avoid that we are raising flag here
   }
   
}
