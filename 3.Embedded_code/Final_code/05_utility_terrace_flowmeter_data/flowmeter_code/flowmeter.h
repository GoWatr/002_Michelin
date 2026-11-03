#include <SoftwareSerial.h>                                                         //software serial library included to set tx,rx pins  
const byte requestframe[] = {0x01, 0x03, 0x00, 0x00, 0x00, 0x21, 0x85, 0xD2};       //assigning request frame values

SoftwareSerial mod(17, 23); // RX, TX ( Creates a new SoftwareSerial object )       //assigning pins for flowmeter
int V8_BIT_1, V8_2BIT_1, V8_2BIT_1_1 = 0;
int V8_BIT_2, V8_2BIT_2 = 0;
int V8_BIT_3 = 0;
uint64_t V16_BIT, V16_BIT1 = 0;
float Flow, Flow1 = 0.0;

String Tot;
int tot=0;
uint8_t values[33];

void MODBUS() 
{                                                                                        //clearing the buffers
  memset(values,0,sizeof(values));
  delay(1000);
  if (mod.write(requestframe, sizeof(requestframe)) == 8)                                //first request frame will be given as input to flowmeter 
  {
    delay(1000);
    for (uint8_t i = 0; i <32; i++) 
    {                                                                                    //response from flowmeter will be read here
      values[i] = mod.read();
      delay(50);
    }

    for (uint8_t i = 0; i < 33; i++) {
      Serial.print(values[i], HEX);
      Serial.print(' ');
    }    
    if ((values[0] == 1) && (values[1] == 3)) {
    //FLOW
    V8_2BIT_1 = (values[5] << 8) | values[6]; // This line has to be implemented for concatenation. (Bitwise operation)
    V8_2BIT_1_1 = (values[11] << 8) | values[12]; // This line has to be implemented for concatenation. (Bitwise operation)
    
    //Tot
    V8_BIT_1 = (values[19] << 8) | values[20]; // This line has to be implemented for concatenation. (Bitwise operation)   
    V8_BIT_2 = (values[21] << 8) | values[22]; // This line has to be implemented for concatenation. (Bitwise operation)
    V16_BIT = static_cast<uint64_t>(V8_BIT_1) << 16 | V8_BIT_2; // This line has to be implemented for concatenation. (Bitwise operation)
    V8_BIT_3 = (values[23] << 8) | values[24]; // This line has to be implemented for concatenation. (Bitwise operation)

    //final 
    //Flow = static_cast<float>(V16_BIT1) * 0.001;
    Flow = V8_2BIT_1 * 0.001;
    Tot =String (String(static_cast<uint32_t>(V16_BIT)) + "." + String(V8_BIT_3));
   
    Serial.println("");
    Serial.println("Flow ="+String(Flow));
    Serial.println("Tot  ="+String(Tot));
    } else if ((values[1] == 1) && (values[2] == 3)) {
    //FLOW
    V8_2BIT_1 = (values[6] << 8) | values[7]; // This line has to be implemented for concatenation. (Bitwise operation)
    V8_2BIT_1_1 = (values[12] << 8) | values[13]; // This line has to be implemented for concatenation. (Bitwise operation)
    
    //Tot
    V8_BIT_1 = (values[20] << 8) | values[21]; // This line has to be implemented for concatenation. (Bitwise operation)   
    V8_BIT_2 = (values[22] << 8) | values[23]; // This line has to be implemented for concatenation. (Bitwise operation)
    V16_BIT = static_cast<uint64_t>(V8_BIT_1) << 16 | V8_BIT_2; // This line has to be implemented for concatenation. (Bitwise operation)
    V8_BIT_3 = (values[24] << 8) | values[25]; // This line has to be implemented for concatenation. (Bitwise operation)

    //final 
    //Flow = static_cast<float>(V16_BIT1) * 0.001;
    Flow = V8_2BIT_1 * 0.001;
    Tot =String (String(static_cast<uint32_t>(V16_BIT)) + "." + String(V8_BIT_3));
   
    Serial.println("");
    Serial.println("Flow ="+String(Flow));
    Serial.println("Tot  ="+String(Tot));
    } else if ((values[2] == 1) && (values[3] == 3)) {
    //FLOW
    V8_2BIT_1 = (values[7] << 8) | values[8]; // This line has to be implemented for concatenation. (Bitwise operation)
    V8_2BIT_1_1 = (values[13] << 8) | values[14]; // This line has to be implemented for concatenation. (Bitwise operation)
    
    //Tot
    V8_BIT_1 = (values[21] << 8) | values[22]; // This line has to be implemented for concatenation. (Bitwise operation)   
    V8_BIT_2 = (values[23] << 8) | values[24]; // This line has to be implemented for concatenation. (Bitwise operation)
    V16_BIT = static_cast<uint64_t>(V8_BIT_1) << 16 | V8_BIT_2; // This line has to be implemented for concatenation. (Bitwise operation)
    V8_BIT_3 = (values[25] << 8) | values[26]; // This line has to be implemented for concatenation. (Bitwise operation)

    //final 
    //Flow = static_cast<float>(V16_BIT1) * 0.001;
    Flow = V8_2BIT_1 * 0.001;
    Tot =String (String(static_cast<uint32_t>(V16_BIT)) + "." + String(V8_BIT_3));
   
    Serial.println("");
    Serial.println("Flow ="+String(Flow));
    Serial.println("Tot  ="+String(Tot));
    }
                                                        
    Serial.println(' ');
  }
}
