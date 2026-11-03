#include <SoftwareSerial.h>                                                         //software serial library included to set tx,rx pins  
const byte requestframe[] = {0x01, 0x03, 0x00, 0x00, 0x00, 0x21, 0x85, 0xD2};       //assigning request frame values

SoftwareSerial mod(A9, A8); // RX, TX ( Creates a new SoftwareSerial object )       //assigning pins for flowmeter
int V8_BIT_1, V8_2BIT_1 = 0;
int V8_BIT_2, V8_2BIT_2 = 0;
int V8_BIT_3 = 0;
uint64_t V16_BIT, V16_BIT1 = 0;
float Flow = 0.0;
String Tot;
int tot=0;
uint8_t values[33];

void MODBUS() 
{                                                                                        //clearing the buffers
  memset(values,0,sizeof(values));
  if (mod.write(requestframe, sizeof(requestframe)) == 8)                                //first request frame will be given as input to flowmeter 
  {
    for (uint8_t i = 0; i <33; i++) 
    {                                                                                    //response from flowmeter will be read here
      values[i] = mod.read();
      delay(10);
    }
    //FLOW
    V8_2BIT_1 = (values[10] << 8) | values[11]; // This line has to be implemented for concatenation. (Bitwise operation)
    Serial.print("The 8_2BIT_1 SOLVED RESULT is "); 
    Serial.println(V8_2BIT_1);
    
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
    
    V8_BIT_2 = (values[20] << 8) | values[21]; // This line has to be implemented for concatenation. (Bitwise operation)
    Serial.print("The 8_BIT_2 SOLVED RESULT is "); 
    Serial.println(V8_BIT_2);
    
    V16_BIT = static_cast<uint64_t>(V8_BIT_1) << 16 | V8_BIT_2; // This line has to be implemented for concatenation. (Bitwise operation)
    Serial.print("The 16_BIT SOLVED RESULT is *********** "); 
    Serial.println(static_cast<uint32_t>(V16_BIT));
    
    V8_BIT_3 = (values[22] << 8) | values[23]; // This line has to be implemented for concatenation. (Bitwise operation)
    Serial.print("The 8_BIT_3 SOLVED RESULT is "); 
    Serial.println(V8_BIT_3);

    //final 
    //Flow = static_cast<float>(V16_BIT1) * 0.001;
    Flow = V8_2BIT_1 * 0.001;
    Tot =String (String(static_cast<uint32_t>(V16_BIT)) + "." + String(V8_BIT_3));
   
    Serial.println("");
    Serial.println("Flow ="+String(Flow));
    Serial.println("Tot  ="+String(Tot));
    Serial.println("");

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

    delay(30);
    mod.flush();
    delay(30);
  }
}
