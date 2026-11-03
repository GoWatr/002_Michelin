#include <HardwareSerial.h>
bool updating = false;
HardwareSerial MySerial(1);  // Use UART1
void processSerialInput();
// void IRAM_ATTR handleInterrupt() {
void handleInterrupt() {
  if (!updating) {
    updating = true;
    processSerialInput();
    updating = false;
  }
}
void setup() {
  Serial.begin(9600);
  MySerial.begin(9600, SERIAL_8N1, 16, 17);  // Initialize UART1: RX -> GPIO16, TX -> GPIO17

  while (!Serial) {
    ;
  }
  attachInterrupt(digitalPinToInterrupt(16), handleInterrupt, RISING);  // or RISING depending on your requirement
  Serial.println("ESP32 Serial Communication Started");
}

void loop() {
  Serial.println("just printing:");
  delay(10000);
}
void processSerialInput() {
  if (MySerial.available() > 0) {
    char inByte = MySerial.read();
    Serial.print("Received: ");
    Serial.println(inByte);
    if (inByte == 'A') {  // A: PC requests measurement data from Arduino
      Serial.println('B');
    } else {
      Serial.println(inByte);
    }
  }
}
