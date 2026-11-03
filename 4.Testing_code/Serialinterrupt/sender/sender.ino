#include <HardwareSerial.h>

HardwareSerial MySerial(1);  // Use UART1
char data0[63] = { 0 };
void setup() {
  Serial.begin(115200);                      // Initialize Serial Monitor
  MySerial.begin(9600, SERIAL_8N1, 16, 17);  // Initialize UART1: RX -> GPIO16, TX -> GPIO17
}

void loop() {
  if (Serial.available() > 0) {
    Serial.readBytesUntil('\n', data0, 63);
    // String inByte = Serial.readString();
    
    // Serial.println(inByte);
    MySerial.print(data0);
    delay(1000);
  }
}
