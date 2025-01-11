#include <WiFi.h>
#include <PubSubClient.h>
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


// Wi-Fi credentials
const char* ssid = "TESTESP";
const char* password = "0884118773";

// MQTT Broker details
const char* mqtt_server = "broker.hivemq.com";
const int mqtt_port = 1883;
const char* publish_topic = "test/topicTar";
const char* subscribe_topic = "python/testTar";

// Wi-Fi and MQTT clients
WiFiClient espClient;
PubSubClient client(espClient);

void setupWiFi() {
  delay(10);
  Serial.println("Connecting to Wi-Fi...");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Connected to Wi-Fi.");
    // Once connected, print IP address
  Serial.println("\nConnected to Wi-Fi!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP()); // Print the ESP32's IP address
}

void reconnectMQTT() {
  while (!client.connected()) {
    Serial.println("Connecting to MQTT...");
    if (client.connect("ESP32Client")) {
      client.publish(publish_topic, "hello world");
      client.subscribe(subscribe_topic);
    } else {
      Serial.print("Failed, rc=");
      Serial.print(client.state());
      delay(5000);
    }
  }
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message received [");
  Serial.print(topic);
  Serial.print("]: ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}

void setup() {
  Serial.begin(115200);
  display.begin(i2c_Address, true); // Address 0x3C default
  display.clearDisplay();
  delay(2000);

  dht.begin();
  
  setupWiFi();
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
}

void loop() {
  if (!client.connected()) {
    reconnectMQTT();
  }
  client.loop();

  // Example of publishing a message
  static unsigned long lastTime = 0;
  if (millis() - lastTime > 5000) {
    lastTime = millis();
 
    int temp = dht.readTemperature();
    int humi = dht.readHumidity(); 
    
    String message = "Hello from ESP32! Temp is" + String(temp)+ " *c Humi is " + String(humi)+ " %";
    client.publish(publish_topic, message.c_str());
    Serial.println("Message published.");
         
    display.setTextSize(1);
    display.setTextColor(SH110X_WHITE);
    display.setCursor(0, 0);
    display.println("Day2 learn ESP32");
    display.setCursor(0, 10);
    display.println("by Marc");
    display.setCursor(0, 20);
    display.print("temp is ");
    display.print(temp);
    display.println(" *C");
    display.setCursor(0, 30);
    display.print("Humi is ");
    display.print(humi);
    display.println(" %");
    display.setCursor(0, 40);
    display.print("IP : ");
    display.println(WiFi.localIP()); // Print the ESP32's IP address
    display.display();
    delay(2000);
    display.clearDisplay();
  }
}
