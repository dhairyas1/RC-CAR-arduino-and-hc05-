#include <SoftwareSerial.h>
SoftwareSerial BTSerial(10, 11);  // RX | TX (Connect HC-05 TX to Pin 10, HC-05 RX to Pin 11)

int leftMotorPin1 = 8;  // IN1 for left motor
int leftMotorPin2 = 7;  // IN2 for left motor
int rightMotorPin1 = 5; // IN3 for right motor
int rightMotorPin2 = 4; // IN4 for right motor

int leftMotorEnable = 9;  // ENA for left motor (PWM)
int rightMotorEnable = 3; // ENB for right motor (PWM)

String inputX = ""; // To build the X value
String inputY = ""; // To build the Y value
bool readingX = true;

int leftv =0; 
int rightv =0;

void setup() {
  Serial.begin(9600);   // Serial Monitor
  BTSerial.begin(9600); // HC-05
  Serial.println("Bluetooth Ready");
  pinMode(leftMotorPin1, OUTPUT);
  pinMode(leftMotorPin2, OUTPUT);
  pinMode(rightMotorPin1, OUTPUT);
  pinMode(rightMotorPin2, OUTPUT);
  pinMode(leftMotorEnable, OUTPUT);
  pinMode(rightMotorEnable, OUTPUT);
}

void loop() {
  // Check if data is available from the HC-05 Bluetooth module
  while (BTSerial.available()) {
    char c = BTSerial.read(); // Read a single character from Bluetooth
    Serial.print(c);       // Print received character (debugging)
    if(c=='\n')
      {
        readingX = true;
        Serial.println("new");
        break;
      }
    else if(readingX)
      {
        inputX += String(c); //concatinating x input from joystick app.
      }
    else if (!readingX){
        inputY += String(c); //concatenating y input from joystick app.
      }
    else if(c==':') //x axis and y axis coordintes are seperated by colons
      {
        readingX = false;
      }
  }
  //type casting string to integral values
   int x = inputX.toInt(); 
   int y = inputY.toInt();
  //in the case a blank string is converted to int
  if(x==0)
  {
     x = 140; 
  }
  if(y==0)
  {
     y = 140; 
  }
  //mapping values received to the left and right motors
  
   leftv= map(y + x, 436, 124 , -255, 255); 
   rightv= map(y - x,-156 ,156 ,-255, 255);
  //passing the values mapped to motors and ensuring negative values result in the motor running backwards
   if (leftv > 5 ){
     analogWrite(leftMotorEnable, leftv);
     digitalWrite(leftMotorPin1, HIGH);
     digitalWrite(leftMotorPin2, LOW);
   }
   else if (leftv < 5 ){
     analogWrite(leftMotorEnable, -leftv);
     digitalWrite(leftMotorPin1, LOW);
     digitalWrite(leftMotorPin2, HIGH);
   }
   else
   {
     analogWrite(leftMotorEnable, 0);
     digitalWrite(leftMotorPin1, LOW);
     digitalWrite(leftMotorPin2, LOW);

   }

   if (rightv > 10 ){
     analogWrite(rightMotorEnable, rightv);
     digitalWrite(rightMotorPin1, HIGH);
     digitalWrite(rightMotorPin2, LOW);
   }
   else if (rightv < -10 ){
     analogWrite(rightMotorEnable, -rightv);
     digitalWrite(rightMotorPin1, LOW);
     digitalWrite(rightMotorPin2, HIGH);
   }
   else
   {
     analogWrite(rightMotorEnable, 0);
     digitalWrite(leftMotorPin1, LOW);
     digitalWrite(leftMotorPin2, LOW);
   }
//resetting values
  leftv=0;
  rightv=0;
  inputX= "";
  inputY= "";
  delay(50);
}

