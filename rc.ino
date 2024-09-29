//RC CAR ARDUINO CODE: integrating bluetooth module HC-05 with motors to run an RC car usign an adroid app on a mobile device
int mleft = 6;
int mright= 10;

void setup()
{
  Serial.begin(9600); 
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
