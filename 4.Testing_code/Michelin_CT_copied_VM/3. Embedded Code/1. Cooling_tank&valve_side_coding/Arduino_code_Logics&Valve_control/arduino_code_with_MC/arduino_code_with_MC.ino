
#include <stdio.h>        //input output library
#include <stdint.h>       //integer type library
#include <string.h>       //string library
#include <Wire.h>         //To communicate with i2c
#include "functions.h"    //.h library with hydrostatic and relay functions
#include "flowmeter.h"    //.h library with flowmeter functions
char *strcmp_status;      //char pointer
char *strcmp_action;      //char pointer
#define RXp1 19           //defining rx pin of arduino
#define TXp1 18           //defining tx pin of arduino
char delim[] = ";";       //char array with value ";"
char data0[63] = { 0 };  //char buffer
char data1[100] = { 0 };  //char buffer
char a[15][100] = { 0 };  //two dimensional char array
int flag1 = 1;            //int variable
int flag2 = 1;            //int variable
int flag3 = 1;            //int variable
int flag4 = 1;            //int variable
int flag5 = 1;            //int variable
int flag6 = 1;            //int variable
int flag7 = 1;            //int variable
int flag8 = 1;            //int variable
int flag9 = 0;            //int variable



void setup()  //setup function
{
  Serial.begin(115200);  //setting the serial baud rate to 115200

  Serial1.begin(9600);  //setting the serial1 baud rate to 9600
  mod.begin(9600);
  Serial.println("michelin valve control");  //printing the value as "michelin valve control"
  pinMode(valve1, OUTPUT);                   //Declaring  the valve1 pin as output
  digitalWrite(valve1, LOW);                 //initially the valve1 pin is low
  pinMode(valve2, OUTPUT);                   //Declaring  the valve2 pin as output
  digitalWrite(valve2, LOW);                 //initially the valve2 pin is low
  pinMode(valve3, OUTPUT);                   //Declaring  the valve3 pin as output
  digitalWrite(valve3, LOW);                 //initially the valve3 pin is low
  pinMode(valve4, OUTPUT);                   //Declaring  the valve4 pin as output
  digitalWrite(valve4, LOW);                 //initially the valve4 pin is low
  pinMode(valve5, OUTPUT);                   //Declaring  the valve5 pin as output
  digitalWrite(valve5, LOW);                 //initially the valve5 pin is low
  pinMode(valve6, OUTPUT);                   //Declaring  the valve6 pin as output
  digitalWrite(valve6, LOW);                 //initially the valve6 pin is low
  pinMode(valve7, OUTPUT);                   //Declaring  the valve7 pin as output
  digitalWrite(valve7, LOW);                 //initially the valve7 pin is low
  pinMode(valve8, OUTPUT);                   //Declaring  the valve8 pin as output
  digitalWrite(valve8, LOW);                 //initially the valve8 pin is low
  pinMode(valve9, OUTPUT);                   //Declaring  the valve9 pin as output
  digitalWrite(valve9, LOW);                 //initially the valve9 pin is low
}


void loop()  //Main loop starts here
{
  int i = 0;                //declaring i variable is zero
  if (Serial1.available())  //Checking continuously for serial data
  {
    memset(data0,0,sizeof(data0));
    Serial.println("inside serial check");     //printing the value as "inside serial check"
    Serial1.readBytesUntil('\n', data0, 63);  //read the serial data and storing in data0
    Serial.print("Received: ");                //printing the value as "received"
    Serial.println(data0);                     //print the value in data0
    memset(data1, 0, sizeof(data1));           //clearing the data1 buffer
    strcpy(data1, data0);                      //copying the data0 value to data1
    Serial.println(data1);                     //printing the data1 value
    delay(2000);                               //delay 2000
    char *ptr = strtok(data0, delim);          //breaking the strings based on delimiter
    while (ptr != NULL)                        //while function to split the data
    {
      sprintf(a[i], "%s", ptr);  //copy the data in ptr to a buffer

      ptr = strtok(NULL, delim);  //breaking the strings based on delimiter
      i++;                        //increment i
    }

    Serial.println(i);           //printing the i value
    for (int j = 0; j < i; j++)  //for loop with i range
    {
      Serial.println(a[j]);  //printing the a value

      strcmp_status = strstr(data0, "gostatus");  //comparing the value with gostatus
      if (strcmp_status)                          //if value is matched
      {
        Serial.println("gostatus");  //printing the value as gostatus
        if (strstr(a[j], "V1:A"))    //compare the serial value with "v1:a"
        {
          Serial.println("Valve one is automatic");  //Printing "valve one automatic"
          flag1 = 1;                                 //Setting flag1 as 1
        }
        if (strstr(a[j], "V1:M"))  //compare the serial value with "v1:m"
        {
          Serial.println("Valve one is manual");  //Printing "valve one manual"
          flag1 = 0;                              //Setting flag1 as 0
        }
        if (strstr(a[j], "V2:A"))  //compare the serial value with "v2:a"
        {
          Serial.println("Valve two is automatic");  //Printing "valve two automatic"
          flag2 = 1;                                 //Setting flag2 as 1
        }
        if (strstr(a[j], "V2:M"))  //compare the serial value with "v2:m"
        {
          Serial.println("Valve two is manual");  //Printing "valve two manual"
          flag2 = 0;                              //Setting flag2 as 0
        }
        if (strstr(a[j], "V3:A"))  //compare the serial value with "v3:a"
        {
          Serial.println("Valve 3 is automatic");  //Printing "valve 3 automatic"
          flag3 = 1;                               //Setting flag3 as 1
        }
        if (strstr(a[j], "V3:M"))  //compare the serial value with "v3:m"
        {
          Serial.println("Valve 3 is manual");  //Printing "valve 3 manual"
          flag3 = 0;                            //Setting flag3 as 0
        }
        if (strstr(a[j], "V4:A"))  //compare the serial value with "v4:a"
        {
          Serial.println("Valve 4 is automatic");  //Printing "valve 4 automatic"
          flag4 = 1;                               //Setting flag4 as 1
        }
        if (strstr(a[j], "V4:M"))  //compare the serial value with "v4:m"
        {
          Serial.println("Valve 4 is manual");  //Printing "valve 4 manual"
          flag4 = 0;                            //Setting flag4 as 0
        }
        if (strstr(a[j], "V5:A"))  //compare the serial value with "v5:a"
        {
          Serial.println("Valve 5 is automatic");  //Printing "valve 5 automatic"
          flag5 = 1;                               //Setting flag5 as 1
        }
        if (strstr(a[j], "V5:M"))  //compare the serial value with "v5:m"
        {
          Serial.println("Valve 5 is manual");  //Printing "valve 5 manual"
          flag5 = 0;                            //Setting flag5 as 0
        }
        if (strstr(a[j], "V6:A"))  //compare the serial value with "v6:a"
        {
          Serial.println("Valve 6 is automatic");  //Printing "valve 6 automatic"
          flag6 = 1;                               //Setting flag6 as 1
        }
        if (strstr(a[j], "V6:M"))  //compare the serial value with "v6:m"
        {
          Serial.println("Valve 6 is manual");  //Printing "valve 6 manual"
          flag6 = 0;                            //Setting flag6 as 0
        }
        if (strstr(a[j], "V7:A"))  //compare the serial value with "v7:a"
        {
          Serial.println("Valve 7 is automatic");  //Printing "valve 7 automatic"
          flag7 = 1;                               //Setting flag7 as 1
        }
        if (strstr(a[j], "V7:M"))  //compare the serial value with "v7:m"
        {
          Serial.println("Valve 7 is manual");  //Printing "valve 7 manual"
          flag7 = 0;                            //Setting flag7 as 0
        }
        if (strstr(a[j], "V8:A"))  //compare the serial value with "v8:a"
        {
          Serial.println("Valve 8 is automatic");  //Printing "valve 8 automatic"
          flag8 = 1;                               //Setting flag8 as 1
        }
        if (strstr(a[j], "V8:M"))  //compare the serial value with "v8:m"
        {
          Serial.println("Valve 8 is manual");  //Printing "valve 8 manual"
          flag8 = 0;                            //Setting flag8 as 0
        }
        if (strstr(a[j], "V9:A"))  //compare the serial value with "v9:a"
        {
          Serial.println("Valve 9 is automatic");  //Printing "valve 9 automatic"
          flag9 = 1;                               //Setting flag9 as 1
        }
        if (strstr(a[j], "V9:M"))  //compare the serial value with "v9:m"
        {
          Serial.println("Valve 9 is manual");  //Printing "valve 9 manual"
          flag9 = 0;                            //Setting flag9 as 0
        }
      }
      strcmp_action = strstr(data0, "govalve");  //if the data is matched with govalve
      if (strcmp_action)                         //if loop
      {
        Serial.println("goaction");  //printing "goaction"
        if (strstr(a[j], "v1_on"))   //compare the value with "v1_on"
        {
          Relay1_ON();                      //calling relay1 on function
          Serial.println("valve1status");   //printing "valve1status"
          Serial.println(valve1status);     //Printing valve1status value
          flag1 = 0;                        //setting flag1 value as 0
          Serial.println("valve one ON");   //Printing "valve one on"
        } else if (strstr(a[j], "v1_off"))  //compare the value with "v1_off"
        {
          Relay1_OFF();                     //calling relay1 off function
          Serial.println(valve1status);     //printing "valve1status"
          flag1 = 0;                        //setting flag1 value as 0
          Serial.println("valve one OFF");  //Printing "valve one on"
        }
        if (strstr(a[j], "v2_on"))  //compare the value with "v2_on"
        {
          Relay2_ON();                      //calling relay2 on function
          Serial.println("valve2status");   //printing "valve1status"
          Serial.println(valve2status);     //Printing valve1status value
          flag2 = 0;                        //setting flag1 value as 0
          Serial.println("valve 2 ON");     //Printing "valve one on"
        } else if (strstr(a[j], "v2_off"))  //compare the value with "v2_off"
        {
          Relay2_OFF();                    //calling relay2 off function
          Serial.println("valve2status");  //printing "valve1status"
          Serial.println(valve2status);    //Printing valve1status value
          flag2 = 0;                       //setting flag1 value as 0
          Serial.println("valve 2 OFF");   //Printing "valve one on"
        }
        if (strstr(a[j], "v3_on"))  //compare the value with "v3_on"
        {
          Relay3_ON();                      //calling relay3 on function
          Serial.println("valve3status");   //printing "valve1status"
          Serial.println(valve3status);     //Printing valve1status value
          flag3 = 0;                        //setting flag1 value as 0
          Serial.println("valve 3 ON");     //Printing "valve one on"
        } else if (strstr(a[j], "v3_off"))  //compare the value with "v3_off"
        {
          Relay3_OFF();                    //calling relay3 off function
          Serial.println("valve3status");  //printing "valve1status"
          Serial.println(valve3status);    //Printing valve1status value
          flag3 = 0;                       //setting flag1 value as 0
          Serial.println("valve 3 OFF");   //Printing "valve one on"
        }
        if (strstr(a[j], "v4_on"))  //compare the value with "v4_on"
        {
          Serial.println("valve 4 ON");
          Relay4_ON();                      //calling relay4 on function
          Serial.println("valve4status");   //printing "valve1status"
          Serial.println(valve4status);     //Printing valve1status value
          flag4 = 0;                        //setting flag1 value as 0
        } else if (strstr(a[j], "v4_off"))  //compare the value with "v4_off"
        {
          Serial.println("valve 4 OFF");
          Relay4_OFF();                    //calling relay4 off function
          Serial.println("valve4status");  //printing "valvestatus"
          Serial.println(valve4status);    //Printing valve4status value
          flag4 = 0;                       //setting flag4 value as 0
        }
        if (strstr(a[j], "v5_on"))  //compare the value with "v5_on"
        {
          Serial.println("valve 5 ON");
          Relay5_ON();                      //calling relay5 on function
          Serial.println("valve5status");   //printing "valve5status"
          Serial.println(valve5status);     //Printing valve5status value
          flag5 = 0;                        //setting flag5 value as 0
        } else if (strstr(a[j], "v5_off"))  //compare the value with "v5_off"
        {
          Serial.println("valve 5 OFF");
          Relay5_OFF();                    //calling relay5 off function
          Serial.println("valve5status");  //printing "valve5status"
          Serial.println(valve5status);    //Printing valve5status value
          flag5 = 0;                       //setting flag5 value as 0
        }
        if (strstr(a[j], "v6_on"))  //compare the value with "v6_on"
        {
          Relay6_ON();                      //calling relay6 on function
          Serial.println("valve6status");   //printing "valve6status"
          Serial.println(valve6status);     //Printing valve6status value
          flag6 = 0;                        //setting flag6 value as 0
          Serial.println("valve 6 ON");     //Printing "valve6 on"
        } else if (strstr(a[j], "v6_off"))  //compare the value with "v6_off"
        {
          Relay6_OFF();                    //calling relay6 off function
          Serial.println("valve6status");  //printing "valve6status"
          Serial.println(valve6status);    //Printing valve6status value
          flag6 = 0;                       //setting flag6 value as 0
          Serial.println("valve 6 OFF");   //Printing "valve on6 on"
        }
        if (strstr(a[j], "v7_on"))  //compare the value with "v7_on"
        {
          Relay7_ON();                      //calling relay7 on function
          Serial.println("valve7status");   //printing "valve7status"
          Serial.println(valve7status);     //Printing valve7status value
          flag7 = 0;                        //setting flag7 value as 0
          Serial.println("valve 7 ON");     //Printing "valve 7 on"
        } else if (strstr(a[j], "v7_off"))  //compare the value with "v7_off"
        {
          Relay7_OFF();                    //calling relay7 off function
          Serial.println("valve7status");  //printing "valve7status"
          Serial.println(valve7status);    //Printing valve7status value
          flag7 = 0;                       //setting flag7 value as 0
          Serial.println("valve 7 OFF");   //Printing "valve 7 on"
        }
        if (strstr(a[j], "v8_on"))  //compare the value with "v8_on"
        {
          Relay8_ON();                      //calling relay8 on function
          Serial.println("valve8status");   //printing "valve8status"
          Serial.println(valve8status);     //Printing valve8status value
          flag8 = 0;                        //setting flag8 value as 0
          Serial.println("valve 8 ON");     //Printing "valve 8 on"
        } else if (strstr(a[j], "v8_off"))  //compare the value with "v8_off"
        {
          Relay8_OFF();                    //calling relay8 off function
          Serial.println("valve8status");  //printing "valve8status"
          Serial.println(valve8status);    //Printing valve9status value
          flag8 = 0;                       //setting flag8 value as 0
          Serial.println("valve 8 OFF");   //Printing "valve 8 on"
        }
        if (strstr(a[j], "v9_on"))  //compare the value with "v9_on"
        {
          Relay9_ON();                      //calling relay9 on function
          Serial.println("valve9status");   //printing "valve9status"
          Serial.println(valve9status);     //Printing valve9status value
          flag9 = 0;                        //setting flag9 value as 0
          Serial.println("valve 9 ON");     //Printing "valve 9 on"
        } else if (strstr(a[j], "v9_off"))  //compare the value with "v9_off"
        {
          Relay9_OFF();                    //calling relay9 off function
          Serial.println("valve9status");  //printing "valve9status"
          Serial.println(valve9status);    //Printing valve9status value
          flag9 = 0;                       //setting flag9 value as 0
          Serial.println("valve 9 OFF");   //Printing "valve 9 off"
        }
      }
    }
    delay(2000);             //delay 200
    Serial.println("***************Sending Ack data************************");
    Serial1.println(data1);  //Sending data via serial to lora heltec board
    Serial.println(data1);   //printing data1 value
    delay(2000);
    Serial.println("*************** Ack sent************************");
  }
  Hydrostatic1();  //call hydrostatic1 function
  delay(100);
  Hydrostatic2();  //call hydrostatic2 function
  delay(100);
  Hydrostatic3();  //call hydrostatic3 function
  delay(100);
  Hydrostatic4();  //call hydrostatic4 function
  delay(100);
  Hydrostatic5();  //call hydrostatic5 function
  delay(100);
  Hydrostatic6();  //call hydrostatic6 function
  delay(100);
  Hydrostatic7();  //call hydrostatic7 function
  delay(100);
  Hydrostatic8();  //call hydrostatic8 function
  delay(100);
  Hydrostatic9();  //call hydrostatic9 function
  delay(100);



  if (flag1 == 1)  //if flag1 is equal to 1
  {
    delay(100);
    if (AVG1 < 45)  //if avg value less than 20
    {
      Relay1_ON();         //call relay1 on function
    } else if (AVG1 >= 50)  //if avg value greater than 20
    {
      Relay1_OFF();  //call relay2 function
    }
  }
  if (flag2 == 1)  //all flag conditions are similar to flag1 condition mentioned above
  {
    delay(100);
    if (AVG2 < 43) {
      Relay2_ON();
    } else if (AVG2 >= 46) {
      Relay2_OFF();
    }
  }

  if (flag3 == 1) {
    delay(100);
    if (AVG3 < 45) {
      Relay3_ON();
    } else if (AVG3 >= 50) {
      Relay3_OFF();
    }
  }

  if (flag4 == 1) {
    delay(100);
    if (AVG4 < 45) {
      Relay4_ON();
    } else if (AVG4 >= 50) {
      Relay4_OFF();
    }
  }

  if (flag5 == 1) {
    delay(100);
    if (AVG5 < 45) {
      Relay5_ON();
    } else if (AVG5 >= 50) {
      Relay5_OFF();
    }
  }
  if (flag6 == 1) {
    delay(100);
    if (AVG6 < 45) {
      Relay6_ON();
    } else if (AVG6 >= 47) {
      Relay6_OFF();
    }
  }

  if (flag7 == 1) {
    delay(100);
    if (AVG7 < 50) {
      Relay7_ON();

    } else if (AVG7 >= 55) {
      Relay7_OFF();
    }
  }

  if (flag8 == 1) {
    delay(100);
    if (AVG8 < 45) {
      Relay8_ON();
    } else if (AVG8 >= 50) {
      Relay8_OFF();
    }
  }
  if (flag9 == 1) {
    delay(100);
    if (AVG9 <= 50) {
      Relay9_ON();
    } else if (AVG9 > 55) {
      Relay9_OFF();
    }
  }
  delay(500);
  Counter++;                     // counter increment
  StaticJsonDocument<300> doc;   //doc memory allocated
  StaticJsonDocument<300> doc1;  //doc1 memory allocated
  StaticJsonDocument<300> doc2;  //doc2 memory allocated
  StaticJsonDocument<300> doc3;  //doc3 memory allocated
  StaticJsonDocument<300> doc4;  //doc4 memory allocated
  StaticJsonDocument<300> doc5;  //doc5 memory allocated
  doc["ID1"] = "GOWATRONE";      //assigning values like key and value we are assigning id,raw value,valvestatus
  doc["CT1"] = String(AVG1);
  doc["v1"] = String(valve1status);
  doc["CT2"] = String(AVG2);
  doc["v2"] = String(valve2status);
  doc1["ID2"] = "GOWATRTWO";  //ALL NINE VALVE STATUS,RAW VALUE ASSIGNED
  doc1["CT3"] = String(AVG3);
  doc1["v3"] = String(valve3status);
  doc1["CT4"] = String(AVG4);
  doc1["v4"] = String(valve4status);
  doc2["ID3"] = "GOWATRTHR";
  doc2["CT5"] = String(AVG5);
  doc2["v5"] = String(valve5status);
  doc2["CT6"] = String(AVG6);
  doc2["v6"] = String(valve6status);
  doc3["ID4"] = "GOWATRFOUR";
  doc3["CT7"] = String(AVG7);
  doc3["v7"] = String(valve7status);
  doc3["CT8"] = String(AVG8);
  doc3["v8"] = String(valve8status);


  /*serializeJson(doc, Serial);  //in json format value will print in serial
  Serial.println();
  serializeJson(doc1, Serial);
  Serial.println();
  serializeJson(doc2, Serial);
  Serial.println();
  serializeJson(doc3, Serial);
  Serial.println();*/
  Serial.println("count is");
  Serial.println(Counter);
  if (Counter == 1)  //if counter is one id1,id2 data will be sent to heltec lora via serial
  {
    serializeJson(doc, Serial);
    delay(500);
    serializeJson(doc, Serial1);
    Serial.println();
    delay(100);
    Counter = 2;  //Increased the counter value here
    delay(5000);  //inorder to avoid the serial data loss we are giving delay We  can change the delay here
  }
  if (Counter == 2)  //if counter is 2 id3,id4 data will be sent to heltec lora via serial
  {
    serializeJson(doc1, Serial);
    delay(500);
    serializeJson(doc1, Serial1);
    Serial.println();
    delay(100);
    Counter = 3;
    delay(5000);
  }
  if (Counter == 3)  //if counter is 3 id5,id6 data will be sent to heltec lora via serial
  {
    serializeJson(doc2, Serial);
    delay(500);
    serializeJson(doc2, Serial1);
    Serial.println();
    delay(100);
    Counter = 4;
    delay(5000);
  }
  if (Counter == 4)  //if counter is 4 id7,id8 data will be sent to heltec lora via serial

  {
    serializeJson(doc3, Serial);
    delay(500);
    serializeJson(doc3, Serial1);
    delay(100);
    Counter = 5;
    delay(5000);
  }
  if (Counter == 5)  //if counter is 5 id9 data will be sent
  {
    Serial.println("count 5");
    doc4["ID5"] = "GOWATRFIVE";
    doc4["CT9"] = String(AVG9);
    doc4["v9"] = String(valve9status);
    serializeJson(doc4, Serial);
    delay(500);
    serializeJson(doc4, Serial1);
    Serial.println();
    delay(1000);
    MODBUS();  //modbus function called to read flowmeter data
    delay(5000);
    doc5["ID6"] = "GOWATRSIX";
    doc5["CT10"] = String(Flow);  //flowmeter data will be sent to heltec via serial
    doc5["TOT"] = String(Tot);
    serializeJson(doc5, Serial1);
    delay(2000);
    //serializeJson(doc4, Serial);
    //delay(100);
    Tot = 0;
    Flow = 0;
    Counter = 0;
  }
}
