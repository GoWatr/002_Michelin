#include <HardwareSerial.h>
#include "esp_system.h"
#include "esp_task_wdt.h"
#include "esp_int_wdt.h"
#include "soc/rtc_wdt.h"


volatile bool dataReady = false;
HardwareSerial MySerial(1);
char delim[] = "*";
char data0[63] = { 0 };
char data1[100] = { 0 };
char a[15][100] = { 0 };
char *strcmp_status;
char *strcmp_action;
char data1231[63] = { 0 };
// void IRAM_ATTR handleInterrupt() {
//   dataReady = true;  // Set flag to indicate data is ready

// }

// void IRAM_ATTR processSerialInput() {
void ISR_1() {

  rtc_wdt_feed();
  vTaskDelay(pdMS_TO_TICKS(100));
  int i = 0;
  if (MySerial.available() > 0) {
    // memset(data0, 0, sizeof(data0));
    Serial.println("inside serial check");
    MySerial.readBytesUntil('\n', data0, 63);
    Serial.print("Received: ");
    Serial.println(data0);
    memset(data1, 0, sizeof(data1));
    strcpy(data1, data0);
    Serial.println(data1);
    //delay(1000);
    char *ptr = strtok(data0, delim);
    while (ptr != NULL) {
      sprintf(a[i], "%s", ptr);

      ptr = strtok(NULL, delim);
      i++;
    }

    Serial.println(i);
    for (int j = 0; j < i; j++) {
      Serial.println(a[j]);

      strcmp_status = strstr(data0, "*");
      if (strcmp_status) {
        Serial.println("gostatus");
        // MySerial.println("ACK: ");
        if (strstr(a[j], "CT1:A")) {
          Serial.println("Valve 1 is automatic");
        }
        if (strstr(a[j], "CT1:M")) {
          Serial.println("Valve 1 is manual");
        }
        if (strstr(a[j], "CT2:A")) {
          Serial.println("Valve 2 is automatic");
        }
        if (strstr(a[j], "CT2:M")) {
          Serial.println("Valve 2 is manual");
        }
        if (strstr(a[j], "CT3:A")) {
          Serial.println("Valve 3 is automatic");
        }
        if (strstr(a[j], "CT3:M")) {
          Serial.println("Valve 3 is manual");
        }
        if (strstr(a[j], "CT4:A")) {
          Serial.println("Valve 4 is automatic");
        }
        if (strstr(a[j], "CT4:M")) {
          Serial.println("Valve 4 is manual");
        }
        if (strstr(a[j], "CT5:A")) {
          Serial.println("Valve 5 is automatic");
        }
        if (strstr(a[j], "CT5:M")) {
          Serial.println("Valve 5 is manual");
        }
        if (strstr(a[j], "CT6:A")) {
          Serial.println("Valve 6 is automatic");
        }
        if (strstr(a[j], "CT6:M")) {
          Serial.println("Valve 6 is manual");
        }
        if (strstr(a[j], "CT7:A")) {
          Serial.println("Valve 7 is automatic");
        }
        if (strstr(a[j], "CT7:M")) {
          Serial.println("Valve 7 is manual");
        }
        if (strstr(a[j], "CT8:A")) {
          Serial.println("Valve 8 is automatic");
        }
        if (strstr(a[j], "CT8:M")) {
          Serial.println("Valve 8 is manual");
        }
        if (strstr(a[j], "CT9:A")) {
          Serial.println("Valve 9 is automatic");
        }
        if (strstr(a[j], "CT9:M")) {
          Serial.println("Valve 9 is manual");
        }
        if (strstr(a[j], "CT10:A")) {
          Serial.println("Valve 10 is automatic");
        }
        if (strstr(a[j], "CT10:M")) {
          Serial.println("Valve 10 is manual");
        }
        if (strstr(a[j], "CT11:A")) {
          Serial.println("Valve 11 is automatic");
        }
        if (strstr(a[j], "CT11:M")) {
          Serial.println("Valve 11 is manual");
        }
        if (strstr(a[j], "CT12:A")) {
          Serial.println("Valve 12 is automatic");
        }
        if (strstr(a[j], "CT12:M")) {
          Serial.println("Valve 12 is manual");
        }
      }
      strcmp_action = strstr(data0, "@");
      if (strcmp_action) {
        Serial.println("goaction");
        if (strstr(a[j], "CT1:ON")) {


          Serial.print("valve1status ");

          Serial.println("valve 1 ON");
        } else if (strstr(a[j], "CT1:OFF")) {

          Serial.print("valve1status ");

          Serial.println("valve 1 OFF");
        }
        if (strstr(a[j], "CT2:ON")) {

          Serial.print("valve2status ");

          Serial.println("valve 2 ON");
        } else if (strstr(a[j], "CT2:OFF")) {

          Serial.print("valve2status ");

          Serial.println("valve 2 OFF");
        }
        if (strstr(a[j], "CT3:ON")) {

          Serial.print("valve3status ");

          Serial.println("valve 3 ON");
        } else if (strstr(a[j], "CT3:OFF")) {

          Serial.print("valve3status ");

          Serial.println("valve 3 OFF");
        }
        if (strstr(a[j], "CT4:ON")) {

          Serial.print("valve4status ");

          Serial.println("valve 4 ON");
        } else if (strstr(a[j], "CT4:OFF")) {

          Serial.print("valve4status ");

          Serial.println("valve 4 OFF");
        }
        if (strstr(a[j], "CT5:ON")) {

          Serial.print("valve5status ");

          Serial.println("valve 5 ON");
        } else if (strstr(a[j], "CT5:OFF")) {

          Serial.print("valve5status ");

          Serial.println("valve 5 OFF");
        }
        if (strstr(a[j], "CT6:ON")) {

          Serial.println("valve6status");

          Serial.println("valve 6 ON");
        } else if (strstr(a[j], "CT6:OFF")) {

          Serial.print("valve6status ");

          Serial.println("valve 6 OFF");
        }
        if (strstr(a[j], "CT7:ON")) {

          Serial.print("valve7status ");

          Serial.println("valve 7 ON");
        } else if (strstr(a[j], "CT7:OFF")) {

          Serial.print("valve7status ");

          Serial.println("valve 7 OFF");
        }
        if (strstr(a[j], "CT8:ON")) {

          Serial.print("valve8status ");

          Serial.println("valve 8 ON");
        } else if (strstr(a[j], "CT8:OFF")) {

          Serial.print("valve8status ");

          Serial.println("valve 8 OFF");
        }
        if (strstr(a[j], "CT9:ON")) {

          Serial.print("valve9status ");

          Serial.println("valve 9 ON");
        } else if (strstr(a[j], "CT9:OFF")) {

          Serial.print("valve9status ");

          Serial.println("valve 9 OFF");
        }
        if (strstr(a[j], "CT10:ON")) {

          Serial.print("valve10status ");

          Serial.println("valve 10 ON");
        } else if (strstr(a[j], "CT10:OFF")) {

          Serial.print("valve10status ");

          Serial.println("valve 10 OFF");
        }
        if (strstr(a[j], "CT11:ON")) {

          Serial.print("valve11status ");

          Serial.println("valve 11 ON");
        } else if (strstr(a[j], "CT11:OFF")) {

          Serial.print("valve11status ");

          Serial.println("valve 11 OFF");
        }
        if (strstr(a[j], "CT12:ON")) {

          Serial.print("valve12status ");

          Serial.println("valve 12 ON");
        } else if (strstr(a[j], "CT12:OFF")) {

          Serial.print("valve12status ");

          Serial.println("valve 12 OFF");
        }
      }
    }
    delay(500);
    Serial.println("***************Sending Ack data************************");
    Serial.println(data1);
    delay(500);
    Serial.println("*************** Ack sent************************");
  }
}

void setup() {
  Serial.begin(9600);
  MySerial.begin(9600, SERIAL_8N1, 16, 17);  // Initialize UART1
  rtc_wdt_protect_off();
  rtc_wdt_disable();
  esp_task_wdt_init(50, false);  // Set timeout to 5 seconds
  esp_task_wdt_add(NULL);        // Add the current task to the WDT
  // attachInterrupt(digitalPinToInterrupt(16), handleInterrupt, RISING);
  attachInterrupt(digitalPinToInterrupt(16), ISR_1, RISING);
  Serial.println("ESP32 Serial Communication Started");
}

void loop() {
  esp_task_wdt_reset();  // Reset the watchdog timer
  // if (dataReady) {
  //   dataReady = false;     // Reset the flag
  //   processSerialInput();  // Call processing directly
  // }

  // Other loop code or just keep it empty
}
