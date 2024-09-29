//RC CAR ARDUINO CODE: inmtegrating bluetooth module HC-05 with motors to run an RC car usign an adroid app on a mobile device
#include<SoftwareSerial.h>

SoftwareSerial blue(2,3); //RX , TX ( If 0,1 pins don't work.)

int mleft = 6;
int mright= 10;
int diff =0;

void setup()
{
  Serial.begin(9600); 
  blue.begin(9600);
}

void loop() 
{

 if (Serial.available())
 {
   char input = Serial.read();
   if (isDigit(input))
   {
     diff = map(input , 0 ,100 , 0, 225);
   }

   else if (input == "f")
   {
     analogWrite(mleft,225);
     analogWrite(mright,225);
   }

   else if (input== "r")
   {
     analogWrite(mleft,diff);
     analogWrite(mright, 225 - diff);
   }

   else if(input == "l")
   {
     analogWrite(mright,diff);
     analogWrite(mleft, 225 - diff);
   }

   else if(input == "b")
   {
     analogWrite(mright, 0);
     analogWrite(mleft, 0);
   }

 }
