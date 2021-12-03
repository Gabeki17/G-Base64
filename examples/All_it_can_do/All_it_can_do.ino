#include <Gbase64.h>

Gbase64 Gbase64;

void setup() 
{
  Serial.begin(57600);
  delay(200);
  Serial.println();

  Serial.print("String to string encode: ");
  Serial.println(Gbase64.Sbe("Teszt"));
  
//---------------------------------------------------------
  Serial.print("String to string decode: ");
  Serial.println(Gbase64.Ski("VGVzenQ="));

//---------------------------------------------------------
  Serial.print("byte to String encode  : ");
  byte be[] = {0x54,0x65,0x73,0x7A,0x74};
  Serial.println(Gbase64.Bbe(be,sizeof(be)));
  
//---------------------------------------------------------
  Serial.print("String to byte decode  : ");
  String bemenet = "VGVzenQ=";                          // Input String
  uint8_t padding = 0;                          
  
  for(uint8_t i=0;i<bemenet.length();i++)               // Define padding 
    {
      if (String(bemenet.charAt(i)) == "=")padding++;
    }
  
  byte ki[bemenet.length()*6/8 - padding];              // create byte array exactly the size we need    
  Gbase64.Bki(bemenet, ki);                             // "ki" is the variable that will be filled up with the resoult. After this command, it will simpley hold it. 

  for(uint8_t i=0;i<bemenet.length()*6/8 - padding;i++) // printing out the resoult as HEX
    {
      Serial.print(ki[i],HEX);
      Serial.print(" ");
    }
  Serial.println();
}

void loop() 
{
 
}
