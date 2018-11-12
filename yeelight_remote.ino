#include <WiFi.h>
#include "yeelight.h"

#define LED 2

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
    digitalWrite(LED, HIGH);
    Serial.println(yeelight->getLocation());
    Serial.println(yeelight->sendCommand("set_power", "[\"on\", \"smooth\", 500]"));
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
