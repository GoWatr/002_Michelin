#include <SoftwareSerial.h>                                                         //software serial library included to set tx,rx pins  
const byte requestframe[] = {0x0A, 0x03, 0x00, 0x00, 0x00, 0x06, 0xC4, 0xB3};       //assigning request frame values

SoftwareSerial mod(A9, A8); // RX, TX ( Creates a new SoftwareSerial object )       //assigning pins for flowmeter
char buf0[4], buf1[4], buf2[4];                                                     //char buffer initializing
float Flow, dataT1, dataT2 ,Tot = 0.0;
byte myHex[18];
byte values[18];// 17

void MODBUS() 
{                                                                                         //modbus function to read the flowmeter value 
  memset(buf0,0,sizeof(buf0));                                                            //clearing the buffers
  memset(buf1,0,sizeof(buf1));
  memset(buf2,0,sizeof(buf2));
  if (mod.write(requestframe, sizeof(requestframe)) == 8)                                //first request frame will be given as input to flowmeter 
  {
    for (byte i = 0; i <18; i++) 
    {                                                                                    //response from flowmeter will be read here
      values[i] = mod.read();
      myHex[i] = values[i];
      delay(10);
    }

    buf0[0] = myHex[7]; buf0[1] = myHex[6]; buf0[2] = myHex[5]; buf0[3] = myHex[4];         //datas from flowmeter will be stored in buffer 
    memcpy((char *)&Flow, buf0, 4);                                                         //in buf0 flow value will be stored
    Serial.print("BUFFER IS" );
    Serial.print(buf0 );
    buf1[0] = myHex[11]; buf1[1] = myHex[10]; buf1[2] = myHex[9]; buf1[3] = myHex[8];   
    memcpy((char *)&dataT1, buf1, 4);                                                       //in buf1 dataT1 will be stored
 
    buf2[0] = myHex[15]; buf2[1] = myHex[14]; buf2[2] = myHex[13]; buf2[3] = myHex[12]; 
    memcpy((char *)&dataT2, buf2, 4);                                                       //in buf2 dataT2 will be stored
    
    Serial.print("dataT1 = ");
    Serial.println(dataT1);
    
    Serial.print("dataT2 = " );
    Serial.println(dataT2);
    Tot = ((65535 * dataT2) + dataT1);                                                   //totalizer formula given in datasheet

    Serial.println(Tot);
    Serial.println("Flow Rate = "+String(Flow));
    Serial.println("TOTALAIZER = "+String(Tot));
    Serial.print(values[1], HEX);                                                         
    Serial.print(' ');
    Serial.print(values[2], HEX);
    Serial.print(' ');
    Serial.print(values[3], HEX);
    Serial.print(' ');
    Serial.print(values[4], HEX);
    Serial.print(' ');
    Serial.print(values[5], HEX);
    Serial.print(' ');
    Serial.print(values[6], HEX);
    Serial.print(' ');
    Serial.print(values[7], HEX);
    Serial.print(' ');
    Serial.print(values[8], HEX);
    Serial.print(' ');
    Serial.print(values[9], HEX);
    Serial.print(' ');
    Serial.print(values[10], HEX);
    Serial.print(' ');
    Serial.print(values[11], HEX);
    Serial.print(' ');
    Serial.print(values[12], HEX);
    Serial.print(' ');
    Serial.print(values[13], HEX);
    Serial.print(' ');
    Serial.print(values[14], HEX);
    Serial.print(' ');
    Serial.print(values[15], HEX);
    Serial.print(' ');
    Serial.print(values[16], HEX);
    Serial.print(' ');
    Serial.print(values[17], HEX);
    Serial.println(' ');
  }
}
