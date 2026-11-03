#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <Wire.h>
#include <Arduino_FreeRTOS.h>
#include <avr/wdt.h>
#include "functions.h"
#define TASK1_STACK_SIZE 128  //128
#define TASK2_STACK_SIZE 128

void CTAutomation(void *pvParameters);
void Serialcontrol(void *pvParameters);

char *strcmp_status;
char *strcmp_action;
#define RXp1 19
#define TXp1 18
char delim[] = "*";
char data0[63] = { 0 };
char data1[100] = { 0 };
char a[15][100] = { 0 };
int flag1 = 1;
int flag2 = 1;
int flag3 = 1;
int flag4 = 1;
int flag5 = 1;
int flag6 = 1;
int flag7 = 1;
int flag8 = 1;
int flag9 = 1;
int flag10 = 1;
int flag11 = 1;
int flag12 = 1;

String ID1 = "&CT1:";
String ID2 = ",?CT1:";
String ID3 = "&CT2:";
String ID4 = ",?CT2:";
String ID5 = "&CT3:";
String ID6 = ",?CT3:";
String ID7 = "&CT4:";
String ID8 = ",?CT4:";
String ID9 = "&CT5:";
String ID10 = ",?CT5:";
String ID11 = "&CT6:";
String ID12 = ",?CT6:";
String ID13 = "&CT7:";
String ID14 = ",?CT7:";
String ID15 = "&CT8:";
String ID16 = ",?CT8:";
String ID17 = "&CT9:";
String ID18 = ",?CT9:";
String ID19 = "&CT10:";
String ID20 = ",?CT10:";
String ID21 = "&CT11:";
String ID22 = ",?CT11:";

String ID23 = "&CT12:";
String ID24 = ",?CT12:";

String ID25 = ",mst1:";
String ID26 = ",mst2:";
String ID27 = ",mst3:";
String ID28 = ",mst4:";
String ID29 = ",mst5:";
String ID30 = ",mst6:";
String ID31 = ",mst7:";
String ID32 = ",mst8:";
String ID33 = ",mst9:";
String ID34 = ",mst10:";
String ID35 = ",mst11:";
String ID36 = ",mst12:";


void setup() {
  Serial.begin(115200);
  Serial1.begin(9600);

  Serial.println("michelin valve control");
  pinMode(valve1, OUTPUT);
  digitalWrite(valve1, LOW);
  pinMode(valve2, OUTPUT);
  digitalWrite(valve2, LOW);
  pinMode(valve3, OUTPUT);
  digitalWrite(valve3, LOW);
  pinMode(valve4, OUTPUT);
  digitalWrite(valve4, LOW);
  pinMode(valve5, OUTPUT);
  digitalWrite(valve5, LOW);
  pinMode(valve6, OUTPUT);
  digitalWrite(valve6, LOW);
  pinMode(valve7, OUTPUT);
  digitalWrite(valve7, LOW);
  pinMode(valve8, OUTPUT);
  digitalWrite(valve8, LOW);
  pinMode(valve9, OUTPUT);
  digitalWrite(valve9, LOW);
  pinMode(valve10, OUTPUT);
  digitalWrite(valve10, LOW);
  pinMode(valve11, OUTPUT);
  digitalWrite(valve11, LOW);
  pinMode(valve12, OUTPUT);
  digitalWrite(valve12, LOW);
  wdt_enable(WDTO_8S);  // Set timeout to 8 seconds
  // Create the tasks
  xTaskCreate(CTAutomation, "CTAutomation", TASK1_STACK_SIZE, NULL, 1, NULL);
  xTaskCreate(Serialcontrol, "Serialcontrol", TASK2_STACK_SIZE, NULL, 1, NULL);

  // Start the scheduler
  vTaskStartScheduler();
}

void loop() {
}

String addDelimiter(String data) {
  return data + "|";
}

void CTAutomation(void *pvParameters) {
  (void)pvParameters;

  while (1) {
    UBaseType_t stackSize = uxTaskGetStackHighWaterMark(NULL);
    Serial.print("CTAutomation stack high water mark: ");
    Serial.println(stackSize);

    vTaskDelay(100 / portTICK_PERIOD_MS);
    wdt_reset();
    Hydrostatic1();
    vTaskDelay(10 / portTICK_PERIOD_MS);
    Hydrostatic2();
    vTaskDelay(10 / portTICK_PERIOD_MS);
    // wdt_reset();

    Hydrostatic3();
    vTaskDelay(10 / portTICK_PERIOD_MS);
    Hydrostatic4();
    vTaskDelay(10 / portTICK_PERIOD_MS);
    // wdt_reset();

    Hydrostatic5();
    vTaskDelay(10 / portTICK_PERIOD_MS);
    Hydrostatic6();
    vTaskDelay(10 / portTICK_PERIOD_MS);
    // wdt_reset();

    Hydrostatic7();
    vTaskDelay(10 / portTICK_PERIOD_MS);
    Hydrostatic8();
    vTaskDelay(10 / portTICK_PERIOD_MS);
    // wdt_reset();

    Hydrostatic9();
    vTaskDelay(10 / portTICK_PERIOD_MS);
    Hydrostatic10();
    vTaskDelay(10 / portTICK_PERIOD_MS);
    // wdt_reset();

    Hydrostatic11();
    vTaskDelay(10 / portTICK_PERIOD_MS);
    Hydrostatic12();
    vTaskDelay(10 / portTICK_PERIOD_MS);
    // wdt_reset();

    if (flag1 == 1) {
      vTaskDelay(100 / portTICK_PERIOD_MS);  // Delay for 500ms
      if (Per_AVG1 <= 70) {
        Relay1_ON();
      } else if (Per_AVG1 >= 80) {
        Relay1_OFF();
      }
    }
    if (flag2 == 1) {
      vTaskDelay(100 / portTICK_PERIOD_MS);
      if (Per_AVG2 <= 70) {
        Relay2_ON();
      } else if (Per_AVG2 >= 80) {
        Relay2_OFF();
      }
    }

    if (flag3 == 1) {
      vTaskDelay(100 / portTICK_PERIOD_MS);
      if (Per_AVG3 <= 70) {
        Relay3_ON();
      } else if (Per_AVG3 >= 80) {
        Relay3_OFF();
      }
    }

    if (flag4 == 1) {
      vTaskDelay(100 / portTICK_PERIOD_MS);
      if (Per_AVG4 <= 70) {
        Relay4_ON();
      } else if (Per_AVG4 >= 80) {
        Relay4_OFF();
      }
    }

    if (flag5 == 1) {
      vTaskDelay(100 / portTICK_PERIOD_MS);
      if (Per_AVG5 <= 70) {
        Relay5_ON();
      } else if (Per_AVG5 >= 80) {
        Relay5_OFF();
      }
    }
    if (flag6 == 1) {
      vTaskDelay(100 / portTICK_PERIOD_MS);
      if (Per_AVG6 <= 70) {
        Relay6_ON();
      } else if (Per_AVG6 > 80) {
        Relay6_OFF();
      }
    }

    if (flag7 == 1) {
      vTaskDelay(100 / portTICK_PERIOD_MS);
      if (Per_AVG7 <= 70) {
        Relay7_ON();
      } else if (Per_AVG7 >= 80) {
        Relay7_OFF();
      }
    }

    if (flag8 == 1) {
      vTaskDelay(100 / portTICK_PERIOD_MS);
      if (Per_AVG8 <= 60) {
        Relay8_ON();
      } else if (Per_AVG8 > 65) {
        Relay8_OFF();
      }
    }
    if (flag9 == 1) {
      vTaskDelay(100 / portTICK_PERIOD_MS);
      if (Per_AVG9 <= 60) {
        Relay9_ON();
      } else if (Per_AVG9 > 65) {
        Relay9_OFF();
      }
    }

    if (flag10 == 1) {
      vTaskDelay(100 / portTICK_PERIOD_MS);
      if (Per_AVG10 <= 60) {
        Relay10_ON();
      } else if (Per_AVG10 > 65) {
        Relay10_OFF();
      }
    }

    if (flag11 == 1) {
      vTaskDelay(100 / portTICK_PERIOD_MS);
      if (Per_AVG11 <= 60) {
        Relay11_ON();
      } else if (Per_AVG11 > 65) {
        Relay11_OFF();
      }

      if (flag12 == 1) {
        vTaskDelay(100 / portTICK_PERIOD_MS);
        if (Per_AVG12 <= 70) {
          Relay12_ON();
        } else if (Per_AVG12 > 80) {
          Relay12_OFF();
        }
      }
      // wdt_reset();
      vTaskDelay(100 / portTICK_PERIOD_MS);
      Counter++;
      vTaskDelay(1000 / portTICK_PERIOD_MS);
      Serial.println("count is");
      Serial.println(Counter);
      if (Counter == 1) {
        String dataToSend = ID1 + String(Per_AVG1) + ID2 + String(valve1status) + ID25 + String(flag1);
        Serial.println(addDelimiter(dataToSend));
        Serial1.println(addDelimiter(dataToSend));
        vTaskDelay(1000 / portTICK_PERIOD_MS);
      }

      if (Counter == 2) {
        String dataToSend = ID3 + String(Per_AVG2) + ID4 + String(valve2status) + ID26 + String(flag2);
        Serial.println(addDelimiter(dataToSend));
        Serial1.println(addDelimiter(dataToSend));
        vTaskDelay(1000 / portTICK_PERIOD_MS);
      }

      if (Counter == 3) {
        String dataToSend = ID5 + String(Per_AVG3) + ID6 + String(valve3status) + ID27 + String(flag3);
        Serial.println(addDelimiter(dataToSend));
        Serial1.println(addDelimiter(dataToSend));
        vTaskDelay(1000 / portTICK_PERIOD_MS);
      }

      if (Counter == 4) {
        String dataToSend = ID7 + String(Per_AVG4) + ID8 + String(valve4status) + ID28 + String(flag4);
        Serial.println(addDelimiter(dataToSend));
        Serial1.println(addDelimiter(dataToSend));
        vTaskDelay(1000 / portTICK_PERIOD_MS);
      }

      if (Counter == 5) {
        String dataToSend = ID9 + String(Per_AVG5) + ID10 + String(valve5status) + ID29 + String(flag5);
        Serial.println(addDelimiter(dataToSend));
        Serial1.println(addDelimiter(dataToSend));
        vTaskDelay(1000 / portTICK_PERIOD_MS);
      }

      if (Counter == 6) {
        String dataToSend = ID11 + String(Per_AVG6) + ID12 + String(valve6status) + ID30 + String(flag6);
        Serial.println(addDelimiter(dataToSend));
        Serial1.println(addDelimiter(dataToSend));
        vTaskDelay(1000 / portTICK_PERIOD_MS);
      }

      if (Counter == 7) {
        String dataToSend = ID13 + String(Per_AVG7) + ID14 + String(valve7status) + ID31 + String(flag7);
        Serial.println(addDelimiter(dataToSend));
        Serial1.println(addDelimiter(dataToSend));
        vTaskDelay(1000 / portTICK_PERIOD_MS);
      }

      if (Counter == 8) {
        String dataToSend = ID15 + String(Per_AVG8) + ID16 + String(valve8status) + ID32 + String(flag8);
        Serial.println(addDelimiter(dataToSend));
        Serial1.println(addDelimiter(dataToSend));
        vTaskDelay(1000 / portTICK_PERIOD_MS);
      }

      if (Counter == 9) {
        String dataToSend = ID17 + String(Per_AVG9) + ID18 + String(valve9status) + ID33 + String(flag9);
        Serial.println(addDelimiter(dataToSend));
        Serial1.println(addDelimiter(dataToSend));
        vTaskDelay(1000 / portTICK_PERIOD_MS);
      }
      if (Counter == 10) {
        String dataToSend = ID19 + String(Per_AVG10) + ID20 + String(valve10status) + ID34 + String(flag10);
        Serial.println(addDelimiter(dataToSend));
        Serial1.println(addDelimiter(dataToSend));
        vTaskDelay(1000 / portTICK_PERIOD_MS);
      }
      if (Counter == 11) {
        String dataToSend = ID21 + String(Per_AVG11) + ID22 + String(valve11status) + ID35 + String(flag11);
        Serial.println(addDelimiter(dataToSend));
        Serial1.println(addDelimiter(dataToSend));
        vTaskDelay(1000 / portTICK_PERIOD_MS);
      }
      if (Counter == 12) {
        Counter = 0;
        String dataToSend = ID23 + String(Per_AVG12) + ID24 + String(valve12status) + ID36 + String(flag12);
        Serial.println(addDelimiter(dataToSend));
        Serial1.println(addDelimiter(dataToSend));
        vTaskDelay(1000 / portTICK_PERIOD_MS);
      }
    }
    wdt_reset();
  }
}

void Serialcontrol(void *pvParameters) {
  (void)pvParameters;

  while (1) {
    vTaskDelay(2000 / portTICK_PERIOD_MS);
    int i = 0;
    if (Serial1.available()) {
      wdt_reset();
      memset(data0, 0, sizeof(data0));
      Serial.println("inside serial check");
      Serial1.readBytesUntil('\n', data0, 63);
      Serial.print("Received: ");
      Serial.println(data0);
      memset(data1, 0, sizeof(data1));
      strcpy(data1, data0);
      Serial.println(data1);
      //vTaskDelay(1000 / portTICK_PERIOD_MS);
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
          vTaskDelay(3000 / portTICK_PERIOD_MS);
          wdt_reset();
          Serial.println("gostatus");
          // Serial1.println("ACK: ");
          if (strstr(a[j], "CT1:A")) {
            Serial.println("Valve 1 is automatic");
            // Serial1.println("ACK: ");
            // Serial1.println(addDelimiter(data1));

            flag1 = 1;
            String dataToSend = ID1 + String(Per_AVG1) + ID2 + String(valve1status) + ID25 + String(flag1);
            Serial1.println(addDelimiter(dataToSend));
            vTaskDelay(1000 / portTICK_PERIOD_MS);
          }
          if (strstr(a[j], "CT1:M")) {
            Serial.println("Valve 1 is manual");
            // Serial1.println(addDelimiter(data1));
            flag1 = 0;
            String dataToSend = ID1 + String(Per_AVG1) + ID2 + String(valve1status) + ID25 + String(flag1);
            Serial1.println(addDelimiter(dataToSend));
            vTaskDelay(1000 / portTICK_PERIOD_MS);
          }
          if (strstr(a[j], "CT2:A")) {
            Serial.println("Valve 2 is automatic");
            // Serial1.println(addDelimiter(data1));

            flag2 = 1;
            String dataToSend = ID3 + String(Per_AVG2) + ID4 + String(valve2status) + ID26 + String(flag2);
            Serial1.println(addDelimiter(dataToSend));
            vTaskDelay(1000 / portTICK_PERIOD_MS);
          }
          if (strstr(a[j], "CT2:M")) {
            Serial.println("Valve 2 is manual");
            // Serial1.println(addDelimiter(data1));
            flag2 = 0;
            String dataToSend = ID3 + String(Per_AVG2) + ID4 + String(valve2status) + ID26 + String(flag2);
            Serial1.println(addDelimiter(dataToSend));
            vTaskDelay(1000 / portTICK_PERIOD_MS);
          }
          if (strstr(a[j], "CT3:A")) {
            Serial.println("Valve 3 is automatic");
            // Serial1.println(addDelimiter(data1));

            flag3 = 1;
            String dataToSend = ID5 + String(Per_AVG3) + ID6 + String(valve3status) + ID27 + String(flag3);
            Serial1.println(addDelimiter(dataToSend));
            vTaskDelay(1000 / portTICK_PERIOD_MS);
          }
          if (strstr(a[j], "CT3:M")) {
            Serial.println("Valve 3 is manual");
            // Serial1.println(addDelimiter(data1));

            flag3 = 0;
            String dataToSend = ID5 + String(Per_AVG3) + ID6 + String(valve3status) + ID27 + String(flag3);
            Serial1.println(addDelimiter(dataToSend));
            vTaskDelay(1000 / portTICK_PERIOD_MS);
          }
          if (strstr(a[j], "CT4:A")) {
            Serial.println("Valve 4 is automatic");
            // Serial1.println(addDelimiter(data1));

            flag4 = 1;
            String dataToSend = ID7 + String(Per_AVG4) + ID8 + String(valve4status) + ID28 + String(flag4);
            Serial1.println(addDelimiter(dataToSend));
            vTaskDelay(1000 / portTICK_PERIOD_MS);
          }
          if (strstr(a[j], "CT4:M")) {
            Serial.println("Valve 4 is manual");
            // Serial1.println(addDelimiter(data1));

            flag4 = 0;
            String dataToSend = ID7 + String(Per_AVG4) + ID8 + String(valve4status) + ID28 + String(flag4);
            Serial1.println(addDelimiter(dataToSend));
            vTaskDelay(1000 / portTICK_PERIOD_MS);
          }
          if (strstr(a[j], "CT5:A")) {
            Serial.println("Valve 5 is automatic");
            // Serial1.println(addDelimiter(data1));
            flag5 = 1;
            String dataToSend = ID9 + String(Per_AVG5) + ID10 + String(valve5status) + ID29 + String(flag5);
            Serial1.println(addDelimiter(dataToSend));
            vTaskDelay(1000 / portTICK_PERIOD_MS);
          }
          if (strstr(a[j], "CT5:M")) {
            Serial.println("Valve 5 is manual");
            // Serial1.println(addDelimiter(data1));
            flag5 = 0;
            String dataToSend = ID9 + String(Per_AVG5) + ID10 + String(valve5status) + ID29 + String(flag5);
            Serial1.println(addDelimiter(dataToSend));
            vTaskDelay(1000 / portTICK_PERIOD_MS);
          }
          if (strstr(a[j], "CT6:A")) {
            Serial.println("Valve 6 is automatic");
            // Serial1.println(addDelimiter(data1));
            flag6 = 1;
            String dataToSend = ID11 + String(Per_AVG6) + ID12 + String(valve6status) + ID30 + String(flag6);
            Serial1.println(addDelimiter(dataToSend));
            vTaskDelay(1000 / portTICK_PERIOD_MS);
          }
          if (strstr(a[j], "CT6:M")) {
            Serial.println("Valve 6 is manual");
            // Serial1.println(addDelimiter(data1));

            flag6 = 0;
            String dataToSend = ID11 + String(Per_AVG6) + ID12 + String(valve6status) + ID30 + String(flag6);
            Serial1.println(addDelimiter(dataToSend));
            vTaskDelay(1000 / portTICK_PERIOD_MS);
          }
          if (strstr(a[j], "CT7:A")) {
            Serial.println("Valve 7 is automatic");
            // Serial1.println(addDelimiter(data1));

            flag7 = 1;
            String dataToSend = ID13 + String(Per_AVG7) + ID14 + String(valve7status) + ID31 + String(flag7);
            Serial1.println(addDelimiter(dataToSend));
            vTaskDelay(1000 / portTICK_PERIOD_MS);
          }
          if (strstr(a[j], "CT7:M")) {
            Serial.println("Valve 7 is manual");
            // Serial1.println(addDelimiter(data1));

            flag7 = 0;
            String dataToSend = ID13 + String(Per_AVG7) + ID14 + String(valve7status) + ID31 + String(flag7);
            Serial1.println(addDelimiter(dataToSend));
            vTaskDelay(1000 / portTICK_PERIOD_MS);
          }
          if (strstr(a[j], "CT8:A")) {
            Serial.println("Valve 8 is automatic");
            // Serial1.println(addDelimiter(data1));

            flag8 = 1;
            String dataToSend = ID15 + String(Per_AVG8) + ID16 + String(valve8status) + ID32 + String(flag8);
            Serial1.println(addDelimiter(dataToSend));
            vTaskDelay(1000 / portTICK_PERIOD_MS);
          }
          if (strstr(a[j], "CT8:M")) {
            Serial.println("Valve 8 is manual");
            // Serial1.println(addDelimiter(data1));

            flag8 = 0;
            String dataToSend = ID15 + String(Per_AVG8) + ID16 + String(valve8status) + ID32 + String(flag8);
            Serial1.println(addDelimiter(dataToSend));
            vTaskDelay(1000 / portTICK_PERIOD_MS);
          }
          if (strstr(a[j], "CT9:A")) {
            Serial.println("Valve 9 is automatic");
            // Serial1.println(addDelimiter(data1));

            flag9 = 1;
            String dataToSend = ID17 + String(Per_AVG9) + ID18 + String(valve9status) + ID33 + String(flag9);
            Serial1.println(addDelimiter(dataToSend));
            vTaskDelay(1000 / portTICK_PERIOD_MS);
          }
          if (strstr(a[j], "CT9:M")) {
            Serial.println("Valve 9 is manual");
            // Serial1.println(addDelimiter(data1));

            flag9 = 0;
            String dataToSend = ID17 + String(Per_AVG9) + ID18 + String(valve9status) + ID33 + String(flag9);
            Serial1.println(addDelimiter(dataToSend));
            vTaskDelay(1000 / portTICK_PERIOD_MS);
          }
          if (strstr(a[j], "CT10:A")) {
            Serial.println("Valve 10 is automatic");
            // Serial1.println(addDelimiter(data1));

            flag10 = 1;
            String dataToSend = ID19 + String(Per_AVG10) + ID20 + String(valve10status) + ID34 + String(flag10);
            Serial1.println(addDelimiter(dataToSend));
            vTaskDelay(1000 / portTICK_PERIOD_MS);
          }
          if (strstr(a[j], "CT10:M")) {
            Serial.println("Valve 10 is manual");
            // Serial1.println(addDelimiter(data1));

            flag10 = 0;
            String dataToSend = ID19 + String(Per_AVG10) + ID20 + String(valve10status) + ID34 + String(flag10);
            Serial1.println(addDelimiter(dataToSend));
            vTaskDelay(1000 / portTICK_PERIOD_MS);
          }
          if (strstr(a[j], "CT11:A")) {
            Serial.println("Valve 11 is automatic");
            // Serial1.println(addDelimiter(data1));
            // vTaskDelay(1000 / portTICK_PERIOD_MS);
            flag11 = 1;
            String dataToSend = ID21 + String(Per_AVG11) + ID22 + String(valve11status) + ID35 + String(flag11);
            Serial1.println(addDelimiter(dataToSend));
            vTaskDelay(1000 / portTICK_PERIOD_MS);
          }
          if (strstr(a[j], "CT11:M")) {
            Serial.println("Valve 11 is manual");
            // Serial1.println(addDelimiter(data1));
            vTaskDelay(1000 / portTICK_PERIOD_MS);
            String dataToSend = ID21 + String(Per_AVG11) + ID22 + String(valve11status) + ID35 + String(flag11);
            Serial1.println(addDelimiter(dataToSend));
            flag11 = 0;
          }
          if (strstr(a[j], "CT12:A")) {
            Serial.println("Valve 12 is automatic");
            // Serial1.println(addDelimiter(data1));

            flag12 = 1;
            String dataToSend = ID23 + String(Per_AVG12) + ID24 + String(valve12status) + ID36 + String(flag12);
            Serial1.println(addDelimiter(dataToSend));
            vTaskDelay(1000 / portTICK_PERIOD_MS);
          }
          if (strstr(a[j], "CT12:M")) {
            Serial.println("Valve 12 is manual");
            // Serial1.println(addDelimiter(data1));

            flag12 = 0;
            String dataToSend = ID23 + String(Per_AVG12) + ID24 + String(valve12status) + ID36 + String(flag12);
            Serial1.println(addDelimiter(dataToSend));
            vTaskDelay(1000 / portTICK_PERIOD_MS);
          }
        }
        strcmp_action = strstr(data0, "@");
        if (strcmp_action) {
          vTaskDelay(3000 / portTICK_PERIOD_MS);
          wdt_reset();
          Serial.println("goaction");
          if (strstr(a[j], "CT1:ON")) {
            flag1 = 0;
            Relay1_ON();
            // Serial1.println(addDelimiter(data1));
            String dataToSend = ID1 + String(Per_AVG1) + ID2 + String(valve1status) + ID25 + String(flag1);
            Serial1.println(addDelimiter(dataToSend));
            vTaskDelay(1000 / portTICK_PERIOD_MS);
            Serial.print("valve1status ");
            Serial.println(valve1status);
            Serial.println("valve 1 ON");
          } else if (strstr(a[j], "CT1:OFF")) {
            flag1 = 0;
            Relay1_OFF();
            // Serial1.println(addDelimiter(data1));
            String dataToSend = ID1 + String(Per_AVG1) + ID2 + String(valve1status) + ID25 + String(flag1);
            Serial1.println(addDelimiter(dataToSend));
            vTaskDelay(1000 / portTICK_PERIOD_MS);
            Serial.print("valve1status ");
            Serial.println(valve1status);
            Serial.println("valve 1 OFF");
          }
          if (strstr(a[j], "CT2:ON")) {
            flag2 = 0;
            Relay2_ON();
            // Serial1.println(addDelimiter(data1));
            String dataToSend = ID3 + String(Per_AVG2) + ID4 + String(valve2status) + ID26 + String(flag2);
            Serial1.println(addDelimiter(dataToSend));
            vTaskDelay(1000 / portTICK_PERIOD_MS);
            Serial.print("valve2status ");
            Serial.println(valve2status);
            Serial.println("valve 2 ON");
          } else if (strstr(a[j], "CT2:OFF")) {
            flag2 = 0;
            Relay2_OFF();
            // Serial1.println(addDelimiter(data1));
            String dataToSend = ID3 + String(Per_AVG2) + ID4 + String(valve2status) + ID26 + String(flag2);
            Serial1.println(addDelimiter(dataToSend));
            vTaskDelay(1000 / portTICK_PERIOD_MS);
            Serial.print("valve2status ");
            Serial.println(valve2status);
            Serial.println("valve 2 OFF");
          }
          if (strstr(a[j], "CT3:ON")) {
            flag3 = 0;
            Relay3_ON();
            // Serial1.println(addDelimiter(data1));
            String dataToSend = ID5 + String(Per_AVG3) + ID6 + String(valve3status) + ID27 + String(flag3);
            Serial1.println(addDelimiter(dataToSend));
            vTaskDelay(1000 / portTICK_PERIOD_MS);
            Serial.print("valve3status ");
            Serial.println(valve3status);
            Serial.println("valve 3 ON");
          } else if (strstr(a[j], "CT3:OFF")) {
            flag3 = 0;
            Relay3_OFF();
            // Serial1.println(addDelimiter(data1));
            String dataToSend = ID5 + String(Per_AVG3) + ID6 + String(valve3status) + ID27 + String(flag3);
            Serial1.println(addDelimiter(dataToSend));
            vTaskDelay(1000 / portTICK_PERIOD_MS);
            Serial.print("valve3status ");
            Serial.println(valve3status);
            Serial.println("valve 3 OFF");
          }
          if (strstr(a[j], "CT4:ON")) {
            flag4 = 0;
            Relay4_ON();
            // Serial1.println(addDelimiter(data1));
            String dataToSend = ID7 + String(Per_AVG4) + ID8 + String(valve4status) + ID28 + String(flag4);
            Serial1.println(addDelimiter(dataToSend));
            vTaskDelay(1000 / portTICK_PERIOD_MS);
            Serial.print("valve4status ");
            Serial.println(valve4status);
            Serial.println("valve 4 ON");
          } else if (strstr(a[j], "CT4:OFF")) {
            flag4 = 0;
            Relay4_OFF();
            // Serial1.println(addDelimiter(data1));
            String dataToSend = ID7 + String(Per_AVG4) + ID8 + String(valve4status) + ID28 + String(flag4);
            Serial1.println(addDelimiter(dataToSend));
            vTaskDelay(1000 / portTICK_PERIOD_MS);
            Serial.print("valve4status ");
            Serial.println(valve4status);
            Serial.println("valve 4 OFF");
          }
          if (strstr(a[j], "CT5:ON")) {
            flag5 = 0;
            Relay5_ON();
            // Serial1.println(addDelimiter(data1));
            String dataToSend = ID9 + String(Per_AVG5) + ID10 + String(valve5status) + ID29 + String(flag5);
            Serial1.println(addDelimiter(dataToSend));
            vTaskDelay(1000 / portTICK_PERIOD_MS);
            Serial.print("valve5status ");
            Serial.println(valve5status);
            Serial.println("valve 5 ON");
          } else if (strstr(a[j], "CT5:OFF")) {
            flag5 = 0;
            Relay5_OFF();
            // Serial1.println(addDelimiter(data1));
            String dataToSend = ID9 + String(Per_AVG5) + ID10 + String(valve5status) + ID29 + String(flag5);
            Serial1.println(addDelimiter(dataToSend));
            vTaskDelay(1000 / portTICK_PERIOD_MS);
            Serial.print("valve5status ");
            Serial.println(valve5status);
            Serial.println("valve 5 OFF");
          }
          if (strstr(a[j], "CT6:ON")) {
            flag6 = 0;
            Relay6_ON();
            // Serial1.println(addDelimiter(data1));
            String dataToSend = ID11 + String(Per_AVG6) + ID12 + String(valve6status) + ID30 + String(flag6);
            Serial1.println(addDelimiter(dataToSend));
            vTaskDelay(1000 / portTICK_PERIOD_MS);
            Serial.println("valve6status");
            Serial.println(valve6status);
            Serial.println("valve 6 ON");
          } else if (strstr(a[j], "CT6:OFF")) {
            flag6 = 0;
            Relay6_OFF();
            // Serial1.println(addDelimiter(data1));
            String dataToSend = ID11 + String(Per_AVG6) + ID12 + String(valve6status) + ID30 + String(flag6);
            Serial1.println(addDelimiter(dataToSend));
            vTaskDelay(1000 / portTICK_PERIOD_MS);
            Serial.print("valve6status ");
            Serial.println(valve6status);
            Serial.println("valve 6 OFF");
          }
          if (strstr(a[j], "CT7:ON")) {
            flag7 = 0;
            Relay7_ON();
            // Serial1.println(addDelimiter(data1));
            String dataToSend = ID13 + String(Per_AVG7) + ID14 + String(valve7status) + ID31 + String(flag7);
            Serial1.println(addDelimiter(dataToSend));
            vTaskDelay(1000 / portTICK_PERIOD_MS);
            Serial.print("valve7status ");
            Serial.println(valve7status);
            Serial.println("valve 7 ON");
          } else if (strstr(a[j], "CT7:OFF")) {
            flag7 = 0;
            Relay7_OFF();
            // Serial1.println(addDelimiter(data1));
            String dataToSend = ID13 + String(Per_AVG7) + ID14 + String(valve7status) + ID31 + String(flag7);
            Serial1.println(addDelimiter(dataToSend));
            vTaskDelay(1000 / portTICK_PERIOD_MS);
            Serial.print("valve7status ");
            Serial.println(valve7status);
            Serial.println("valve 7 OFF");
          }
          if (strstr(a[j], "CT8:ON")) {
            flag8 = 0;
            Relay8_ON();
            // Serial1.println(addDelimiter(data1));
            String dataToSend = ID15 + String(Per_AVG8) + ID16 + String(valve8status) + ID32 + String(flag8);
            Serial1.println(addDelimiter(dataToSend));
            vTaskDelay(1000 / portTICK_PERIOD_MS);
            Serial.print("valve8status ");
            Serial.println(valve8status);
            Serial.println("valve 8 ON");
          } else if (strstr(a[j], "CT8:OFF")) {
            flag8 = 0;
            Relay8_OFF();
            // Serial1.println(addDelimiter(data1));
            String dataToSend = ID15 + String(Per_AVG8) + ID16 + String(valve8status) + ID32 + String(flag8);
            Serial1.println(addDelimiter(dataToSend));
            vTaskDelay(1000 / portTICK_PERIOD_MS);
            Serial.print("valve8status ");
            Serial.println(valve8status);
            Serial.println("valve 8 OFF");
          }
          if (strstr(a[j], "CT9:ON")) {
            flag9 = 0;
            Relay9_ON();
            // Serial1.println(addDelimiter(data1));
            String dataToSend = ID17 + String(Per_AVG9) + ID18 + String(valve9status) + ID33 + String(flag9);
            Serial1.println(addDelimiter(dataToSend));
            vTaskDelay(1000 / portTICK_PERIOD_MS);
            Serial.print("valve9status ");
            Serial.println(valve9status);
            Serial.println("valve 9 ON");
          } else if (strstr(a[j], "CT9:OFF")) {
            flag9 = 0;
            Relay9_OFF();
            // Serial1.println(addDelimiter(data1));
            String dataToSend = ID17 + String(Per_AVG9) + ID18 + String(valve9status) + ID33 + String(flag9);
            Serial1.println(addDelimiter(dataToSend));
            vTaskDelay(1000 / portTICK_PERIOD_MS);
            Serial.print("valve9status ");
            Serial.println(valve9status);
            Serial.println("valve 9 OFF");
          }
          if (strstr(a[j], "CT10:ON")) {
            flag10 = 0;
            Relay10_ON();
            // Serial1.println(addDelimiter(data1));
            String dataToSend = ID19 + String(Per_AVG10) + ID20 + String(valve10status) + ID34 + String(flag10);
            Serial1.println(addDelimiter(dataToSend));
            vTaskDelay(1000 / portTICK_PERIOD_MS);
            Serial.print("valve10status ");
            Serial.println(valve10status);
            Serial.println("valve 10 ON");
          } else if (strstr(a[j], "CT10:OFF")) {
            flag10 = 0;
            Relay10_OFF();
            // Serial1.println(addDelimiter(data1));
            String dataToSend = ID19 + String(Per_AVG10) + ID20 + String(valve10status) + ID34 + String(flag10);
            Serial1.println(addDelimiter(dataToSend));
            vTaskDelay(1000 / portTICK_PERIOD_MS);
            Serial.print("valve10status ");
            Serial.println(valve10status);
            Serial.println("valve 10 OFF");
          }
          if (strstr(a[j], "CT11:ON")) {
            Relay11_ON();
            flag11 = 0;
            // Serial1.println(addDelimiter(data1));
            String dataToSend = ID21 + String(Per_AVG11) + ID22 + String(valve11status) + ID35 + String(flag11);
            Serial1.println(addDelimiter(dataToSend));
            vTaskDelay(1000 / portTICK_PERIOD_MS);
            Serial.print("valve11status ");
            Serial.println(valve11status);
            Serial.println("valve 11 ON");
          } else if (strstr(a[j], "CT11:OFF")) {
            flag11 = 0;
            Relay11_OFF();
            // Serial1.println(addDelimiter(data1));
            String dataToSend = ID21 + String(Per_AVG11) + ID22 + String(valve11status) + ID35 + String(flag11);
            Serial1.println(addDelimiter(dataToSend));
            vTaskDelay(1000 / portTICK_PERIOD_MS);
            Serial.print("valve11status ");
            Serial.println(valve11status);
            Serial.println("valve 11 OFF");
          }
          if (strstr(a[j], "CT12:ON")) {
            flag12 = 0;
            Relay12_ON();
            // Serial1.println(addDelimiter(data1));
            String dataToSend = ID23 + String(Per_AVG12) + ID24 + String(valve12status) + ID36 + String(flag12);
            Serial1.println(addDelimiter(dataToSend));
            vTaskDelay(1000 / portTICK_PERIOD_MS);
            Serial.print("valve12status ");
            Serial.println(valve12status);
            Serial.println("valve 12 ON");
          } else if (strstr(a[j], "CT12:OFF")) {
            flag12 = 0;
            Relay12_OFF();
            // Serial1.println(addDelimiter(data1));
            String dataToSend = ID23 + String(Per_AVG12) + ID24 + String(valve12status) + ID36 + String(flag12);
            Serial1.println(addDelimiter(dataToSend));
            vTaskDelay(1000 / portTICK_PERIOD_MS);
            Serial.print("valve12status ");
            Serial.println(valve12status);
            Serial.println("valve 12 OFF");
          }
        }
      }
      // vTaskDelay(500 / portTICK_PERIOD_MS); // Delay for 500ms
      Serial.println("***************Sending Ack data************************");
      Serial.println(data1);
      vTaskDelay(500 / portTICK_PERIOD_MS);  // Delay for 500ms
      Serial.println("*************** Ack sent************************");
    }
    // UBaseType_t stackSize = uxTaskGetStackHighWaterMark(NULL);
    // Serial.print("CTAutomation stack high water mark: ");
    // Serial.println(stackSize);

    // vTaskDelay(100 / portTICK_PERIOD_MS);
  }
}