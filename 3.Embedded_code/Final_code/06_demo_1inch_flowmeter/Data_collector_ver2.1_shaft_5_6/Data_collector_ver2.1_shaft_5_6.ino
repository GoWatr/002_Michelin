#include <Arduino.h>
#include <HardwareSerial.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <string.h>
#define LED_BUILTIN 2

const uint8_t deviceIDs[] = {0x62, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69, 0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77};
const String deviceNames[] = {"GWFMBH0611", "GWFMBH0536", "GWFMBH0248", "GWFMBH0267", "GWFMBH0287", "GWFMBH0319", "GWFMBH0342", "GWFMBH0369", "GWFMBH0383", "GWFMBH0409", "GWFMBH0"/*nil*/, "GWFMBH0614", "GWFMBH0"/*nil*/, "GWFMBH0449", "GWFMBH0545", "GWFMBH0473"};// 2nos id need
const uint8_t deviceIDs2[] = {0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49, 0x50, 0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57};
const String deviceNames2[] = {"GWFMBH0168", "GWFMBH0208", "GWFMBH0228", "GWFMBH0251", "GWFMBH0269", "GWFMBH0290", "GWFMBH0569", "GWFMBH0345", "GWFMBH0512", "GWFMBH0445", "GWFMBH0446", "GWFMBH0628", "GWFMBH0428", "GWFMBH0445", "GWFMBH0447", "GWFMBH0423", "GWFMBH0635"};

#define FM_REQ 0x01
#define FM_RES 0x02
#define RX_PIN 16
#define TX_PIN 17
#define RX_PIN2 26
#define TX_PIN2 27
#define SERIAL_BAUD_RATE 9600  
#define CURRENT_FW_VERSION 1
#define writeInterval 2000
int LengthADD = sizeof(deviceIDs) / sizeof(deviceIDs[0]);
int counter = 0;
int LengthADD2 = sizeof(deviceIDs2) / sizeof(deviceIDs2[0]);;
int counter2 = 0;
int counter30delay = 0;
HardwareSerial RS485(1);
HardwareSerial RS4852(2); 

const size_t packet_length = 2;
uint8_t rx_buffer[128];

const size_t packet_length2 = 2;
uint8_t rx_buffer2[128];

unsigned int highWord, lowWord, Flow;
unsigned long long dec_value;
unsigned int highWord2, lowWord2, Flow2;
unsigned long long dec_value2;
unsigned long Totalizer_F1;
unsigned long Flowrate_F1;
unsigned long Totalizer_F2;
unsigned long Flowrate_F2;

String datatosend = "";
String datatosend2 = "";

const char *ssid = "BAASHYAAM";
const char *password = "baashyaam@123";
const char *serverUrl = "http://gowatr.com/wms/pushdata/flowset.php?project_id=baashyaam&data=";

void setup() {
  Serial.begin(SERIAL_BAUD_RATE);
  RS485.begin(SERIAL_BAUD_RATE, SERIAL_8N1, RX_PIN, TX_PIN);
  RS4852.begin(SERIAL_BAUD_RATE, SERIAL_8N1, RX_PIN2, TX_PIN2);
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.println("Plutus Flowmeter Data collector");

  WiFi.begin(ssid, password);
    if (WiFi.status() == WL_CONNECTED) {
      Serial.println("WiFi connected");
      digitalWrite(LED_BUILTIN, HIGH);
  }
}

void loop() {
    if (WiFi.status() != WL_CONNECTED) {
    WiFi.begin(ssid, password);
    Serial.println("Attempting to reconnect to WiFi...");
    while (WiFi.status() != WL_CONNECTED) { 
      WiFi.begin(ssid, password);
      delay(1000);
      Serial.println("Connecting to WiFi...");
      digitalWrite(LED_BUILTIN, LOW);
    }

    if (WiFi.status() == WL_CONNECTED) {
      Serial.println("Reconnected to WiFi");
      digitalWrite(LED_BUILTIN, HIGH);
    } else {
      Serial.println("Failed to reconnect to WiFi");
    }
   }
   counter30delay++;
   delay(1000);
   if (counter30delay == 30)
   {
   counter++;
  if (counter <= LengthADD) {
  delay(1000);
  sendData(deviceIDs[counter - 1], FM_REQ);
  }else if (counter == (LengthADD + 1)) {
  counter = 0; // Reset counter
  }
  delay(writeInterval);
    
    if (RS485.available() > 0) {
    Serial.println("Serial 1 Data Received");
    memset(rx_buffer, 0, sizeof(rx_buffer));
    int len = RS485.readBytes(rx_buffer, sizeof(rx_buffer));
    for (int i = 0; i < sizeof(deviceIDs) / sizeof(deviceIDs[0]); i++) {
      if (len > 0 && rx_buffer[0] == deviceIDs[i] && rx_buffer[2] == FM_RES) {
        Serial.println("***********************************");
        for (int j = 0; j < 4; j++)
        {
        Serial.print(rx_buffer[j], HEX);
        Serial.print(' ');
        }
        Serial.println(' ');
        Serial.print("Data request received from Flowmeter for ");
        Serial.println(deviceIDs[i], HEX);
        processReceivedData1();
        datatosend ="flowmeter_id:" + deviceNames[i] + ",flowrate:" + String(Flowrate_F1) + ",totalizer:" + String(static_cast<unsigned long>(Totalizer_F1)) + ",ver:" + String(CURRENT_FW_VERSION);
        Serial.println(datatosend);
        sendToServer(datatosend);
        Serial.println("***********************************");
        Serial.println(' '); Serial.println(' '); Serial.println(' ');
      }
    }
  }
}
  if (counter30delay == 60)
  {
  counter30delay = 0;
  counter2++;
  if (counter2 <= LengthADD2) {
  delay(1000);
  sendData2(deviceIDs2[counter2 - 1], FM_REQ);
  }else if (counter2 == (LengthADD2 + 1)) {
  counter2 = 0; // Reset counter
  }
  delay(writeInterval);
  if (RS4852.available() > 0) {
    Serial.println("serial 2 Data Received");
    memset(rx_buffer2, 0, sizeof(rx_buffer2));
    int len = RS4852.readBytes(rx_buffer2, sizeof(rx_buffer2));
    for (int i = 0; i < sizeof(deviceIDs2) / sizeof(deviceIDs2[0]); i++) {
      if (len > 0 && rx_buffer2[0] == deviceIDs2[i] && rx_buffer2[2] == FM_RES) {
        Serial.println("***********************************");
        for (int j = 0; j < 4; j++)
        {
        Serial.print(rx_buffer2[j], HEX);
        Serial.print(' ');
        }
        Serial.println(' ');
        Serial.print("Data request received from Flowmeter for ");
        Serial.println(deviceIDs2[i], HEX);
        processReceivedData2();
        datatosend2 ="flowmeter_id:" + deviceNames2[i] + ",flowrate:" + String(Flowrate_F2) + ",totalizer:" + String(static_cast<unsigned long>(Totalizer_F2)) + ",ver:" + String(CURRENT_FW_VERSION);
        Serial.println(datatosend2);
        sendToServer(datatosend2);
        Serial.println("***********************************");
        Serial.println(' '); Serial.println(' '); Serial.println(' ');
      }
    }
  }
}
}

void sendData(uint8_t id, uint8_t code) {
  Serial.print("||ADDRESS = ");
  Serial.print(counter);
  Serial.print(" || ID = ");
  Serial.print(id, HEX);
  Serial.print(" || CODE = ");
  Serial.println(code, HEX);
  uint8_t packet[packet_length] = {id, code};
  delay(100);
  RS485.write(packet, packet_length);
  delay(200);
  RS485.flush();
}

void sendData2(uint8_t id, uint8_t code) {
  Serial.print("||ADDRESS = ");
  Serial.print(counter);
  Serial.print(" || ID = ");
  Serial.print(id, HEX);
  Serial.print(" || CODE = ");
  Serial.println(code, HEX);
  uint8_t packet2[packet_length2] = {id, code};
  delay(100);
  RS4852.write(packet2, packet_length2);
  delay(200);
  RS4852.flush();
}

void processReceivedData1() {
  Serial.println("***********************************");
  for (int i = 0; i < 22; i++) {
    Serial.print(rx_buffer[i], HEX);
    Serial.print(" ");
  }
  Serial.println();
  Flow = (rx_buffer[1] << 8) | rx_buffer[3];

  highWord = (rx_buffer[4] << 8) | rx_buffer[6];
  lowWord = (rx_buffer[8] << 8) | rx_buffer[10];
  dec_value = ((unsigned long long)lowWord << 16) | highWord;
  Totalizer_F1 = ((rx_buffer[4] << 40) | (rx_buffer[6] << 32) | (rx_buffer[8] << 24) | (rx_buffer[10] << 16) | (rx_buffer[12] << 8) | rx_buffer[14]);
  Flowrate_F1 = ((rx_buffer[16] << 16) | (rx_buffer[18] << 8) | rx_buffer[20]);
        
  Serial.print("The combined result before transmitting is : ");
  Serial.println(static_cast<unsigned long>(Totalizer_F1));
  Serial.println("***********************************");
}

void processReceivedData2() {
  Serial.println("***********************************");
  for (int i = 0; i < packet_length2 + 15; i++) {
    Serial.print(rx_buffer2[i], HEX);
    Serial.print(" ");
  }
  Serial.println();
  Flow2 = (rx_buffer2[1] << 8) | rx_buffer2[3];

  highWord2 = (rx_buffer2[4] << 8) | rx_buffer2[6];
  lowWord2 = (rx_buffer2[8] << 8) | rx_buffer2[10];
  dec_value2 = ((unsigned long long)lowWord2 << 16) | highWord2;
  Totalizer_F2 = ((rx_buffer2[4] << 40) | (rx_buffer2[6] << 32) | (rx_buffer2[8] << 24) | (rx_buffer2[10] << 16) | (rx_buffer2[12] << 8) | rx_buffer2[14]);
  Flowrate_F2 = ((rx_buffer2[16] << 16) | (rx_buffer2[18] << 8) | rx_buffer2[20]);
        
  Serial.print("The combined result before transmitting is : ");
  Serial.println(static_cast<unsigned long>(Totalizer_F2));
  Serial.println("***********************************");
}

void sendToServer(String data) {
  HTTPClient http;
  String url = String(serverUrl) + data;
  Serial.println(url);
  http.begin(url);

  int httpResponseCode = http.GET();
  if (httpResponseCode > 0) {
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
  } else {
    Serial.println("HTTP Request failed");
  }
  http.end();
}
