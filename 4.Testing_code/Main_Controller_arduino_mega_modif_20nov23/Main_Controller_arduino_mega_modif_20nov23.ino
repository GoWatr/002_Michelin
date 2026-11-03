#include <stdio.h>        //input output library
#include <stdint.h>       //integer type library
#include <string.h>       //string library
#include <Wire.h>         //To communicate with i2c
#include "functions.h"    //.h library with hydrostatic and relay functions
#include "flowmeter.h"    //.h library with flowmeter functions
#include <SoftwareReset.h>
char *strcmp_status;      //char pointer
char *strcmp_action;      //char pointer
#define RXp1 19           //defining rx pin of arduino
#define TXp1 18           //defining tx pin of arduino
char delim[] = "*";       //char array with value ";"
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
int flag9 = 1;            //int variable

String ID1 = "&CT1:";                                                                                      //string variable ID1 to ID13 created and used to send the data to api
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
String ID14 = ",?CT7:";                                                                                      //string variable ID1 to ID13 created and used to send the data to api
String ID15 = "&CT8:";
String ID16 = ",?CT8:";
String ID17 = "&CT9:";
String ID18 = ",?CT9:";
String ID19 = "!FMA01T:";
String ID20 = ",!FMA01F:";

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
  pinMode(valve10, OUTPUT);                   //Declaring  the valve9 pin as output
  digitalWrite(valve10, LOW);
  pinMode(valve11, OUTPUT);                   //Declaring  the valve9 pin as output
  digitalWrite(valve11, LOW);
  pinMode(valve12, OUTPUT);                   //Declaring  the valve9 pin as output
  digitalWrite(valve12, LOW);
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
    //delay(1000);                               //delay 2000
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

      strcmp_status = strstr(data0, "*");  //comparing the value with gostatus
      if (strcmp_status)                          //if value is matched
      {
        Serial.println("gostatus");  //printing the value as gostatus
        if (strstr(a[j], "CT1:A"))    //compare the serial value with "v1:a"
        {
          Serial.println("Valve one is automatic");  //Printing "valve one automatic"
          flag1 = 1; 
          Relay10_ON();                                //Setting flag1 as 1
        }
        if (strstr(a[j], "CT1:M"))  //compare the serial value with "v1:m"
        {
          Serial.println("Valve one is manual");  //Printing "valve one manual"
          flag1 = 0;                              //Setting flag1 as 0
          Relay10_OFF();
        }
        if (strstr(a[j], "CT2:A"))  //compare the serial value with "v2:a"
        {
          Serial.println("Valve two is automatic");  //Printing "valve two automatic"
          flag2 = 1;                                 //Setting flag2 as 1
          Relay11_ON();
        }
        if (strstr(a[j], "CT2:M"))  //compare the serial value with "v2:m"
        {
          Serial.println("Valve two is manual");  //Printing "valve two manual"
          flag2 = 0;                              //Setting flag2 as 0
          Relay11_OFF();
        }
        if (strstr(a[j], "CT3:A"))  //compare the serial value with "v3:a"
        {
          Serial.println("Valve 3 is automatic");  //Printing "valve 3 automatic"
          flag3 = 1;                               //Setting flag3 as 1
          Relay12_ON();
        }
        if (strstr(a[j], "CT3:M"))  //compare the serial value with "v3:m"
        {
          Serial.println("Valve 3 is manual");  //Printing "valve 3 manual"
          flag3 = 0;                            //Setting flag3 as 0
          Relay12_OFF();
        }
        if (strstr(a[j], "CT4:A"))  //compare the serial value with "v4:a"
        {
          Serial.println("Valve 4 is automatic");  //Printing "valve 4 automatic"
          flag4 = 1;                               //Setting flag4 as 1
        }
        if (strstr(a[j], "CT4:M"))  //compare the serial value with "v4:m"
        {
          Serial.println("Valve 4 is manual");  //Printing "valve 4 manual"
          flag4 = 0;                            //Setting flag4 as 0
        }
        if (strstr(a[j], "CT5:A"))  //compare the serial value with "v5:a"
        {
          Serial.println("Valve 5 is automatic");  //Printing "valve 5 automatic"
          flag5 = 1;                               //Setting flag5 as 1
        }
        if (strstr(a[j], "CT5:M"))  //compare the serial value with "v5:m"
        {
          Serial.println("Valve 5 is manual");  //Printing "valve 5 manual"
          flag5 = 0;                            //Setting flag5 as 0
        }
        if (strstr(a[j], "CT6:A"))  //compare the serial value with "v6:a"
        {
          Serial.println("Valve 6 is automatic");  //Printing "valve 6 automatic"
          flag6 = 1;                               //Setting flag6 as 1
        }
        if (strstr(a[j], "CT6:M"))  //compare the serial value with "v6:m"
        {
          Serial.println("Valve 6 is manual");  //Printing "valve 6 manual"
          flag6 = 0;                            //Setting flag6 as 0
        }
        if (strstr(a[j], "CT7:A"))  //compare the serial value with "v7:a"
        {
          Serial.println("Valve 7 is automatic");  //Printing "valve 7 automatic"
          flag7 = 1;                               //Setting flag7 as 1
        }
        if (strstr(a[j], "CT7:M"))  //compare the serial value with "v7:m"
        {
          Serial.println("Valve 7 is manual");  //Printing "valve 7 manual"
          flag7 = 0;                            //Setting flag7 as 0
        }
        if (strstr(a[j], "CT8:A"))  //compare the serial value with "v8:a"
        {
          Serial.println("Valve 8 is automatic");  //Printing "valve 8 automatic"
          flag8 = 1;                               //Setting flag8 as 1
        }
        if (strstr(a[j], "CT8:M"))  //compare the serial value with "v8:m"
        {
          Serial.println("Valve 8 is manual");  //Printing "valve 8 manual"
          flag8 = 0;                            //Setting flag8 as 0
        }
        if (strstr(a[j], "CT9:A"))  //compare the serial value with "v9:a"
        {
          Serial.println("Valve 9 is automatic");  //Printing "valve 9 automatic"
          flag9 = 1;                               //Setting flag9 as 1
        }
        if (strstr(a[j], "CT9:M"))  //compare the serial value with "v9:m"
        {
          Serial.println("Valve 9 is manual");  //Printing "valve 9 manual"
          flag9 = 0;                            //Setting flag9 as 0
        }
      }
      strcmp_action = strstr(data0, "@");  //if the data is matched with govalve
      if (strcmp_action)                         //if loop
      {
        Serial.println("goaction");  //printing "goaction"
        if (strstr(a[j], "CT1:ON"))   //compare the value with "v1_on"
        {
          Relay1_ON();                      //calling relay1 on function
          Serial.println("valve1status");   //printing "valve1status"
          Serial.println(valve1status);     //Printing valve1status value
          flag1 = 0;                        //setting flag1 value as 0
          Serial.println("valve one ON");   //Printing "valve one on"
        } else if (strstr(a[j], "CT1:OFF"))  //compare the value with "v1_off"
        {
          Relay1_OFF();                     //calling relay1 off function
          Serial.println(valve1status);     //printing "valve1status"
          flag1 = 0;                        //setting flag1 value as 0
          Serial.println("valve one OFF");  //Printing "valve one on"
        }
        if (strstr(a[j], "CT2:ON"))  //compare the value with "v2_on"
        {
          Relay2_ON();                      //calling relay2 on function
          Serial.println("valve2status");   //printing "valve1status"
          Serial.println(valve2status);     //Printing valve1status value
          flag2 = 0;                        //setting flag1 value as 0
          Serial.println("valve 2 ON");     //Printing "valve one on"
        } else if (strstr(a[j], "CT2:OFF"))  //compare the value with "v2_off"
        {
          Relay2_OFF();                    //calling relay2 off function
          Serial.println("valve2status");  //printing "valve1status"
          Serial.println(valve2status);    //Printing valve1status value
          flag2 = 0;                       //setting flag1 value as 0
          Serial.println("valve 2 OFF");   //Printing "valve one on"
        }
        if (strstr(a[j], "CT3:ON"))  //compare the value with "v3_on"
        {
          Relay3_ON();                      //calling relay3 on function
          Serial.println("valve3status");   //printing "valve1status"
          Serial.println(valve3status);     //Printing valve1status value
          flag3 = 0;                        //setting flag1 value as 0
          Serial.println("valve 3 ON");     //Printing "valve one on"
        } else if (strstr(a[j], "CT3:OFF"))  //compare the value with "v3_off"
        {
          Relay3_OFF();                    //calling relay3 off function
          Serial.println("valve3status");  //printing "valve1status"
          Serial.println(valve3status);    //Printing valve1status value
          flag3 = 0;                       //setting flag1 value as 0
          Serial.println("valve 3 OFF");   //Printing "valve one on"
        }
        if (strstr(a[j], "CT4:ON"))  //compare the value with "v4_on"
        {
          Serial.println("valve 4 ON");
          Relay4_ON();                      //calling relay4 on function
          Serial.println("valve4status");   //printing "valve1status"
          Serial.println(valve4status);     //Printing valve1status value
          flag4 = 0;                        //setting flag1 value as 0
        } else if (strstr(a[j], "CT4:OFF"))  //compare the value with "v4_off"
        {
          Serial.println("valve 4 OFF");
          Relay4_OFF();                    //calling relay4 off function
          Serial.println("valve4status");  //printing "valvestatus"
          Serial.println(valve4status);    //Printing valve4status value
          flag4 = 0;                       //setting flag4 value as 0
        }
        if (strstr(a[j], "CT5:ON"))  //compare the value with "v5_on"
        {
          Serial.println("valve 5 ON");
          Relay5_ON();                      //calling relay5 on function
          Serial.println("valve5status");   //printing "valve5status"
          Serial.println(valve5status);     //Printing valve5status value
          flag5 = 0;                        //setting flag5 value as 0
        } else if (strstr(a[j], "CT5:OFF"))  //compare the value with "v5_off"
        {
          Serial.println("valve 5 OFF");
          Relay5_OFF();                    //calling relay5 off function
          Serial.println("valve5status");  //printing "valve5status"
          Serial.println(valve5status);    //Printing valve5status value
          flag5 = 0;                       //setting flag5 value as 0
        }
        if (strstr(a[j], "CT6:ON"))  //compare the value with "v6_on"
        {
          Relay6_ON();                      //calling relay6 on function
          Serial.println("valve6status");   //printing "valve6status"
          Serial.println(valve6status);     //Printing valve6status value
          flag6 = 0;                        //setting flag6 value as 0
          Serial.println("valve 6 ON");     //Printing "valve6 on"
        } else if (strstr(a[j], "CT6:OFF"))  //compare the value with "v6_off"
        {
          Relay6_OFF();                    //calling relay6 off function
          Serial.println("valve6status");  //printing "valve6status"
          Serial.println(valve6status);    //Printing valve6status value
          flag6 = 0;                       //setting flag6 value as 0
          Serial.println("valve 6 OFF");   //Printing "valve on6 on"
        }
        if (strstr(a[j], "CT7:ON"))  //compare the value with "v7_on"
        {
          Relay7_ON();                      //calling relay7 on function
          Serial.println("valve7status");   //printing "valve7status"
          Serial.println(valve7status);     //Printing valve7status value
          flag7 = 0;                        //setting flag7 value as 0
          Serial.println("valve 7 ON");     //Printing "valve 7 on"
        } else if (strstr(a[j], "CT7:OFF"))  //compare the value with "v7_off"
        {
          Relay7_OFF();                    //calling relay7 off function
          Serial.println("valve7status");  //printing "valve7status"
          Serial.println(valve7status);    //Printing valve7status value
          flag7 = 0;                       //setting flag7 value as 0
          Serial.println("valve 7 OFF");   //Printing "valve 7 on"
        }
        if (strstr(a[j], "CT8:ON"))  //compare the value with "v8_on"
        {
          Relay8_ON();                      //calling relay8 on function
          Serial.println("valve8status");   //printing "valve8status"
          Serial.println(valve8status);     //Printing valve8status value
          flag8 = 0;                        //setting flag8 value as 0
          Serial.println("valve 8 ON");     //Printing "valve 8 on"
        } else if (strstr(a[j], "CT8:OFF"))  //compare the value with "v8_off"
        {
          Relay8_OFF();                    //calling relay8 off function
          Serial.println("valve8status");  //printing "valve8status"
          Serial.println(valve8status);    //Printing valve9status value
          flag8 = 0;                       //setting flag8 value as 0
          Serial.println("valve 8 OFF");   //Printing "valve 8 on"
        }
        if (strstr(a[j], "CT9:ON"))  //compare the value with "v9_on"
        {
          Relay9_ON();                      //calling relay9 on function
          Serial.println("valve9status");   //printing "valve9status"
          Serial.println(valve9status);     //Printing valve9status value
          flag9 = 0;                        //setting flag9 value as 0
          Serial.println("valve 9 ON");     //Printing "valve 9 on"
        } else if (strstr(a[j], "CT9:OFF"))  //compare the value with "v9_off"
        {
          Relay9_OFF();                    //calling relay9 off function
          Serial.println("valve9status");  //printing "valve9status"
          Serial.println(valve9status);    //Printing valve9status value
          flag9 = 0;                       //setting flag9 value as 0
          Serial.println("valve 9 OFF");   //Printing "valve 9 off"
        }
      }
    }
    delay(1000);             //delay 200///////////////////////////////////////////////////////////////ji change to 1000 if it is problem change previous value
    Serial.println("***************Sending Ack data************************");
    Serial1.println(data1);  //Sending data via serial to lora heltec board
    Serial.println(data1);   //printing data1 value
    delay(100);
    Serial.println("*************** Ack sent************************");
  }
  Hydrostatic1();  //call hydrostatic1 function
  delay(10);
  Hydrostatic2();  //call hydrostatic2 function
  delay(10);
  Hydrostatic3();  //call hydrostatic3 function
  delay(10);
  Hydrostatic4();  //call hydrostatic4 function
  delay(10);
  Hydrostatic5();  //call hydrostatic5 function
  delay(10);
  Hydrostatic6();  //call hydrostatic6 function
  delay(10);
  Hydrostatic7();  //call hydrostatic7 function
  delay(10);
  Hydrostatic8();  //call hydrostatic8 function
  delay(10);
  Hydrostatic9();  //call hydrostatic9 function
  delay(10);
  MODBUS();        //modbus function called to read flowmeter data
  delay(10);


  if (flag1 == 1)  //if flag1 is equal to 1
  {
    delay(100);
    if (Per_AVG1 <= 85)  //45
    {
      Relay1_ON();         //call relay1 on function
    } else if (Per_AVG1 >= 95)  //>=50
    {
      Relay1_OFF();  //call relay2 function
    }
  }
  if (flag2 == 1)  //all flag conditions are similar to flag1 condition mentioned above
  {
    delay(100);
    if (Per_AVG2 <= 85) {//45
      Relay2_ON();
    } else if (Per_AVG2 >= 95) {//50
      Relay2_OFF();
    }
  }

  if (flag3 == 1) {
    delay(100);
    if (Per_AVG3 <= 85) {//45
      Relay3_ON();
    } else if (Per_AVG3 >= 95) {//50
      Relay3_OFF();
    }
  }

  if (flag4 == 1) {
    delay(100);
    if (Per_AVG4 <= 85) {//45
      Relay4_ON();
    } else if (Per_AVG4 >= 100) {//50
      Relay4_OFF();
    }
  }

  if (flag5 == 1) {
    delay(100);
    if (Per_AVG5 <= 85) {//45
      Relay5_ON();
    } else if (Per_AVG5 >= 95) {//50
      Relay5_OFF();
    }
  }
  if (flag6 == 1) {
    delay(100);
    if (Per_AVG6 <= 85) {//45
      Relay6_ON();
    } else if (Per_AVG6 > 95) {//50
      Relay6_OFF();
    }
  }

  if (flag7 == 1) {
    delay(100);
    if (Per_AVG7 <= 85) {//50
      Relay7_ON();

    } else if (Per_AVG7 >= 95) {//55
      Relay7_OFF();
    }
  }

  if (flag8 == 1) {
    delay(100);
    if (Per_AVG8 <= 85) {//45
      Relay8_ON();
    } else if (Per_AVG8 >= 95) {//50
      Relay8_OFF();
    }
  }
  if (flag9 == 1) {
    delay(100);
    if (Per_AVG9 <= 50) {
      Relay9_ON();
    } else if (Per_AVG9 > 55) {
      Relay9_OFF();
    }
  }
  delay(500);
  Counter++;
  delay(1000);                     // counter increment
  Serial.println("count is");
  Serial.println(Counter);
  if (Counter == 1)  //if counter is one id1,id2 data will be sent to heltec lora via serial
  {
    Serial.println(ID1+String(Per_AVG1)+ID2+String(valve1status));
    //delay(500);
    Serial1.println(ID1+String(Per_AVG1)+ID2+String(valve1status));
    delay(1000);
  }

if (Counter == 2)  //if counter is one id1,id2 data will be sent to heltec lora via serial
  {
    Serial.println(ID3+String(Per_AVG2)+ID4+String(valve2status));
    //delay(500);
    Serial1.println(ID3+String(Per_AVG2)+ID4+String(valve2status));
    delay(1000);
  }
  if (Counter == 3)  //if counter is one id1,id2 data will be sent to heltec lora via serial
  {
    Serial.println(ID5+String(Per_AVG3)+ID6+String(valve3status));
    //delay(500);
    Serial1.println(ID5+String(Per_AVG3)+ID6+String(valve3status));
    delay(1000);
  }
  if (Counter == 4)  //if counter is 2 id3,id4 data will be sent to heltec lora via serial
  {
    Serial.println(ID7+String(Per_AVG4)+ID8+String(valve4status));
    //delay(500);
    Serial1.println(ID7+String(Per_AVG4)+ID8+String(valve4status));
    delay(1000);
  }
  if (Counter == 5)  //if counter is 3 id5,id6 data will be sent to heltec lora via serial
  {
    Serial.println(ID9+String(Per_AVG5)+ID10+String(valve5status));
    Serial1.println(ID9+String(Per_AVG5)+ID10+String(valve5status));
    delay(1000);
  }
if (Counter == 6)  //if counter is 3 id5,id6 data will be sent to heltec lora via serial
  {
    Serial.println(ID11+String(Per_AVG6)+ID12+String(valve6status));
    Serial1.println(ID11+String(Per_AVG6)+ID12+String(valve6status));
    delay(1000);
  }
  if (Counter == 7)  //if counter is 4 id7,id8 data will be sent to heltec lora via serial

  {
    Serial.println(ID13+String(Per_AVG7)+ID14+String(valve7status));
    Serial1.println(ID13+String(Per_AVG7)+ID14+String(valve7status));
    delay(1000);
  }

if (Counter == 8)  //if counter is 4 id7,id8 data will be sent to heltec lora via serial

  {
    Serial.println(ID15+String(Per_AVG8)+ID16+String(valve8status));
    Serial1.println(ID15+String(Per_AVG8)+ID16+String(valve8status));
    delay(1000);
  }

  if (Counter == 9)  //if counter is 5 id9 data will be sent
  {
    Serial.println(ID17+String(Per_AVG9)+ID18+String(valve9status));
    Serial1.println(ID17+String(Per_AVG9)+ID18+String(valve9status)); 
    delay(1000);
  }
  if (Counter == 10)  //if counter is 5 id9 data will be sent
  {
      
    delay(1000);
    Serial.println(ID19+String(Tot)+ID20+String(Flow));
    Serial1.println(ID19+String(Tot)+ID20+String(Flow));
    delay(1000);
    //Tot = 0;
    Flow = 0;
    Counter = 0;
  }
}
