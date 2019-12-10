//te

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
RS = 7
RW = -
E = 6
D4 = 5
D5 = 4
D6 = 3
D7 = 2
A = +
K = -

Potentiometer
Venste = +

*/
// Henter bibloteket LiquidCrystal som bruges til lcd skærmen og så hvilke pins ledninger sider i
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

DHT dht(A1,DHT11);


int sensor = A0;
int light = 12;
int value;
int temp = A1;
#define SensorPin A0 
float sensorValue = A0; 

void setup() {
  pinMode(22,INPUT);
  pinMode(12,OUTPUT);
  Serial.begin(9600);
  dht.begin();
  lcd.begin(20,4);
}

void loop() {
  /*
  value = digitalRead(A0);
  
  if (value == LOW) {
    digitalWrite(12,HIGH);
    Serial.print("HØJ");
  }
  else
  {
    digitalWrite(12,LOW); //if soil moisture sensor provides HIGH value send HIGH value to relay
    Serial.print("LAV");
  }
  */
  
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