#include <LiquidCrystal.h>
#include<SoftwareSerial.h>
int led = 13;                     //Led (i.e) Cal from Electricity Meter
int relaypin = 7;                  // Relay Control pin
SoftwareSerial s(5,6);             //(rx,tx)
int current = A2;                   //Select the input pin for current sensor
int sensorPin = A1;                  // select the input pin for LDR
const int voltageSensor = A0;       //Voltage sensor    

float vOUT = 0.0;                    //Voltage Sensor Intiation -- Start
float vIN = 0.0;
float R1 = 30000.0;
float R2 = 7500.0;
int value = 0;                        // Voltage Sensor Intiation -- End
int impblink = 0;                       
float unit = 0;                         //Electricity Unit
float rate = 0;                         // Electricity Rate 
int LDRsensorValue = 0;                   // variable to store the value coming from the sensor
float currentaverage = 0;                ////Current sensor 

LiquidCrystal lcd(2, 3, 8, 9, 10, 11);      // put your pin numbers here


void setup()
  {
  Serial.begin(9600);
  s.begin(9600);
  lcd.begin(16, 2); 
  lcd.setCursor(0,0); // put your LCD parameters here
  lcd.print("Unit:");
  lcd.setCursor(0,1);
  lcd.print("Rate:");
  pinMode(led, OUTPUT);
  pinMode(relaypin, OUTPUT);
  }

String str1;
void loop()
{
  digitalWrite(led, HIGH);         // turn on the Led (i.e) Cal from Electricity Meter
  digitalWrite(relaypin, HIGH); 
  float average = 0;
  //average = average + (.0264 * analogRead(A2) -13.51);//for the 5A mode,
  delay(5000); 
  digitalWrite(relaypin, LOW);


  Serial.print("Current :");
  Serial.print(average/1000);
  Serial.println("A");


   if(digitalRead(led == HIGH))      // Measuring Voltage ---Start
   
  {    value = analogRead(voltageSensor);
      vOUT = (value * 5.0) / 1024.0;
      vIN = vOUT / (R2/(R1+R2));
      impblink++;                       //Blink Counter
      Serial.print("Input = ");
      Serial.println(vIN);
      Serial.print("Impblink = " );      //Measuring Voltage ----End
      Serial.println(impblink); 
   }
   
   digitalWrite(led, LOW);
   delay(1000);   

   Serial.println(impblink);
   unit = impblink/3200.0; 
   Serial.print("Unit = ");
   Serial.println(unit, 7);
   //Serial.println(unit);
   //impblink = 0; 

   if(impblink == 3200)
   {
   impblink = 0;  
   }
   
   if (unit <= 100)
    {    Serial.print("Rate =");

    rate = unit * 150; 
    Serial.println(rate, 7);
    }
     else if (unit <=200)
     {
       rate = unit * 200; 
       Serial.print("Rate =");
       Serial.println(rate, 7);
     }

LDRsensorValue = analogRead(sensorPin);
//Serial.print("LDR Value");
//Serial.println(LDRsensorValue);

lcd.setCursor(7, 0); // top right
lcd.print(unit,7);

lcd.setCursor(7, 1); // top right
lcd.print(rate,7);
if(s.available()>0)
{
 str1=String(unit)+(',')+String(rate);
 s.println(str1);
}}
