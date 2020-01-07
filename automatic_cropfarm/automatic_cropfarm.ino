#include <Adafruit_Sensor.h>

#include <DHT.h>
#include <DHT_U.h>

#include  <Wire.h> // include wire
#include <LiquidCrystal.h>
#include <Average.h>
//Noter til opbygning
//Skærm
/*
VSS = Højre på Potentiometer
VDD = +
V0 = Midte på Potentiometer
RS = 22
RW = -
E = 24
D4 = 26
D5 = 28
D6 = 30
D7 = 32
A = +
K = -

Potentiometer
Venste = +

*/
// Henter bibloteket LiquidCrystal som bruges til lcd skærmen og så hvilke pins ledninger sider i
LiquidCrystal lcd(22, 24, 26, 28, 30, 32);

DHT dht(A1,DHT11);


int value;
int temp = A1;
#define SensorPin A0 
float sensorValue = A0; 

void setup() {
  Serial.begin(9600);
  pinMode(34,OUTPUT);
  dht.begin();
  lcd.begin(20,4);
}

void loop() {
  value = digitalRead(A0);
  
  if (value == LOW) {
    digitalWrite(34,LOW);
    Serial.print("HØJ");
  }
  else
  {
    digitalWrite(34,HIGH); //if soil moisture sensor provides HIGH value send HIGH value to relay
    Serial.print("LAV");
  }
  
  delay(400);
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(t) || isnan(f)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  for (int i = 0; i <= 100; i++) 
 { 
   sensorValue = sensorValue + analogRead(SensorPin); 
   delay(1); 
 } 
 sensorValue = sensorValue/100.0; 
 Serial.println(sensorValue); 
 delay(30); 
  
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.print(" *C ");
  Serial.print(f);
  Serial.print(" *F\t");
  lcd.setCursor(0,1); 
  lcd.print("Temp: ");
  lcd.print(t);
  lcd.print((char)223);
  lcd.print("C ");
  lcd.print(f);
  lcd.print("F");
  lcd.setCursor(0,2);
  lcd.print("Humidity: ");
  lcd.print(sensorValue);
  lcd.print("");
}