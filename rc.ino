//RC CAR ARDUINO CODE: integrating bluetooth module HC-05 with motors to run an RC car using an android app on a mobile device
int leftMotorPin1 = 5;  // IN1 for left motor
int leftMotorPin2 = 6;  // IN2 for left motor
int rightMotorPin1 = 9; // IN1 for right motor
int rightMotorPin2 = 10; // IN2 for right motor

int leftMotorEnable = 3;  // ENA for left motor (PWM)
int rightMotorEnable = 11; // ENB for right motor (PWM)

int x;
int y;

void setup()
{
  pinMode(leftMotorPin1, OUTPUT);
  pinMode(leftMotorPin2, OUTPUT);
  pinMode(rightMotorPin1, OUTPUT);
  pinMode(rightMotorPin2, OUTPUT);
  pinMode(leftMotorEnable, OUTPUT);
  pinMode(rightMotorEnable, OUTPUT);
  Serial.begin(9600); 
}

void loop() 
{

 if (Serial.available())
 {
   char placeholder  = Serial.read();  //find x and y of analog stick

   int ny = map(y,0,260 ,-255, 255);

   int nx = map(x, 0 , 260 ,-255, 255);
  
   int leftv= constrain(ny + nx , -255, 255);
   int rightv= constrain(ny - nx, -255, 255);

   if (leftv > 0 ){
     analogWrite(leftMotorEnable, leftv);
     digitalWrite(leftMotorPin1, HIGH);
     digitalWrite(leftMotorPin2, LOW);
   }
   else if (leftv < 0 ){
     analogWrite(leftMotorEnable, -leftv);
     digitalWrite(leftMotorPin1, LOW);
     digitalWrite(leftMotorPin2, HIGH);
   }
   else
   {
     analogWrite(leftMotorEnable, 0);
   }

   if (rightv > 0 ){
     analogWrite(rightMotorEnable, rightv);
     digitalWrite(rightMotorPin1, HIGH);
     digitalWrite(rightMotorPin2, LOW);
   }
   else if (rightv < 0 ){
     analogWrite(rightMotorEnable, -tightv);
     digitalWrite(rightMotorPin1, LOW);
     digitalWrite(rightMotorPin2, HIGH);
   }
   else
   {
     analogWrite(rightMotorEnable, 0);
   }
 }
