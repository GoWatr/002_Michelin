#include <ArduinoJson.h>                                                                                          //include arduino json function


int Raw1,Raw2,Raw3,Raw4,Raw5,Raw6,Raw7,Raw8,Raw9,Raw10,Raw11,Raw12,Counter = 0;                                  //INITIALIZING VARIABLES
int AVG1,AVG2,AVG3,AVG4,AVG5,AVG6,AVG7,AVG8,AVG9,AVG10,AVG11,AVG12 = 0;
int OHTcm1,OHTcm2,OHTcm3,OHTcm4,OHTcm5,OHTcm6,OHTcm7,OHTcm8,OHTcm9,OHTcm10,OHTcm11,OHTcm12 = 0;
int valve1status,valve2status,valve3status,valve4status,valve5status,valve6status,valve7status,valve8status,valve9status,valve10status,valve11status,valve12status = 0;


#define valve1 5                                            //DEFINE VALVE PINS                                                         
#define valve2 4
#define valve3 3
#define valve4 2
#define valve5 14  //12
#define valve6 11  //11
#define valve7 10  //10
#define valve8 9  //9
#define valve9 8 //8
//#define valve10 
//#define valve11 11
//#define valve12 10
void Hydrostatic1(void)
{                                                  //Hydrosatatic sensor reading functions and relay function is mentioned in this .h file
  //lcd.clear(); 
  for(int k=0;k<=20;k++)
  {                                                //20 RAW VALUES TAKEN AND MADE AVG AND STORED IN AVG1 VARIABLE
    delay(100);
    Raw1 = analogRead(A0);
    //Serial.print("Raw Value1 = " );
    //Serial.println(Raw1);
    AVG1 = AVG1 + Raw1;
   }
    AVG1 = AVG1/20;
    Serial.print("average 1 = " );
    Serial.println(AVG1);    
}
void Hydrostatic2(void)                         //All hydrostatic functions are similar as mentioned above
{
  for(int k=0;k<=20;k++)
  {
    delay(100);
    Raw2 = analogRead(A1);
    //Serial.println("Raw Value2 = " );
    //Serial.println(Raw2);
    AVG2 = AVG2 + Raw2;
   }
    AVG2 = AVG2/20;
    Serial.print("average 2 = " );
    Serial.println(AVG2);
}

void Hydrostatic3(void)
{
  for(int k=0;k<=20;k++)
  {
    delay(100);
    Raw3 = analogRead(A3);
    //Serial.println("Raw Value3 = " );
    //Serial.println(Raw3);
    AVG3 = AVG3 + Raw3;
   }
    AVG3 = AVG3/20;
    Serial.print("average 3 = " );
    Serial.println(AVG3);
}

void Hydrostatic4(void)
{
  for(int k=0;k<=20;k++)
  {
    delay(100);
    Raw4 = analogRead(A4);
    //Serial.println("Raw Value4 = " );
    //Serial.println(Raw4);
    AVG4 = AVG4 + Raw4;
    }
    AVG4 = AVG4/20;
    Serial.print("average 4 = " );
    Serial.println(AVG4);
}

void Hydrostatic5(void)
{
  for(int k=0;k<=20;k++)
  {
    delay(100);
    Raw5 = analogRead(A6);
    //Serial.println("Raw Value5 = " );
    //Serial.println(Raw5);
    AVG5 = AVG5 + Raw5;
   }
    AVG5=AVG5/20;
    Serial.print("average 5 = " );
    Serial.println(AVG5);
}

void Hydrostatic6(void)
{
  for(int k=0;k<=20;k++)
  {
    delay(100);
    Raw6 = analogRead(A7);
    //Serial.println("Raw Value6 = " );
    //Serial.println(Raw6);
    AVG6 = AVG6 + Raw6;
    
  }
    AVG6 = AVG6/20;
    Serial.print("average 6 = " );
    Serial.println(AVG6);
}

void Hydrostatic7(void)
{
  for(int k=0;k<=20;k++)
  {
    delay(100);
    Raw7 = analogRead(A12);
    //Serial.println("Raw Value7 = " );
    //Serial.println(Raw7);
    AVG7 = AVG7 + Raw7;
   }
   AVG7 = AVG7/20;
   Serial.print("average 7 = " );
   Serial.println(AVG7);
}

void Hydrostatic8(void)
{
  for(int k=0;k<=20;k++)
  {
    delay(100);
    Raw8 = analogRead(A13);
    //Serial.println("Raw Value8 = " );
    //Serial.println(Raw8);
    AVG8 = AVG8 + Raw8;
   }
    AVG8 = AVG8/20;
    Serial.print("average 8 = " );
    Serial.println(AVG8);
}

void Hydrostatic9(void)
{
  for(int k=0;k<=20;k++)
  {
    delay(100);
    Raw9 = analogRead(A14);
    //Serial.println("Raw Value9 = " );
    //Serial.println(Raw9);
    AVG9 = AVG9 + Raw9;
   }
    AVG9 = AVG9/20;
    Serial.print("average 9 = " );
    Serial.println(AVG9);
}

/*void Hydrostatic10(void)
{
  for(int k=0;k<=20;k++)
  {
    delay(100);
    Raw10 = analogRead(A9);
    Serial.println("Raw Value10 = " );
    Serial.println(Raw10);
    AVG10 = AVG10 + Raw10;
   }
   AVG10 = AVG10/20;
    Serial.println("average 10 = " );
    Serial.println(AVG10);
    OHTcm10 = AVG10 *0.1 ;//tank height/raw value  
    Serial.println("oht 10 cm is:");
    Serial.println(OHTcm10); 
    Serial.println();
}
void Hydrostatic11(void)
{
  for(int k=0;k<=20;k++)
  {
    delay(100);
    Raw11 = analogRead(A10);
    Serial.println("Raw Value11 = " );
    Serial.println(Raw11);
    AVG11 = AVG11 + Raw11;
    }
    AVG11 = AVG11/20;
    Serial.println("average 11 = " );
    Serial.println(AVG11);

    OHTcm11 = AVG11 *0.1 ;//tank height/raw value  
    Serial.println("oht 11 cm is:");
    Serial.println(OHTcm11); 
    Serial.println();
}
void Hydrostatic12(void)
{
  for(int k=0;k<=20;k++)
  {
    delay(100);
    Raw12 = analogRead(A11);
    Serial.println("Raw Value12 = " );
    Serial.println(Raw12);
    AVG12 = AVG12 + Raw12;
   }
    AVG12 = AVG12/20;
    Serial.println("average 12 = " );
    Serial.println(AVG12);
    OHTcm12 = AVG12 *0.1 ;//tank height/raw value  
    Serial.println("oht 12 cm is:");
    Serial.println(OHTcm12); 
    Serial.println();
}*/
                                                                       //RELAY FUNCTIONS  
void Relay1_ON()
{
    digitalWrite(valve1, HIGH );                                       //VALVE PIN IS HIGH 
    valve1status = 1;                                                  //VALVE1 STATUS VALUE IS 1
    Serial.println("valve1 is on");
}
void Relay1_OFF()
{
    digitalWrite(valve1, LOW);                                      //ALL RELAY FUNCTIONS ARE SIMILAR AS ABOVE MENTIONED
    valve1status = 0;
    Serial.println("valve1 is off");
}

void Relay2_ON()
{
    digitalWrite(valve2, HIGH);
    valve2status = 1;
    Serial.println("valve2 is on");
}
void Relay2_OFF()
{
    digitalWrite(valve2, LOW);
    valve2status = 0;
    Serial.println("valve2 is off");
}

void Relay3_ON()
{
    digitalWrite(valve3, HIGH);
    valve3status = 1;
    Serial.println("valve3 is on");
}
void Relay3_OFF()
{
    digitalWrite(valve3, LOW);
    valve3status = 0;
    Serial.println("valve3 is off");
}

void Relay4_ON()
{
    digitalWrite(valve4, HIGH);
    valve4status = 1;
    Serial.println("valve4 is on");
}
void Relay4_OFF()
{
    digitalWrite(valve4, LOW);
    valve4status = 0;
    Serial.println("valve4 is off");
}

void Relay5_ON()
{
    digitalWrite(valve5, HIGH);
    valve5status = 1;
    Serial.println("valve5 is on");
}
void Relay5_OFF()
{
    digitalWrite(valve5, LOW);
    valve5status = 0;
    Serial.println("valve5 is off");
}

void Relay6_ON()
{
    digitalWrite(valve6, HIGH);
    valve6status = 1;
    Serial.println("valve6 is on");
}
void Relay6_OFF()
{
    digitalWrite(valve6, LOW);
    valve6status = 0;
    Serial.println("valve6 is off");
}

void Relay7_ON()
{
    digitalWrite(valve7, HIGH);
    valve7status = 1;
    Serial.println("valve7 is on");
}
void Relay7_OFF()
{
    digitalWrite(valve7, LOW);
    valve7status = 0;
    Serial.println("valve7 is off");
}

void Relay8_ON()
{
    digitalWrite(valve8, HIGH);
    valve8status = 1;
    Serial.println("valve8 is on");
}
void Relay8_OFF()
{
    digitalWrite(valve8, LOW);
    valve8status = 0;
    Serial.println("valve8 is off");
}

void Relay9_ON()
{
    digitalWrite(valve9, HIGH);
    valve9status = 1;
    Serial.println("valve9 is on");
}
void Relay9_OFF()
{
    digitalWrite(valve9, LOW);
    valve9status = 0;
    Serial.println("valve9 is off");
}

/*void Relay10_ON()
{
    digitalWrite(valve10, HIGH);
    valve10status = 1;
    //lcd.clear();
    //lcd.setCursor(0, 0);
    //lcd.print("v1:ON");
    Serial.println("valve10 is on");
}
void Relay10_OFF()
{
    digitalWrite(valve10, LOW);
    valve10status = 0;
    //lcd.clear();
    //lcd.setCursor(0, 0);
    //lcd.print("v1:OFF");
    Serial.println("valve10 is off");
}

void Relay11_ON()
{
    digitalWrite(valve11, HIGH);
    valve11status = 1;
    //lcd.clear();
    //lcd.setCursor(0, 0);
    //lcd.print("v1:ON");
    Serial.println("valve11 is on");
}
void Relay11_OFF()
{
    digitalWrite(valve11, LOW);
    valve11status = 0;
    //lcd.clear();
    //lcd.setCursor(0, 0);
    //lcd.print("v1:OFF");
    Serial.println("valve11 is off");
}

void Relay12_ON()
{
    digitalWrite(valve12, HIGH);
    valve12status = 1;
    //lcd.clear();
    //lcd.setCursor(0, 0);
    //lcd.print("v1:ON");
    Serial.println("valve12 is on");
}
void Relay12_OFF()
{
    digitalWrite(valve12, LOW);
    valve12status = 0;
    //lcd.clear();
    //lcd.setCursor(0, 0);
    //lcd.print("v1:OFF");
    Serial.println("valve12 is off");
}*/
