#include <SPI.h>  
#include "RF24.h" 

RF24 myRadio (7, 8); 
struct package
{
  int X=512;
  int Y=512;
};

byte addresses[][6] = {"0"}; 
int M_L = 5;
int M_R = 6;



typedef struct package Package;
Package data;

void setup() 
{
  Serial.begin(115200);
  delay(1000);

  myRadio.begin(); 
  myRadio.setChannel(115); 
  myRadio.setPALevel(RF24_PA_MAX);
  myRadio.setDataRate( RF24_250KBPS ) ; 
  myRadio.openReadingPipe(1, addresses[0]);
  myRadio.startListening();
  pinMode(M_L, OUTPUT);
  pinMode(M_R, OUTPUT);
  analogWrite(M_L, 0);
  analogWrite(M_R, 0);
}


void loop()  
{
  if ( myRadio.available()) 
  {
    while (myRadio.available())
    {
      myRadio.read( &data, sizeof(data) );
    }
    Serial.print("X:");
    Serial.print(data.X);
    Serial.print("      Y");
    Serial.println(data.Y);
    int X = data.X;
    int Y = data.Y;
    if(Y<=300)
    {
      int blc_L = map(X,0,1024,0,254) - map(X,0,1024,50,120);
      int blc_R = map(X,0,1024,0,254);
      analogWrite(M_L,blc_L);
      analogWrite(M_R,blc_R);
    }
    else if(Y>300&&Y<700)
    {
      int blc_T = map(X,0,1024,0,254);
      analogWrite(M_L,blc_T);
      analogWrite(M_R,blc_T);
    }
    else
    {
      int blc_L = map(X,0,1024,0,254);
      int blc_R = map(X,0,1024,0,254) - map(X,0,1024,50,120);
      analogWrite(M_L,blc_L);
      analogWrite(M_R,blc_R);
    }
       
  }

}
