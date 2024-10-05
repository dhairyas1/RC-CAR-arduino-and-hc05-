#include <SoftwareSerial.h>

// Define SoftwareSerial pins for HC-05
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

  if (!BTSerial.available()) {
    analogWrite(leftMotorEnable, 0);
    analogWrite(rightMotorEnable, 0);
  }

  while (BTSerial.available()) {
    char c = BTSerial.read(); // Read a single character from Bluetooth
    //Serial.print(); // Print label
    //Serial.print(c);       // Print received character
    if(readingX){
      if(c==':'){
        readingX=false;
      }else{
        inputX += String(c);
      }
    }else{
      if(c=='\n'){
        break;
      }else{
        inputY += String(c);
      }
    }
  }


  //Serial.println(inputX+inputY);
   int x = inputX.toInt();
   int y = inputY.toInt();

   //int ny = map(y,218, 62 ,-255, 255);

   //int nx = map(x, 62 , 218 ,-255, 255);

  if (y == 0){
    y= 140;
  }
  if (x == 0){
    x= 140;
  }
  
  //  leftv= map(y + x, 436, 124 , -255, 255);
  //  rightv= map(y - x,-156 ,156 ,-255, 255);
  // Serial.println(inputX);
  // Serial.println(inputY);
    y -= 140;
    x -= 140;

    y = map(y, 80 , -80, -255, 255);
    x = map(x, -80 , 80, -255, 255);
   //int ny = map(y,218, 62 ,-255, 255);

   //int nx = map(x, 62 , 218 ,-255, 255);
   
   leftv = constrain(y + x, -255, 255);
   rightv = constrain(y - x, -255, 255);


  if (leftv > 10) { 
    analogWrite(leftMotorEnable, leftv);
    digitalWrite(leftMotorPin1, HIGH);
    digitalWrite(leftMotorPin2, LOW);
  } 
  else if (leftv < -10) { 
    analogWrite(leftMotorEnable, -leftv);
    digitalWrite(leftMotorPin1, LOW);
    digitalWrite(leftMotorPin2, HIGH);
  } 
  else { 
    analogWrite(leftMotorEnable, 0);
    digitalWrite(leftMotorPin1, LOW);
    digitalWrite(leftMotorPin2, LOW);
  }
  if (rightv > 10) { 
    analogWrite(rightMotorEnable, rightv);
    digitalWrite(rightMotorPin1, HIGH);
    digitalWrite(rightMotorPin2, LOW);
  } 
  else if (rightv < -10) { 
    analogWrite(rightMotorEnable, -rightv);
    digitalWrite(rightMotorPin1, LOW);
    digitalWrite(rightMotorPin2, HIGH);
  } 
  else { 
    analogWrite(rightMotorEnable, 0);
    digitalWrite(rightMotorPin1, LOW);
    digitalWrite(rightMotorPin2, LOW);
  }
  leftv=0;
  rightv=0;
  inputX= "";
  inputY= "";
  readingX=true;
  delay(10);
}

