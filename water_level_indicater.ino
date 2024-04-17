#include <LiquidCrystal.h>
 
#define trigger 10
#define echo 11
#define motor 12
#define buzzer 13
#define actuator 9
#define rain 8
int ph = A0;
int ph_value=0;
 
const int rs = 7, en = 6, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
 
float time=0,distance=0;
int temp=0; 
void setup()
{
 lcd.begin(16,2);
 pinMode(rain,INPUT);
 pinMode(trigger,OUTPUT);
 pinMode(echo,INPUT);
 pinMode(motor, OUTPUT);
 pinMode(buzzer, OUTPUT);
 pinMode(actuator, OUTPUT);
  pinMode(22,OUTPUT) ;
   pinMode(23,OUTPUT) ;
    pinMode(24,OUTPUT) ;
 lcd.print("  Water Level ");
 lcd.setCursor(0,1);
 lcd.print("   Indicator  ");
 delay(500);
 Serial.begin(9600);
}
 
void loop()
{
  digitalWrite (motor,LOW);
  digitalWrite (actuator,LOW);
  int rain_val=digitalRead(rain);
  ph_value=analogRead(ph);
  ph_value=((ph_value*0.0009765625)*100);
 lcd.clear();
 digitalWrite(trigger,LOW);
 delayMicroseconds(2);
 digitalWrite(trigger,HIGH);
 delayMicroseconds(10);
 digitalWrite(trigger,LOW);
 delayMicroseconds(2);
 time=pulseIn(echo,HIGH);
 distance=time*340/20000;
 lcd.clear();
 lcd.print("Water Space In this ");
 lcd.setCursor(0,1);
 lcd.print("Tank is: ");
 lcd.print(distance);
 lcd.print("Cm");
 delay(2000);
 if(distance<12 && temp==0)
 {
     digitalWrite(motor, LOW);
     digitalWrite(buzzer, HIGH);
     //delay(3000);
     lcd.clear();
     lcd.print("Water Tank Full  ");
     lcd.setCursor(0,1);
     lcd.print("Motor Turned OFF");
     delay(2000);
     digitalWrite(buzzer, LOW);
     delay(3000);
     temp=1;
    
   delay(1000);
 }
 
  else if(distance<12 && temp==1)
 {
     digitalWrite(motor, LOW);
     lcd.clear();
     lcd.print("Water Tank Full ");
     lcd.setCursor(0,1);
     lcd.print("Motor Turned OFF");
     delay(500);
 }
 else if(distance>=12 && distance <=30)
 {
  digitalWrite(motor,HIGH);
 }
 
 else if(distance>30)
 {
   
   lcd.clear();
   lcd.print("LOW Water Level");
   lcd.setCursor(0,1);
   lcd.print("Motor Turned ON");
   delay(500);
   digitalWrite(motor, HIGH);
   delay(5000);
   temp=0;
 }
 if(rain_val==1 && distance>12)
 {
  lcd.clear();
  lcd.print("Storing Rain Water " );
  
  delay(100);
  //lcd.clear();
   if(distance>12)
  {
    digitalWrite(actuator,HIGH);
    delay(5000);
  }
  digitalWrite(actuator,LOW);
  delay(100);
 }
 else if((rain_val==1||rain_val==0) && distance<=12)
 {
  digitalWrite(buzzer,HIGH);
  
  digitalWrite(actuator,LOW);
  delay(500);
  digitalWrite(buzzer,LOW);
  digitalWrite(motor,LOW);
 }
 

 if(ph_value>0 && ph_value<8)
 {
   
   
   
       // lcd.clear();
       //lcd.setCursor(0,1);
   lcd.clear();
   lcd.print("PH_Value= ");  
   lcd.print(ph_value);
   lcd.setCursor(0,1);
   lcd.print("PH_Acidic");
   delay(1000);
   digitalWrite(22,HIGH);
    delay(1000);
    digitalWrite(22,LOW);
 }

 else if(ph_value<14&& ph_value>7)
 {
     
      
        //lcd.clear();
         //lcd.setCursor(0,1);
      lcd.clear();
   lcd.print("PH_Value= ");  
   lcd.print(ph_value);
   lcd.setCursor(0,1);
   lcd.print("PH_Basic");
      delay(1000);
      digitalWrite(23,HIGH);
          delay(1000);
    digitalWrite(23,LOW);
      }

       else if(ph_value>14){
      
      
       // lcd.clear();
        //lcd.setCursor(0,1);
      lcd.clear();
   lcd.print("PH_Value= ");  
   lcd.print(ph_value);
   lcd.setCursor(0,1);
   lcd.print("PH_Abnormal");
      delay(1000);
      digitalWrite(24,HIGH);
          delay(1000);
    digitalWrite(24,LOW);
      }
 else
 {
  lcd.clear();
  lcd.print("Problem in PH Sensor");
  digitalWrite(actuator,HIGH);
    digitalWrite(22,HIGH);
       digitalWrite(23,LOW);
  
  }
}