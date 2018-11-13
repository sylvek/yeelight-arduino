#include <WiFi.h>
#include <ArduinoJson.h>
#include "yeelight.h"

#define LED 2

StaticJsonBuffer<200> jsonBuffer;
Yeelight* yeelight;

void setup() {
  Serial.begin(115200);
  pinMode(LED, OUTPUT);
  digitalWrite (LED, LOW);
  Serial.println("Starting...");

  connectToWiFi("ssid", "password");

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
    }

    JsonObject& root = jsonBuffer.parseObject(yeelight->sendCommand("get_prop", "[\"power\"]"));
    const char* state = root["result"][0];
    Serial.print("- power is: ");
    Serial.println(state);
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
