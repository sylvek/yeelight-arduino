#ifdef ESP32
  #include <WiFi.h>
#else
  #include <ESP8266WiFi.h>
#endif
#include <ArduinoJson.h>
#include "yeelight.h"

#define LED 2

StaticJsonDocument<200> jsonBuffer;
Yeelight* yeelight;

void setup() {
  Serial.begin(115200);
  pinMode(LED, OUTPUT);
  digitalWrite (LED, LOW);
  Serial.println("Starting...");

  connectToWiFi("***", "***");

  yeelight = new Yeelight();
  yeelight->lookup();
}

void loop() {
  if (yeelight->feedback()) {
    Serial.print("device: ");
    Serial.println(yeelight->getLocation());

    if (!yeelight->isPowered()) {
      digitalWrite(LED, HIGH);
      Serial.println(yeelight->sendCommand("set_power", "[\"on\", \"smooth\", 500]"));
      // Serial.println(yeelight->sendCommand("set_name", "[\"tv\"]"));
    }
    deserializeJson(jsonBuffer, yeelight->sendCommand("get_prop", "[\"power\", \"name\"]"));
    JsonObject root = jsonBuffer.as<JsonObject>();
    const char* state = root["result"][0];
    const char* name = root["result"][1];
    Serial.print("- power is: ");
    Serial.println(state);
    Serial.print("- name is: ");
    Serial.println(name);
  }
}

void connectToWiFi(const char * ssid, const char * pwd)
{
  WiFi.begin(ssid, pwd);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(F("."));
  }

  Serial.println("");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}
