//*****************************Water Tank Monitering Sysytem****************************
#include <LCD_I2C.h>
LCD_I2C lcd(0x27, 16, 2);//Default address of most PCF8574 modules, change according

//****************************************
//pin defined for sensor,buzzer,motor pump
//****************************************
const int trigPin = 9;
const int echoPin = 10;
const int buzzer = 4;
const int endled = 3;
const int pump=13;

int ledA=7;
int ledB=12;
int ledC=5;
                                                           
long duration;
int distance;
  
void setup() 
{
//***************************************************
//Read data as Input or Output from Arduino Uno board
//***************************************************  
   pinMode(trigPin, OUTPUT);
   pinMode(echoPin, INPUT); 
   pinMode(ledA,OUTPUT);
   pinMode(ledB,OUTPUT);
   pinMode(ledC,OUTPUT);

   pinMode(buzzer, OUTPUT);
   pinMode(endled, OUTPUT);
   pinMode(pump,OUTPUT);
 Serial.begin(9600); 
 lcd.begin();
 lcd.backlight();
   digitalWrite(buzzer, LOW);
   digitalWrite(pump, LOW);
}
//**************************
//Algorithm to detect Water
//**************************
void loop() {
//digitalWrite(buzzer, LOW);
   digitalWrite(trigPin, LOW);
   delayMicroseconds(2);
   digitalWrite(trigPin, HIGH);
   delayMicroseconds(10);
   digitalWrite(trigPin, LOW);
   digitalWrite(buzzer, HIGH);
   digitalWrite(endled, LOW); 
   digitalWrite(ledA, LOW);
   digitalWrite(ledB, LOW);
   digitalWrite(ledC, LOW);

//************************
//distance calculation
//************************
duration = pulseIn(echoPin, HIGH);
distance= (duration/2)/29.1;
 
if (distance <5)   
{
  digitalWrite(buzzer, LOW);
  digitalWrite(endled, HIGH);
  digitalWrite(ledA, HIGH);
  digitalWrite(ledB, HIGH);
  digitalWrite(ledC, HIGH);
  digitalWrite(pump,HIGH);
  lcd.print("---100 %---");
  lcd.setCursor(3,1);
  lcd.print("FILL"); 
  Serial.print("Capacity of tank has been reached!!");
}
else if(distance>8 && distance<=10){
  digitalWrite(buzzer, HIGH);
  digitalWrite(endled, LOW);
  digitalWrite(ledA, HIGH);
  digitalWrite(ledB, HIGH);
  digitalWrite(ledC, HIGH);
  lcd.print("---80 %---");
  lcd.setCursor(3,1);
  lcd.print("FILL"); 
  Serial.println("Tank is 80% FULL");
}
else if(distance>10 && distance<=15)
{
  digitalWrite(buzzer, HIGH);
  digitalWrite(endled, LOW);
  digitalWrite(ledA, LOW);
  digitalWrite(ledB, HIGH);
  digitalWrite(ledC, HIGH);
  lcd.print("---60 %---");
  lcd.setCursor(3,1);
  lcd.print("FILL"); 
  Serial.println("Tank is 50% FULL");
}
else if(distance>12 && distance<=23)
{
  digitalWrite(buzzer, HIGH);
  digitalWrite(endled, LOW);
  digitalWrite(ledA, LOW);
  digitalWrite(ledB, LOW);
  digitalWrite(ledC, HIGH);
  lcd.print("---20 %---");
  lcd.setCursor(3,1);
  lcd.print("FILL"); 
  Serial.println("Tank is 40% FULL");
}
else if(distance>25)
{
  digitalWrite(buzzer, HIGH);
  digitalWrite(endled, LOW);
  digitalWrite(ledA, LOW);
  digitalWrite(ledB, LOW);
  digitalWrite(ledC, LOW);
  digitalWrite(pump,LOW);
  lcd.setCursor(2,0);
  lcd.print("  Tank is  ");
  lcd.setCursor(3,1);
  lcd.print(" Empty      "); 
  Serial.println("Tank is Filling");
}
//************************************************* 
// Prints the distance on the Serial Monitor/Screen
//*************************************************
Serial.print("Distance: ");
Serial.println(distance);
} 
