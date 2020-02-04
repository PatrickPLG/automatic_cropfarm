/*
 * Automatic cropfarm for small gardens
 * Made by PatrickPLG og Klint02
 * version 1.1 Public Release
 */

// Include libraries
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#include  <Wire.h>
#include <LiquidCrystal.h>
// ------------------

// Notes to setup for screen
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
// ------------------

// Which pins the LCD screen uses / Setup for LCD screen
LiquidCrystal lcd(32, 30, 28, 26, 24, 22);
// ------------------

// Temeperature sensor
DHT dht(A1, DHT11);
// ------------------

// Target values
int tempTarget = 25;
int humTarget = 700;
int waterTarget = 7;

// ------------------

// Actual values
int sekDelay = 5;
int humActual = 500;

// ------------------

// Different sensors
int temp = A1;
#define SensorPin A0
float sensorValue = A0;
int transistor = transistor;
// ------------------

// Values to the settings menu
int menu = 1;
void updateMenu();
// ------------------

// Inputs that the bluetooth module and app uses
char state = 0;
char state2 = 0;
// ------------------


// Different booleans there is used for making different things on the screen appear
boolean check = false;
boolean updateMenuRUN = false;
boolean runSettings = false;
boolean sensorValueRUN = true;
// ------------------

void setup() {
  // Starts Serial
  Serial.begin(9600);
  // Sets the transistor to OUTPUT 
  pinMode(transistor, OUTPUT);
  // Starts the DHT sensor
  dht.begin();
  // Starts the LCD screen
  lcd.begin(20, 4);
}

void loop() {
  if (check == false) {
    // Soil Moisture Sensor and pump
    // If the Soil Moisture Sensors input is high
    if (sensorValue == HIGH) {
      // Set the input to the Transistor high which starts the pump
      digitalWrite(transistor, HIGH);
      // Delay
      delay(waterTarget * 1000);
      // Stops the pump
      digitalWrite(transistor, LOW);
    }

    // If the Soil Moisture Sensor is low
    if (sensorValue == LOW)
    {
      // Set the input to the Transistor low which stops the pump
      digitalWrite(transistor, LOW);
    }
    // ------------------

    // Delay
    delay(1000);

    // Temeperature
    // Reads the temeperature in celsius
    float t = dht.readTemperature();
    // Reads the temeperature in Fahrenheit
    float f = dht.readTemperature(true);
    // ------------------


    // Soil Moisture Sensor
    // Runs measurement of the Soil Moisture Sensor while sensorValueRUN is true
    while sensorValueRUN = true {
      sensorValue = sensorValue + analogRead(SensorPin);
      delay(1);
    }

    // Takes the value of sensorValue and divides it by 100
    sensorValue = sensorValue / 100.0;
    // ------------------

    // delay
    delay(30);

    // LCD Screen
    // Places the cursor in 0,1
    lcd.setCursor(0, 1);
    // Prints the temperature in celsius and Fahrenheit
    lcd.print("Temp: ");
    lcd.print(t);
    lcd.print((char)223);
    lcd.print("C ");
    lcd.print(f);
    lcd.print("F");

    // Places the cursor in 0,2
    lcd.setCursor(0, 2);
    // Prins value from the Soil Moisture Sensor
    lcd.print("Fugtighed: ");
    lcd.print(sensorValue);
    lcd.print("");
    // ------------------
  }
  // initiate settings menu
  // Checks if there is coming data from the bluetooth module
  if (Serial.available() > 0) {
    state = Serial.read();
    // if input from app to bluetoth module is equal to 2
    if (state == '2') {
      // sets runSettings to false
      runSettings = false;
      // sets check to true
      check = true;
      // clear the LCD screen
      lcd.clear();
      // while runsettings is equal to false, run settings
      while (runSettings == false) {
        settings();
      }
    }
  }
  // ------------------
}

void settings() {
  // updateMenu
  // runs updateMenu one time
  if (updateMenuRUN == false) {
    updateMenu();
    updateMenuRUN = true;
  }
  // ------------------

  // navigation in settings, with data from app
  // Checks if there is coming data from the bluetooth module
  if (Serial.available() > 0) {
    state = Serial.read();
    // if input from app to bluetoth module is equal to a
    if (state == 'a') {
      // prints "down" in the app
      Serial.println("Down");
      // moves cursor in menu up
      menu++;
      // updates the menu, so it shows
      updateMenu();
      // delay
      delay(100);
    }
    // if input from app to bluetoth module is equal to b
    if (state == 'b') {
      // prints "up" in the app
      Serial.println("Up");
      // moves cursor down in menu
      menu--;
      // updates the menu, so it shows
      updateMenu();
      // delay
      delay(100);
    }
    // if input from app to bluetoth module is equal to 0
    if (state == '0') {
      // prints "+" in the app
      Serial.println("+");
      // executes the action which the cursor is on
      executeAction();
      // updates the menu
      updateMenu();
      // delay
      delay(100);
    }
    // if input from app to bluetoth module is equal to 1
    if (state == '1') {
      // prints "-" in the app
      Serial.println("-");
      // executes action2
      executeAction2();
      // updates the menu
      updateMenu();
      // delay
      delay(100);
    }
  }
  // ------------------
}


void updateMenu() {
  // Visual navigation
  // sets runsettings to false
  if (runSettings == false) {
    // runs different visuals on the LCD screen with input from the app
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
  // ------------------
}

void executeAction() {
  // execute action
  // executes the action which the cursor is on
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
  // ------------------
}

// actions related to executeAction
void action1() {
  // plus tempTarget
  tempTarget++;
}
void action2() {
  // plus humTarget
  humTarget++;
}
void action3() {
  // plus waterTarget
  waterTarget++;
}
void action4() {
  // clears the LCD screen
  lcd.clear();
  // prints "Quitting" on the LCD screen
  lcd.print(">Quitting");
  // delay
  delay(1500);
  // clears the LCD screen
  lcd.clear();
  // sets runsettings to true
  runSettings = true;
  // sets check to false
  check = false;
  // sets sekDelay equal to waterTarget
  sekDelay = waterTarget;
}
// ------------------

void executeAction2() {
  // execute action2
  // executes the action which the cursor is on
  switch (menu) {
    case 1:
      action5();
      break;
    case 2:
      action6();
      break;
    case 3:
      action7();
      break;
    case 4:
      action8();
      break;
  }
  // ------------------
}

// actions related to executeAction2
void action5() {
  // minus tempTarget
  tempTarget--;
}
void action6() {
  // minus humTarget
  humTarget--;
}
void action7() {
  // minus waterTarget
  waterTarget--;
}
void action8() {
  // clears the LCD screen
  lcd.clear();
  // prints "Quitting" on the lcd screen
  lcd.print(">Quitting");
  // delay
  delay(1500);
  // clears the LCD screen
  lcd.clear();
  // sets runsettings to true
  runSettings = true;
  // sets check to false
  check = false;
  // sets sekDelay equal to waterTarget
  sekDelay = waterTarget;
}
// ------------------