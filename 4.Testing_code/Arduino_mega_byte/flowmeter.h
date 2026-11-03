#include <SoftwareSerial.h>                                                         //software serial library included to set tx,rx pins  
const byte requestframe[] = {0x01, 0x03, 0x00, 0x00, 0x00, 0x021, 0x85, 0xD2};       //assigning request frame values

SoftwareSerial mod(A9, A8); // RX, TX ( Creates a new SoftwareSerial object )       //assigning pins for flowmeter
//char buf0[4], buf1[4], buf2[4];                                                     //char buffer initializing
int V8_BIT_1, V8_2BIT_1 = 0;
int V8_BIT_2, V8_2BIT_2 = 0;
int V8_BIT_3 = 0;
uint64_t V16_BIT, V16_BIT1 = 0;
float Flow = 0.0;
String Tot;
int tot=0;
//byte myHex[18];
//byte values[18];// 17
byte myHex[33];
byte values[33];

void MODBUS() 
{                                                                                         //modbus function to read the flowmeter value 
  memset(myHex,0,sizeof(myHex));                                                            //clearing the buffers
  memset(values,0,sizeof(values));
  //memset(buf2,0,sizeof(buf2));
  if (mod.write(requestframe, sizeof(requestframe)) == 8)                                //first request frame will be given as input to flowmeter 
  {
    for (byte i = 0; i <33; i++) 
    {                                                                                    //response from flowmeter will be read here
      values[i] = mod.read();
      myHex[i] = values[i];
      delay(10);
    }
    //FLOW
    V8_2BIT_1 = (values[10] << 8) | values[11]; // This line has to be implemented for concatenation. (Bitwise operation)
    Serial.print("The 8_2BIT_1 SOLVED RESULT is "); 
    Serial.println(V8_2BIT_1);
    delay(500);
    /*V8_2BIT_2 = (values[4] << 8) | values[5]; // This line has to be implemented for concatenation. (Bitwise operation)
    Serial.print("The 8_2BIT_2 SOLVED RESULT is "); 
    Serial.println(V8_2BIT_2);
    delay(500);
    V16_BIT1 = static_cast<uint64_t>(V8_2BIT_1) << 16 | V8_2BIT_2; // This line has to be implemented for concatenation. (Bitwise operation)
    Serial.print("The 16_BIT SOLVED RESULT is *********** "); 
    Serial.println(static_cast<uint32_t>(V16_BIT1));
    delay(500);*/
    
    //Tot
    V8_BIT_1 = (values[18] << 8) | values[19]; // This line has to be implemented for concatenation. (Bitwise operation)
    Serial.print("The 8_BIT_1 SOLVED RESULT is "); 
    Serial.println(V8_BIT_1);
    delay(500);
    V8_BIT_2 = (values[20] << 8) | values[21]; // This line has to be implemented for concatenation. (Bitwise operation)
    Serial.print("The 8_BIT_2 SOLVED RESULT is "); 
    Serial.println(V8_BIT_2);
    delay(500);
    V16_BIT = static_cast<uint64_t>(V8_BIT_1) << 16 | V8_BIT_2; // This line has to be implemented for concatenation. (Bitwise operation)
    Serial.print("The 16_BIT SOLVED RESULT is *********** "); 
    Serial.println(static_cast<uint32_t>(V16_BIT));
    delay(500);
    V8_BIT_3 = (values[22] << 8) | values[23]; // This line has to be implemented for concatenation. (Bitwise operation)
    Serial.print("The 8_BIT_3 SOLVED RESULT is "); 
    Serial.println(V8_BIT_3);

    //final 
    //Flow = static_cast<float>(V16_BIT1) * 0.001;
    Flow = V8_2BIT_1 * 0.001;
    //Tot =String (String(static_cast<uint32_t>(V16_BIT)) + "." + String(V8_BIT_3));
    Tot =String (String(static_cast<uint32_t>(V16_BIT)));
    Tot = Tot+"."+V8_BIT_3;
    Serial.println("");
    Serial.println("Flow ="+String(Flow));
    Serial.println("Tot  ="+String(Tot));
    Serial.println("");

    ////////////////////////////////////////////////////////
    //for accumax flowmeter
    /*buf0[0] = myHex[7]; buf0[1] = myHex[6]; buf0[2] = myHex[5]; buf0[3] = myHex[4];         //datas from flowmeter will be stored in buffer 
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
    Serial.println("TOTALAIZER = "+String(Tot));*/
    ////////////////////////////////////////////////////////////////
    Serial.print(values[0], HEX);                                                         
    Serial.print(' ');
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
    Serial.print(' ');
    Serial.print(values[18], HEX);                                                         
    Serial.print(' ');
    Serial.print(values[19], HEX);                                                         
    Serial.print(' ');
    Serial.print(values[20], HEX);                                                         
    Serial.print(' ');
    Serial.print(values[21], HEX);                                                         
    Serial.print(' ');
    Serial.print(values[22], HEX);                                                         
    Serial.print(' ');
    Serial.print(values[23], HEX);                                                         
    Serial.print(' ');
    Serial.print(values[24], HEX);                                                         
    Serial.print(' ');
    Serial.print(values[25], HEX);                                                         
    Serial.print(' ');
    Serial.print(values[26], HEX);                                                         
    Serial.print(' ');
    Serial.print(values[27], HEX);                                                         
    Serial.print(' ');
    Serial.print(values[28], HEX);                                                         
    Serial.print(' ');
    Serial.print(values[29], HEX);                                                         
    Serial.print(' ');
    Serial.print(values[30], HEX);                                                         
    Serial.print(' ');
    Serial.print(values[31], HEX);                                                         
    Serial.print(' ');
    Serial.print(values[32], HEX);                                                         
    Serial.println(' ');
  }
}
