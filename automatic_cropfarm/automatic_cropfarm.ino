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


// Target skærm
int tempTarget = 25;
int humTarget = 700;
int waterTarget = 7;

//------------------

// Actual skærm
int sekDelay = 5;
int humActual = 500;

//------------------

int value;
int temp = A1;
#define SensorPin A0 
float sensorValue = A0;

int menu = 1;

void updateMenu();

char state = 0;

char state2 = 0;

boolean check = false;

boolean updateMenuRUN = false;

boolean he = false;

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
  if (check == false) {
    // Jord-fugtigheds sensor
  value = digitalRead(A0);

  // Hvis jord-fugtigheds sensoren er high
  if (value == HIGH) {
    // Transistoren sættes til high = pumpen kører
    digitalWrite(34,HIGH);
    delay(waterTarget);
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

  
  }
  if (Serial.available() > 0) {
      state = Serial.read();
      if (state == '2'){
        he = false;
        check = true;
        lcd.clear();
        while (he == false) {
          settings();
        }
      }
  }
}

void settings() {
  if (updateMenuRUN == false) {
    updateMenu();
    updateMenuRUN = true;
  }
  if (Serial.available() > 0) {
  state = Serial.read();
    if (state == 'a') {
      //digitalWrite(13, HIGH);
      Serial.println("Down");
      menu++;
      updateMenu();
      delay(100);
      //while (results.value == 0XFF30CF);
    }
    if (state == 'b') {
      //digitalWrite(13, HIGH);
      Serial.println("Up");
      menu--;
      updateMenu();
      delay(100);
      //while (results.value == 0XFF30CF);
    }
    if (state == '0') {
      Serial.println("+");
      executeAction();
      updateMenu();
      delay(100);
      //while (results.value == 0XFF629D);
      }
    if (state == '1') {
      Serial.println("-");
      executeAction2();
      updateMenu();
      delay(100);
      //while (results.value == 0XFF629D);
      }
  }
} 


void updateMenu() {
  if (he == false) {
    switch (menu) {
    case 0:
      menu = 1;
      break;
    case 1:
      lcd.clear();
      lcd.print(">Temp: ");
      lcd.print(dht.readTemperature());
      lcd.print(" ");
      lcd.print(tempTarget);
      lcd.setCursor(0, 1);
      lcd.print(" Humit: ");
      lcd.print(sensorValue);
      lcd.print(" ");
      lcd.print(humTarget);
      lcd.setCursor(0, 2);
      lcd.print(" WaterC: ");
      lcd.print(sekDelay);
      lcd.print(" ");
      lcd.print(waterTarget);
      lcd.setCursor(0, 3);
      lcd.print(" Quit");
      break;
    case 2:
      lcd.clear();
      lcd.print(" Temp: ");
      lcd.print(dht.readTemperature());
      lcd.print(" ");
      lcd.print(tempTarget);
      lcd.setCursor(0, 1);
      lcd.print(">Humit: ");
      lcd.print(sensorValue);
      lcd.print(" ");
      lcd.print(humTarget);
      lcd.setCursor(0, 2);
      lcd.print(" WaterC: ");
      lcd.print(sekDelay);
      lcd.print(" ");
      lcd.print(waterTarget);
      lcd.setCursor(0, 3);
      lcd.print(" Quit ");
      break;
    case 3:
      lcd.clear();
      lcd.print(" Temp: ");
      lcd.print(dht.readTemperature());
      lcd.print(" ");
      lcd.print(tempTarget);
      lcd.setCursor(0, 1);
      lcd.print(" Humit: ");
      lcd.print(sensorValue);
      lcd.print(" ");
      lcd.print(humTarget);
      lcd.setCursor(0, 2);
      lcd.print(">WaterC: ");
      lcd.print(sekDelay);
      lcd.print(" ");
      lcd.print(waterTarget);
      lcd.setCursor(0, 3);
      lcd.print(" Quit ");
      break;
    case 4:
      lcd.clear();
      lcd.print(" Temp: ");
      lcd.print(dht.readTemperature());
      lcd.print(" ");
      lcd.print(tempTarget);
      lcd.setCursor(0, 1);
      lcd.print(" Humit: ");
      lcd.print(sensorValue);
      lcd.print(" ");
      lcd.print(humTarget);
      lcd.setCursor(0, 2);
      lcd.print(" WaterC: ");
      lcd.print(sekDelay);
      lcd.print(" ");
      lcd.print(waterTarget);
      lcd.setCursor(0, 3);
      lcd.print(">Quit");
      break;
    case 5:
      menu = 4;
      break;
  }
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
      action3(); //Måske while løkke med state = 1
      break;
    case 4:
      action4();
      break;
  }
}

void action1() {
  tempTarget++;
}
void action2() {
  humTarget++;
}
void action3() {
  waterTarget++;
}
void action4() {
  lcd.clear();
  lcd.print(">Quitting");
  delay(1500);
  lcd.clear();
  he = true;
  check = false;
  sekDelay = waterTarget;
}

void executeAction2() {
  switch (menu) {
    case 1:
      action5();
      break;
    case 2:
      action6();
      break;
    case 3:
      action7(); //Måske while løkke med state = 1
      break;
    case 4:
      action8();
      break;
  }
}

void action5() {
  tempTarget--;
}
void action6() {
  humTarget--;
}
void action7() {
  waterTarget--;
}
void action8() {
  lcd.clear();
  lcd.print(">Quitting");
  delay(1500);
  lcd.clear();
  he = true;
  check = false;
  sekDelay = waterTarget;
}