#include <SPI.h>  
#include "RF24.h"

RF24 myRadio (7, 8);
byte addresses[][6] = {"0"};

struct package
{
  int X=1;
  int Y=1;
};


typedef struct package Package;
Package data;


void setup()
{
  Serial.begin(115200);
  delay(150);
  myRadio.begin();  
  myRadio.setChannel(115); 
  myRadio.setPALevel(RF24_PA_MIN);
  myRadio.setDataRate( RF24_250KBPS ) ; 
  myRadio.openWritingPipe( addresses[0]);
  delay(100);
}

void loop()
{
   myRadio.write(&data, sizeof(data)); 

  Serial.print("X:");
  Serial.print(data.X);
  Serial.print("    Y");
  Serial.println(data.Y);
  data.X = analogRead(A0);
  data.Y = analogRead(A1);
  delay(80);
}
