#include <Arduino.h>
#include "Gbase64.h"

const char PROGMEM B64[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";


String Gbase64::Sbe(String input)
  {
	byte input_b[input.length()];
	uint8_t padding;
    byte atalakit_6[(input.length()*8)/6];
    uint16_t z = 0;
	String bekodolva;
  
  input.getBytes(input_b, input.length() + 1);
  
    for (uint16_t i =0;i<(input.length()*8)/6;i=i+3)
      {
        if(z<=(input.length()*8)/6) atalakit_6[z] = input_b[i] >> 2;
        if(z+1<=(input.length()*8)/6) atalakit_6[z+1] = ((input_b[i] - (atalakit_6[z] << 2)) << 4) + (input_b[i+1] >> 4);
        if(z+2<=(input.length()*8)/6) atalakit_6[z+2] = ((input_b[i+1] - ((input_b[i+1] >> 4) << 4)) << 2) + (input_b[i+2] >> 6);
        if(z+3<=(input.length()*8)/6) atalakit_6[z+3] = input_b[i+2] - ((input_b[i+2] >> 6) << 6);
      
        z=z+4;
        delay(0);
      }

    if (((input.length()*8)/6)*6 < input.length()*8) {padding = 6 - (input.length()*8 - ((input.length()*8)/6)*6);}

    for (uint16_t i=0;i<=(input.length()*8)/6;i++)
      {
        delay(0);
        bekodolva+=char(pgm_read_byte(B64 + atalakit_6[i]));
      }

    if ((bekodolva.length() / 4) * 4 < bekodolva.length() )
      {
        uint8_t p = 4 - (bekodolva.length() - (bekodolva.length() / 4) * 4);
        for (uint8_t i=0;i<p;i++)
          {
            bekodolva += "=";
          }
      }
	return bekodolva;
  }

String Gbase64::Bbe(byte *input_b,uint16_t hossz)
  {
	uint8_t padding;
    byte atalakit_6[(hossz*8)/6];
    uint16_t z = 0;
	String bekodolva;
  
    for (uint16_t i =0;i<(hossz*8)/6;i=i+3)
      {
        if(z<=(hossz*8)/6) atalakit_6[z] = input_b[i] >> 2;
        if(z+1<=(hossz*8)/6) atalakit_6[z+1] = ((input_b[i] - (atalakit_6[z] << 2)) << 4) + (input_b[i+1] >> 4);
        if(z+2<=(hossz*8)/6) atalakit_6[z+2] = ((input_b[i+1] - ((input_b[i+1] >> 4) << 4)) << 2) + (input_b[i+2] >> 6);
        if(z+3<=(hossz*8)/6) atalakit_6[z+3] = input_b[i+2] - ((input_b[i+2] >> 6) << 6);
      
        z=z+4;
        delay(0);
      }

    if (((hossz*8)/6)*6 < hossz*8) {padding = 6 - (hossz*8 - ((hossz*8)/6)*6);}

    for (uint16_t i=0;i<=(hossz*8)/6;i++)
      {
        delay(0);
        bekodolva+=char(pgm_read_byte(B64 + atalakit_6[i]));
      }

    if ((bekodolva.length() / 4) * 4 < bekodolva.length() )
      {
        uint8_t p = 4 - (bekodolva.length() - (bekodolva.length() / 4) * 4);
        for (uint8_t i=0;i<p;i++)
          {
            bekodolva += "=";
          }
      }
	return bekodolva;
  }

String Gbase64::Ski(String kikodol)
  {
	char todec[kikodol.length()];
	byte visszaalakit_6[kikodol.length()];
	uint8_t padding_v = 0;
	uint16_t counter = 0;
	String visszateres;

  kikodol.toCharArray(todec, kikodol.length()+1);

  for (uint16_t i=0;i<=kikodol.length();i++)
    {
      for (uint8_t j=0;j<64;j++)
        {
          if ( char(pgm_read_byte(B64 + j)) == todec[i] )
            {
              visszaalakit_6[i] = j;
              break; 
            }
          else if ( todec[i] == 61)    // 61 az egyenlőségjel ASCII kódja (=)
            {
              padding_v++;
              break;
            }
          delay(0);
        }
      
    }

  for(uint16_t i=0;i<kikodol.length();i=i+4)
    {
      if (counter   < (kikodol.length() * 6) /8 - padding_v) visszaalakit_6[counter]     = (visszaalakit_6[i] << 2) + (visszaalakit_6[i+1] >> 4);
      if (counter+1 < (kikodol.length() * 6) /8 - padding_v) visszaalakit_6[counter + 1] = ((visszaalakit_6[i+1] - ((visszaalakit_6[i+1] >> 4) << 4)) << 4) + (visszaalakit_6[i+2] >> 2);
      if (counter+2 < (kikodol.length() * 6) /8 - padding_v) visszaalakit_6[counter + 2] = ((visszaalakit_6[i+2] - ((visszaalakit_6[i+2] >> 2) << 2)) << 6) + visszaalakit_6[i+3];
 
      counter = counter + 3;
      delay(0);
    }

  
  for (uint16_t i = 0 ; i < (kikodol.length() * 6) /8 - padding_v; i++)
    {
      visszateres += char(visszaalakit_6[i]);
	  delay(0);
    }
    return visszateres;
  }
  
void Gbase64::Bki(String kikodol, byte *vissza)
  {
	char todec[kikodol.length()];
	byte visszaalakit_6[kikodol.length()];
	uint8_t padding_v = 0;
	uint16_t counter = 0;

  kikodol.toCharArray(todec, kikodol.length()+1);

  for (uint16_t i=0;i<=kikodol.length();i++)
    {
      for (uint8_t j=0;j<64;j++)
        {
          if ( char(pgm_read_byte(B64 + j)) == todec[i] )
            {
              visszaalakit_6[i] = j;
              break; 
            }
          else if ( todec[i] == 61)    // 61 az egyenlőségjel ASCII kódja (=)
            {
              padding_v++;
              break;
            }
          delay(0);
        }
      
    }

  for(uint16_t i=0;i<kikodol.length();i=i+4)
    {
      if (counter   < (kikodol.length() * 6) /8 - padding_v) visszaalakit_6[counter]     = (visszaalakit_6[i] << 2) + (visszaalakit_6[i+1] >> 4);
      if (counter+1 < (kikodol.length() * 6) /8 - padding_v) visszaalakit_6[counter + 1] = ((visszaalakit_6[i+1] - ((visszaalakit_6[i+1] >> 4) << 4)) << 4) + (visszaalakit_6[i+2] >> 2);
      if (counter+2 < (kikodol.length() * 6) /8 - padding_v) visszaalakit_6[counter + 2] = ((visszaalakit_6[i+2] - ((visszaalakit_6[i+2] >> 2) << 2)) << 6) + visszaalakit_6[i+3];
 
      counter = counter + 3;
      delay(0);
    }

  
  for (uint16_t i = 0 ; i < (kikodol.length() * 6) /8 - padding_v; i++)
    {
	  vissza[i] = visszaalakit_6[i];
	  delay(0);
    }
  }