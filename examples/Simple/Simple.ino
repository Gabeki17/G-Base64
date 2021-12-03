#include <Gbase64.h>

Gbase64 Gbase64;

void setup() 
{
  Serial.begin(57600);
  delay(200);
  Serial.println();


  Serial.print("String to string encode: ");
  Serial.println(Gbase64.Sbe("Teszt"));
  
  Serial.print("String to string decode: ");
  Serial.println(Gbase64.Ski("VGVzenQ="));
}

void loop() 
{
 
}
