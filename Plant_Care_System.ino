#include "DHT.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>

// Constants
#define DHTPIN 2      // Pin connected to the DHT sensor
#define DHTTYPE DHT11 // DHT 11

const int analogPin = A0; // analog input pin for soil moisture sensor
const int relayPin = 3;   // output pin for relay module

char caracter;
int temperature = 0;
int humidity = 0;
int hplmin = 350; 
int hplmax = 716; 
String tempera_humidity;

DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x27, 16, 2); // Set the LCD address to 0x27 for a 16 chars and 2 line display

void setup() {
  pinMode(relayPin, OUTPUT); // output pin for relay board
  Serial.begin(9600); // initialize serial communication
  dht.begin(); // initialize the DHT sensor
  lcd.init(); // initialize the LCD with 16 columns and 2 rows
  lcd.backlight(); // turn on the LCD backlight
}

void loop() {
  // Read the analog value from the soil moisture sensor
  int analogValue = analogRead(analogPin);

  // Read temperature and humidity values from the DHT11 sensor
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

   //Print sensor readings to the serial monitor
  Serial.print("Soil Moisture: ");
  Serial.print(analogValue);
  Serial.print("\nTemperature: ");
  Serial.print(temperature);
  Serial.print(" °C\nHumidity: ");
  Serial.print(humidity);
  Serial.println(" %");

  // Display sensor readings on the LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(temperature);
  lcd.print(" C");
  lcd.setCursor(0, 1);
  lcd.print("Humidity: ");
  lcd.print(humidity);
  lcd.print(" %");

  // Control the relay based on the analog sensor reading
  if (analogValue < 350) { // if analog value is less than 300 (soil is dry), then activate the relay and pump
    Serial.println("PUMP ACTIVE");
    digitalWrite(relayPin, HIGH); // HIGH to continue providing signal and water supply
  } else {
   digitalWrite(relayPin, LOW); 
  }

  // Check if there's any data sent from the HC-05 Bluetooth module
 if (Serial.available()) {
   char c = Serial.read();
   Serial.write(c);
  }

    Serial.println(tempera_humidity);
    
  delay(1000); // update every second
}

