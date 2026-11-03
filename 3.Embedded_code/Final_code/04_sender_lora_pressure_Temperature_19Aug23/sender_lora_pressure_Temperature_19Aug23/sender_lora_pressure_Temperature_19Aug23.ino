#include "heltec.h"
#include "images.h"
#include <Adafruit_ADS1015.h>
#define BAND 868E6  //you can set band here directly,e.g. 868E6,915E6

unsigned int counter = 0;
unsigned int counter1 = 0;
String rssi = "RSSI --";
String packSize = "--";
String packet;

Adafruit_ADS1115 ads(0x48);
int16_t adc0, adc1, adc2, adc3;
float Pressure_Voltage = 0.0;
float Temperature_Voltage = 0.0;
float Maximum_level = 17600;
const float voltageMin = 0.0;
const float voltageMax = 3.3;
float Pressure_Percentage;
float Temperature_Percentage;
String ID1 = "%PSA01:";  //string variable ID1 to ID13 created and used to send the data to api
String ID2 = ",%TSA01:";
String datatosend_Pressure;
String datatosend_Temperature;

const float minimumOutput = 4.0;    // Minimum output value of the sensor (in mA)
const float maximumOutput = 20.0;   // Maximum output value of the sensor (in mA)
const float pressureRange = 10.0;   // Pressure range that the sensor measures (in bar)
const float resistorValue = 250.0;  // Resistance (in ohms) in the current-to-voltage converter circuit

void logo() {
  Heltec.display->clear();
  Heltec.display->drawXbm(0, 5, logo_width, logo_height, logo_bits);
  Heltec.display->display();
}

void setup() {
  //WIFI Kit series V1 not support Vext control
  Heltec.begin(true /*DisplayEnable Enable*/, true /*Heltec.Heltec.Heltec.LoRa Disable*/, true /*Serial Enable*/, true /*PABOOST Enable*/, BAND /*long BAND*/);

  Serial.begin(115200);
  ads.begin();

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
  adc0 = ads.readADC_SingleEnded(0);
  Pressure_Voltage = (adc0 * 0.1875) / 1000;
  Pressure_Percentage = ((adc0 / Maximum_level) * 100);
  delay(50);

  adc1 = ads.readADC_SingleEnded(1);
  Temperature_Voltage = (adc1 * 0.1875) / 1000;
  Temperature_Percentage = ((adc1 / Maximum_level) * 100);
  adc2 = ads.readADC_SingleEnded(2);
  delay(50);

  // Convert raw value to current (mA) using the map function
  float Pressure_current = (adc0 * (maximumOutput - minimumOutput) / Maximum_level) + minimumOutput;
  float Temperature_current = (adc1 * (maximumOutput - minimumOutput) / Maximum_level) + minimumOutput;
  delay(50);

  // Convert current (mA) to pressure (bar)
  float pressure = (Pressure_current - minimumOutput) * (pressureRange / (maximumOutput - minimumOutput));
  delay(50);

  // Function to map voltage to temperature using calibration data // Placeholder calibration data - Replace this with actual calibration equation or lookup table
  //float temperature = (Temperature_Voltage - voltageMin) * (30.0 - (0.0)) / (voltageMax - voltageMin) + (0.0);
  float temperature = (Temperature_Voltage - voltageMin) * (45.0 - (10.0)) / (voltageMax - voltageMin) + (10.0);
  delay(50);

  //lora sending
  datatosend_Pressure = ID1 + String(pressure);
  datatosend_Temperature = ID2 + String(temperature);

  Heltec.display->clear();
  Heltec.display->setTextAlignment(TEXT_ALIGN_LEFT);
  Heltec.display->setFont(ArialMT_Plain_10);

  Heltec.display->drawString(0, 0, "(ADC0)  " + String(adc0));
  Heltec.display->drawString(0, 12, "(ADC1)  " + String(adc1));
  Heltec.display->drawString(0, 24, String(datatosend_Pressure) + " bar");
  Heltec.display->drawString(0, 36, String(datatosend_Temperature) + " °C");
  //Heltec.display->drawString(0, 23, String(Percentage) + "%");
  Heltec.display->display();
  // send packet
  counter1++;
  delay(1000);
  if (counter1 > 100) {
    Heltec.display->display();
    counter1 = 0;
    LoRa.beginPacket();
    LoRa.setTxPower(14, RF_PACONFIG_PASELECT_PABOOST);
    LoRa.print(datatosend_Pressure);
    delay(100);
    LoRa.print(datatosend_Temperature);
    delay(100);
    LoRa.print(String("|"));
    LoRa.endPacket();
    delay(500);
    Serial.print(datatosend_Pressure + datatosend_Temperature + String("|"));
    Serial.println("*****************data sent*****************");

    /* LoRa.beginPacket();
  LoRa.setTxPower(14,RF_PACONFIG_PASELECT_PABOOST);
  LoRa.print("ADC0: " + String(adc0) + "ADC1: " + String(adc1));
  Serial.print(datatosend_Pressure + datatosend_Temperature);
  LoRa.endPacket();*/
    counter++;
    digitalWrite(LED, HIGH);  // turn the LED on (HIGH is the voltage level)
    delay(1000);              // wait for a second
    digitalWrite(LED, LOW);   // turn the LED off by making the voltage LOW
    delay(2000);
  }
  Serial.print("1.AIN0: ");
  Serial.println(adc0);
  Serial.print("2.AIN1: ");
  Serial.println(adc1);
  Serial.print("2.Pressure Voltage: ");
  Serial.print(Pressure_Voltage, 7);
  Serial.print("Temperature Volatge: ");
  Serial.println(Temperature_Voltage, 7);
  Serial.print("3.Pressure Current (mA): ");
  Serial.print(Pressure_current, 5);
  Serial.print("Temperature Current (mA): ");
  Serial.println(Temperature_current, 5);
  Serial.print("4.Pressure (bar): ");
  Serial.println(pressure, 5);
  Serial.print("5.Temperature: ");
  Serial.print(temperature);
  Serial.println(" °C");
  Serial.println("6.Pressure_Percentage: " + String(Pressure_Percentage) + "%" + "Temperature_Percentage:" + String(Temperature_Percentage) + "%");
  Serial.println("");
}
