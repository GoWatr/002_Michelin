#include "functions.h"
#include <Arduino.h>
#include <string.h>
#include <HardwareSerial.h>
#define LED_BUILTIN 2
#define DEVICE_ADDRESS 0x72
#define FM1_ADDRESS 0x05
#define FM2_ADDRESS 0x05
#define FM_REQ 0x01
#define FM_RES 0x02
#define MDL_REQ 0x04
#define MDL_RES 0x05

HardwareSerial SerialPort1(1);
HardwareSerial SerialPort2(2);
int i, j, k, l = 0;
int counter = 0;
int request_switch = 1;
const size_t packet_length = 10;
uint8_t rx_buffer1[128];
uint8_t rx_buffer2[128];
byte byteData[7];
byte byteData2[7];
int restart_counter = 0;

void setup() {
  Serial.begin(115200);
  SerialPort1.begin(9600, SERIAL_8N1, 26, 27);
  SerialPort2.begin(9600, SERIAL_8N1, 16, 17);
  pinMode (LED_BUILTIN, OUTPUT);
  Serial.println("Initializing....");
  lcd_startup();
}

void send_request() {
  counter++;
  restart_counter++;
  delay(1000);
  //Serial.println("The current counter is " + String(counter));
  if (restart_counter >= 21600) {
    restart_counter = 0;
    //  ESP.restart();
  }
  else {
  }

  if (counter == 3) { //10******************************************
    counter = 0;
    if (request_switch == 1) {
      request_switch = 0;
      uint8_t packet[packet_length] = {FM1_ADDRESS, FM_REQ};
      delay(100);
      SerialPort2.write(packet, packet_length);
      delay(200);
      SerialPort2.flush();
      Serial.println("Request sent for Flowmeter 1 with ID" + String(FM1_ADDRESS, HEX));
      //lcd_send_req_1();
    }
    else {
      request_switch = 1; //1******************************************
      uint8_t packet[packet_length] = {FM2_ADDRESS, FM_REQ};
      delay(100);
      SerialPort2.write(packet, packet_length);
      delay(200);
      SerialPort2.flush();
      Serial.println("Request sent for Flowmeter 2 with ID" + String(FM2_ADDRESS, HEX));
      //lcd_send_req_2();
    }
  }
  delay(100);
}

void flowmeter_data()
{
  if (SerialPort2.available() > 0) {
    int len2 = SerialPort2.readBytes(rx_buffer2, sizeof(rx_buffer2));
    if (len2 > 0) {
      Serial.println("***********************************");
      for (i = 0; i < 4; i++)
      {
        Serial.print(rx_buffer2[i], HEX);
      }
      Serial.println("  ");

      if ((rx_buffer2[0] == FM1_ADDRESS) && (rx_buffer2[2] == FM_RES)) {
        for (i = 4; i < 22; i++)
        {
          Serial.print(rx_buffer2[i], HEX);
        }
        Serial.println("  ");
        Totalizer_F1 = ((rx_buffer2[4] << 40) | (rx_buffer2[6] << 32) | (rx_buffer2[8] << 24) | (rx_buffer2[10] << 16) | (rx_buffer2[12] << 8) | rx_buffer2[14]);
        Flowrate_F1 = ((rx_buffer2[16] << 16) | (rx_buffer2[18] << 8) | rx_buffer2[20]);
        Serial.println("The received TOTALIZER value of Flowmeter 1 is " + String(Totalizer_F1));
        Serial.println("The received FLOWRATE value of Flowmeter 1 is " + String(Flowrate_F1));
        lcd_print_fm1();
      }

      else if ((rx_buffer2[0] == FM2_ADDRESS) && (rx_buffer2[2] == FM_RES)) {
        for (i = 4; i < 22; i++)
        {
          Serial.print(rx_buffer2[i], HEX);
        }
        Serial.println("  ");
        Totalizer_F2 = ((rx_buffer2[4] << 40) | (rx_buffer2[6] << 32) | (rx_buffer2[8] << 24) | (rx_buffer2[10] << 16) | (rx_buffer2[12] << 8) | rx_buffer2[14]);
        Flowrate_F2 = ((rx_buffer2[16] << 16) | (rx_buffer2[18] << 8) | rx_buffer2[20]);
        Serial.println("The received TOTALIZER value of Flowmeter 2 is " + String(Totalizer_F2));
        Serial.println("The received FLOWRATE value of Flowmeter 2 is " + String(Flowrate_F2));
        lcd_print_fm2();
      }
    }
  }
}

void loop() {
  Serial.println("The counter value is " + String(counter));
  flowmeter_data();
  if (SerialPort1.available() > 0) {
    int len1 = SerialPort1.readBytes(rx_buffer1, sizeof(rx_buffer1));
    if (len1 > 0) {
      Serial.println("***********************************");
      for (i = 0; i < 4; i++)
      {
        Serial.print(rx_buffer1[i], HEX);
      }
      Serial.println("  ");

      if ((rx_buffer1[0] == FM1_ADDRESS) && (rx_buffer1[1] == MDL_REQ)) {
        Serial.println("Data request received from MDL for FM1");
        byteData[0] = (Totalizer_F1 >> 24) & 0xFF;
        byteData[1] = (Totalizer_F1 >> 16) & 0xFF;
        byteData[2] = (Totalizer_F1 >> 8) & 0xFF;
        byteData[3] = Totalizer_F1 & 0xFF;

        Serial.println("The value of byte0 is " + String(byteData[0]));
        Serial.println("The value of byte1 is " + String(byteData[1]));
        Serial.println("The value of byte2 is " + String(byteData[2]));
        Serial.println("The value of byte3 is " + String(byteData[3]));

        int intflow = (int)Flowrate_F1;
        //Serial.println(intflow);
        byteData[4] = (intflow >> 16) & 0xFF;
        byteData[5] = (intflow >> 8) & 0xFF;
        byteData[6] = intflow & 0xFF;

        uint8_t packet[packet_length] = {FM1_ADDRESS, MDL_RES, byteData[0], byteData[1], byteData[2], byteData[3], byteData[4], byteData[5], byteData[6]};
        delay(200);
        SerialPort1.write(packet, packet_length);
        delay(200);
        SerialPort1.flush();
        delay(100);
        Serial.println("Response sent to MDL for FM1 with fn_code 0x05");
      }
      else if ((rx_buffer1[0] == FM2_ADDRESS) && (rx_buffer1[1] == MDL_REQ)) {
        Serial.println("Data request received from MDL for FM2");
        byteData2[0] = (Totalizer_F2 >> 24) & 0xFF;
        byteData2[1] = (Totalizer_F2 >> 16) & 0xFF;
        byteData2[2] = (Totalizer_F2 >> 8) & 0xFF;
        byteData2[3] = Totalizer_F2 & 0xFF;

        Serial.println("The value of byte0 is " + String(byteData2[0]));
        Serial.println("The value of byte1 is " + String(byteData2[1]));
        Serial.println("The value of byte2 is " + String(byteData2[2]));
        Serial.println("The value of byte3 is " + String(byteData2[3]));

        int intflow2 = (int)Flowrate_F2;
        //Serial.println(intflow2);
        byteData2[4] = (intflow2 >> 16) & 0xFF;
        byteData2[5] = (intflow2 >> 8) & 0xFF;
        byteData2[6] = intflow2 & 0xFF;

        uint8_t packet[packet_length] = {FM2_ADDRESS, MDL_RES, byteData2[0], byteData2[1], byteData2[2], byteData2[3], byteData2[4], byteData2[5], byteData2[6]};
        delay(200);
        SerialPort1.write(packet, packet_length);
        delay(200);
        SerialPort1.flush();
        delay(100);
        Serial.println("Response sent to MDL for FM2 with fn_code 0x05");
      }
      Serial.println("***********************************");
    }
  }
  send_request();
}
