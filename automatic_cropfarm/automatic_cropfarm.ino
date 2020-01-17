#include <Adafruit_Sensor.h>

#include <DHT.h>
#include <DHT_U.h>

#include  <Wire.h> // include wire
#include <LiquidCrystal.h>
#include <Average.h>


// Noter til opbygning
// Skærm
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
LiquidCrystal lcd(32, 30, 28, 26, 24, 22);

//Temeperatur sensor
DHT dht(A1,DHT11);


int value;
int temp = A1;
#define SensorPin A0 
float sensorValue = A0;

int state = 0;


void setup() {
  Serial.begin(38400);
  pinMode(34,OUTPUT);
  dht.begin();
  lcd.begin(20,4);
}

void loop() {

  if (Serial.available() > 0) {
    state = Serial.read();
  }
  // Jord-fugtigheds sensor
  value = digitalRead(A0);

 
  if (state == "0") {
    Serial.println("Sut den");
    state = 0;
  }

  else if (state == "1") {
    Serial.println("hejsa");
  }

  // Hvis jord-fugtigheds sensoren er high
  if (value == HIGH) {
    // Transistoren sættes til high = pumpen kører
    digitalWrite(34,HIGH);
  }

  // Hvis jord-fugtigheds sensoren er low
  if (value == LOW)
  {
    // Transistoren sættes til low = intet vand i pumpen
    digitalWrite(34,LOW);
  }
  
  // Delay som opdatere skærmen
  delay(400);

  // Læser temperaturen i celsius
  float t = dht.readTemperature();
  // læser temeperaturen i Fahrenheit
  float f = dht.readTemperature(true);

  // Tjekker om der er fejl med temeperatur sensoren
  if (isnan(t) || isnan(f)) {
    //Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // Kører 100 målinger
  for (int i = 0; i <= 100; i++) 
 { 
   // 
   sensorValue = sensorValue + analogRead(SensorPin); 
   delay(1); 
 } 
 sensorValue = sensorValue/100.0; 
 //Serial.println(sensorValue); 
 delay(30); 
  
  // Console output

 /* // Temeperatur i celsius og i Fahrenheit
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.print(" *C ");
  Serial.print(f);
  Serial.print(" *F\t");
*/
  // Lcd skærm output

  // Sætter cursoren i 0,1
  lcd.setCursor(0,1); 
  // Printer temperaturen i celsius og Fahrenheit
  lcd.print("Temp: ");
  lcd.print(t);
  lcd.print((char)223);
  lcd.print("C ");
  lcd.print(f);
  lcd.print("F");

  // Sætter cursoren i 0,2
  lcd.setCursor(0,2);

  // Printer Jord fugtigheden
  lcd.print("Fugtighed: ");
  lcd.print(sensorValue);
  lcd.print("");
}