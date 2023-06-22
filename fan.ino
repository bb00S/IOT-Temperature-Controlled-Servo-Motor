#include "DHT.h"
#define DHTPIN 2     
#define DHTTYPE DHT11   

DHT dht(DHTPIN, DHTTYPE);
#include <Wire.h>               
#include <LiquidCrystal_I2C.h>  

LiquidCrystal_I2C lcd(0x27,16,2);

// Include the Servo library 
#include <Servo.h> 
int servoPin = 3; 
                               
Servo Servo1; 
   

void setup() {
  lcd.init();  
  lcd.backlight();                

  dht.begin();
  
  
   Servo1.attach(servoPin); 
}

void loop() {
  delay(2000);
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  float f = dht.readTemperature(true);
  float hif = dht.computeHeatIndex(f, h);
  float hic = dht.computeHeatIndex(t, h, false);
  float tempMin = 30.00;   // startna temperatura 
  float tempMax = 50.00; 

   if(t  < tempMin) { // ako je temp manja od minimuma
      Servo1.write(0); ; // ventilator ne radi 
      delay(1000);
   }
   else if((t  >= tempMin) && (t <= tempMax)) { // if temperature is higher than minimum temp   
         Servo1.write(0); 
         delay(500); 
         // Servo ide na 90 stepeni 
         Servo1.write(90); 
         delay(500); 
         // Servo ide na 180 stepeni 
         Servo1.write(180); 
         delay(500);
         Servo1.write(0); 
         delay(500); 
         Servo1.write(90); 
         delay(500); 
         Servo1.write(180); 
         delay(500);
         Servo1.write(0); 
         delay(500); 
         Servo1.write(90); 
         delay(500); 
         Servo1.write(180); 
         delay(500); } 
  lcd.setCursor(0,0);            
  lcd.print("Vlaznost:");
  lcd.print(h);
  lcd.setCursor(0,1);
  lcd.print("Temperatura:");
  lcd.print(t);
  lcd.print(" C");
  
}
