//function.h

#include <ArduinoJson.h>
int Raw1,Raw2,Raw3,Raw4,Raw5,Raw6,Raw7,Raw8,Raw9,Raw10,Raw11,Raw12,Counter = 0;
int AVG1,AVG2,AVG3,AVG4,AVG5,AVG6,AVG7,AVG8,AVG9,AVG10,AVG11,AVG12 = 0;
int Per_AVG1,Per_AVG2,Per_AVG3,Per_AVG4,Per_AVG5,Per_AVG6,Per_AVG7,Per_AVG8,Per_AVG9,Per_AVG10,Per_AVG11,Per_AVG12 = 0;
float s1_max = 19, s2_max = 22, s3_max = 18, s4_max = 45, s5_max = 48, s6_max = 47, s7_max = 42, s8_max = 42, s9_max = 45, s10_max = 39, s11_max = 45, s12_max = 83;
int Per1,Per2,Per3,Per4,Per5,Per6,Per7,Per8,Per9,Per10,Per11,Per12 = 0;
int OHTcm1,OHTcm2,OHTcm3,OHTcm4,OHTcm5,OHTcm6,OHTcm7,OHTcm8,OHTcm9,OHTcm10,OHTcm11,OHTcm12 = 0;
int valve1status,valve2status,valve3status,valve4status,valve5status,valve6status,valve7status,valve8status,valve9status,valve10status,valve11status,valve12status = 0;

#define valve1 8                                                       
#define valve2 7
#define valve3 6
#define valve4 9
#define valve5 10
#define valve6 11
#define valve7 14
#define valve8 2 
#define valve9 3 
#define valve10 4 
#define valve11 5
#define valve12 12
#define f = 17;
void Hydrostatic1(void)
{ 
  for(int k=0;k<=20;k++)
  {
    vTaskDelay(100 / portTICK_PERIOD_MS);
    Raw1 = analogRead(A10);
    AVG1 = AVG1 + Raw1;
   }
    AVG1 = AVG1/20;
    Per_AVG1 = ((AVG1/s1_max)*100);
    Serial.print("average ACCT-01 = " );
    Serial.print(AVG1);
    Serial.print("\t percentage ACCT-01 = " );
    Serial.println(Per_AVG1);

}
void Hydrostatic2(void)
{
  for(int k=0;k<=20;k++)
  {
    vTaskDelay(100 / portTICK_PERIOD_MS);
    Raw2 = analogRead(A11);
    AVG2 = AVG2 + Raw2;
   }
    AVG2 = AVG2/20;
    Per_AVG2 = ((AVG2/s2_max)*100);
    Serial.print("average ACCT-02 = " );
    Serial.print(AVG2);
    Serial.print("\t percentage ACCT-02 = " );
    Serial.println(Per_AVG2);
}

void Hydrostatic3(void)
{
  for(int k=0;k<=20;k++)
  {
    vTaskDelay(100 / portTICK_PERIOD_MS);
    Raw3 = analogRead(A14);
    AVG3 = AVG3 + Raw3;
   }
    AVG3 = AVG3/20;
    Per_AVG3=(AVG3/s3_max)*100;
    Serial.print("average ACCT-03 = " );
    Serial.print(AVG3);
    Serial.print("\t Percentage ACCT-03 = " );
    Serial.println(Per_AVG3);
    Serial.println(' ');
}

void Hydrostatic4(void)
{
  for(int k=0;k<=20;k++)
  {
    vTaskDelay(100 / portTICK_PERIOD_MS);
    Raw4 = analogRead(A13);
    AVG4 = AVG4 + Raw4;
    }
    AVG4 = AVG4/20;
    Per_AVG4=(AVG4/s4_max)*100;
    Serial.print("average CHCT-01 = " );
    Serial.print(AVG4);
    Serial.print("\t Percentage CHCT-01 = " );
    Serial.println(Per_AVG4);
    
}

void Hydrostatic5(void)
{
  for(int k=0;k<=20;k++)
  {
    vTaskDelay(100 / portTICK_PERIOD_MS);
    Raw5 = analogRead(A12);
    AVG5 = AVG5 + Raw5;
   }
    AVG5=AVG5/20;
    Per_AVG5=(AVG5/s5_max)*100;
    Serial.print("average CHCT-02 = " );
    Serial.print(AVG5);
    Serial.print("\t Percentage CHCT-02 = " );
    Serial.println(Per_AVG5);
    
}

void Hydrostatic6(void)
{
  for(int k=0;k<=20;k++)
  {
    vTaskDelay(100 / portTICK_PERIOD_MS);
    Raw6 = analogRead(A7);
    AVG6 = AVG6 + Raw6;
    
  }
    AVG6 = AVG6/20;
    Per_AVG6=(AVG6/s6_max)*100;
    Serial.print("average CHCT-03 = " );
    Serial.print(AVG6);
    Serial.print("\t Percentage CHCT-03 = " );
    Serial.println(Per_AVG6);
    
}

void Hydrostatic7(void)
{
  for(int k=0;k<=20;k++)
  {
    vTaskDelay(100 / portTICK_PERIOD_MS);
    Raw7 = analogRead(A6);
    AVG7 = AVG7 + Raw7;
   }
   AVG7 = AVG7/20;
   Per_AVG7=(AVG7/s7_max)*100;
   Serial.print("average CHCT-04 = " );
   Serial.print(AVG7);
    Serial.print("\t Percentage CHCT-04 = " );
    Serial.println(Per_AVG7);
   
}

void Hydrostatic8(void)
{
  for(int k=0;k<=20;k++)
  {
    vTaskDelay(100 / portTICK_PERIOD_MS);
    Raw8 = analogRead(A4);
    AVG8 = AVG8 + Raw8;
   }
    AVG8 = AVG8/20;
    Per_AVG8=(AVG8/s8_max)*100;
    Serial.print("average CHCT-05 = " );
    Serial.print(AVG8);
    Serial.print("\t Percentage CHCT-05 = " );
    Serial.println(Per_AVG8);
}

void Hydrostatic9(void)
{
  for(int k=0;k<=20;k++)
  {
    vTaskDelay(100 / portTICK_PERIOD_MS);
    Raw9 = analogRead(A3);
    AVG9 = AVG9 + Raw9;
   }
    AVG9 = AVG9/20;
    Per_AVG9=(AVG9/s9_max)*100;
    Serial.print("average CHCT-06 = " );
    Serial.print(AVG9);
    Serial.print("\t Percentage CHCT-06 = " );
    Serial.println(Per_AVG9);
    
}

  void Hydrostatic10(void)
{
  for(int k=0;k<=20;k++)
  {
    vTaskDelay(100 / portTICK_PERIOD_MS);
    Raw10 = analogRead(A1);
    AVG10 = AVG10 + Raw10;
   }
    AVG10 = AVG10/20;
    Per_AVG10=(AVG10/s10_max)*100;
    Serial.print("average CHCT-07 = " );
    Serial.print(AVG10);
    Serial.print("\t Percentage CHCT-07 = " );
    Serial.println(Per_AVG10);
}
void Hydrostatic11(void)
{
  for(int k=0;k<=20;k++)
  {
    vTaskDelay(100 / portTICK_PERIOD_MS);
    Raw11 = analogRead(A0);
    AVG11 = AVG11 + Raw11;
    }
    AVG11 = AVG11/20;
    Per_AVG11=(AVG11/s11_max)*100;
    Serial.print("average CHCT-08 = " );
    Serial.print(AVG11);
    Serial.print("\t Percentage CHCT-08 = " );
    Serial.println(Per_AVG11);
}
void Hydrostatic12(void)
{
  for(int k=0;k<=20;k++)
  {
    vTaskDelay(100 / portTICK_PERIOD_MS);
    Raw12 = analogRead(A15);
    AVG12 = AVG12 + Raw12;
   }
    AVG12 = AVG12/20;
    Per_AVG12=(AVG12/s12_max)*100;
    Serial.print("average HDR - T = " );
    Serial.print(AVG12);
    Serial.print("\t Percentage HDR - T = " );
    Serial.println(Per_AVG12);
}
                                                                        
void Relay1_ON()                                                       //RELAY FUNCTIONS 
{
    digitalWrite(valve1, HIGH );
    valve1status = 1;
    Serial.println("valve1 is on");
}
void Relay1_OFF()
{
    digitalWrite(valve1, LOW);
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

void Relay10_ON()
{
    digitalWrite(valve10, HIGH);
    valve10status = 1;
    Serial.println("valve10 is on");
}
void Relay10_OFF()
{
    digitalWrite(valve10, LOW);
    valve10status = 0;
    Serial.println("valve10 is off");
}

void Relay11_ON()
{
    digitalWrite(valve11, HIGH);
    valve11status = 1;
    Serial.println("valve11 is on");
}
void Relay11_OFF()
{
    digitalWrite(valve11, LOW);
    valve11status = 0;
    Serial.println("valve11 is off");
}

void Relay12_ON()
{
    digitalWrite(valve12, HIGH);
    valve12status = 1;
    Serial.println("valve12 is on");
}
void Relay12_OFF()
{
    digitalWrite(valve12, LOW);
    valve12status = 0;
    Serial.println("valve12 is off");
}
