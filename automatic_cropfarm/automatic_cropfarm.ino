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
RS = 32
RW = -
E = 30
D4 =28
D5 = 26
D6 = 24
D7 = 22
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

int sekDelay = 5;

int menu = 1;

void updateMenu();

char state = 0;

int check = 0;

boolean updateMenuRUN = false;

void setup() {
  Serial.begin(9600);
  pinMode(34,OUTPUT);
  dht.begin();
  lcd.begin(20,4);
  //updateMenu();
}

void loop() {
/*
  if (Serial.available() > 0) {
      state = Serial.read();
      if (state == 'a') {
        //digitalWrite(13, HIGH);
        Serial.print("Down");
        menu++;
        updateMenu();
        delay(100);
        //while (results.value == 0XFF30CF);
      }
      if (state == 'b') {
        //digitalWrite(13, HIGH);
        Serial.print("Up");
        menu--;
        updateMenu();
        delay(100);
        //while (results.value == 0XFF30CF);
      }
      if (state == '0') {
        Serial.print("Select");
        executeAction();
        updateMenu();
        delay(100);
        //while (results.value == 0XFF629D);
    }
  }
*/


  while (check == 0) {
    // Jord-fugtigheds sensor
  value = digitalRead(A0);

  // Hvis jord-fugtigheds sensoren er high
  if (value == HIGH) {
    // Transistoren sættes til high = pumpen kører
    digitalWrite(34,HIGH);
    delay(sekDelay);
    digitalWrite(34,LOW);
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

  if (Serial.available() > 0) {
      state = Serial.read();
      if (state == '1'){
        check++;
        lcd.clear();
        settings();
      }
  }
  }
}

void settings() {
  if (updateMenuRUN == false) {
    updateMenu();
    Serial.print("Settings");
    updateMenuRUN = true;
  }
  
  if (Serial.available() > 0) {
      state = Serial.read();
      if (state == 'a') {
        //digitalWrite(13, HIGH);
        Serial.print("Down");
        menu++;
        updateMenu();
        delay(100);
        //while (results.value == 0XFF30CF);
      }
      if (state == 'b') {
        //digitalWrite(13, HIGH);
        Serial.print("Up");
        menu--;
        updateMenu();
        delay(100);
        //while (results.value == 0XFF30CF);
      }
      if (state == '0') {
        Serial.print("Select");
        executeAction();
        updateMenu();
        delay(100);
        //while (results.value == 0XFF629D);
    }
  }
}


void updateMenu() {
  switch (menu) {
    case 0:
      menu = 1;
      break;
    case 1:
      lcd.clear();
      lcd.print(">MenuItem1");
      lcd.setCursor(0, 1);
      lcd.print(" MenuItem2");
      break;
    case 2:
      lcd.clear();
      lcd.print(" MenuItem1");
      lcd.setCursor(0, 1);
      lcd.print(">MenuItem2");
      break;
    case 3:
      lcd.clear();
      lcd.print(">MenuItem3");
      lcd.setCursor(0, 1);
      lcd.print(" MenuItem4");
      break;
    case 4:
      lcd.clear();
      lcd.print(" MenuItem3");
      lcd.setCursor(0, 1);
      lcd.print(">MenuItem4");
      break;
    case 5:
      menu = 4;
      break;
  }
}

void executeAction() {
  switch (menu) {
    case 1:
      action1();
      break;
    case 2:
      action2();
      break;
    case 3:
      action3();
      break;
    case 4:
      action4();
      break;
  }
}

void action1() {
  lcd.clear();
  lcd.print(">Executing #1");
  delay(1500);
}
void action2() {
  lcd.clear();
  lcd.print(">Executing #2");
  delay(1500);
}
void action3() {
  lcd.clear();
  lcd.print(">Executing #3");
  delay(1500);
}
void action4() {
  lcd.clear();
  lcd.print(">Executing #4");
  delay(1500);
}