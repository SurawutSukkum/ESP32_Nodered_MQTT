

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>

#include "DHT.h"

#define i2c_Address 0x3c //initialize with the I2C addr 0x3C Typically eBay OLED's
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET -1   //   QT-PY / XIAO


Adafruit_SH1106G display = Adafruit_SH1106G(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


#define DHTPIN 4 
#define DHTTYPE DHT11   // DHT 11
DHT dht(DHTPIN, DHTTYPE);


void setup() {
  display.begin(i2c_Address, true); // Address 0x3C default
  display.clearDisplay();
  delay(2000);

  dht.begin();
}

void loop() {
    // text display tests
  int temp = dht.readTemperature();
  int humi = dht.readHumidity(); 
      
  display.setTextSize(1);
  display.setTextColor(SH110X_WHITE);
  display.setCursor(0, 0);
  display.println("First Day1 learn ESP32 by Marc");
  display.setCursor(0, 20);
  display.print("temp is ");
  display.print(temp);
  display.println(" *C");
  display.setCursor(0, 30);
  display.print("Humi is ");
  display.print(humi);
  display.println(" %");
  display.display();
  delay(2000);
  display.clearDisplay();


  
}
