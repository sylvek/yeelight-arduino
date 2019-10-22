/*
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.

smaucourt@gmail.com - 11/11/2018
*/

#ifdef ESP32
  #include <WiFi.h>
#else
  #include <ESP8266WiFi.h>
#endif

#include <WiFiUdp.h>
#include "yeelight.h"

WiFiUDP _udp;
WiFiClient _client;
IPAddress _ipMulti(239, 255, 255, 250);
char _packetBuffer[550];

String _location, _support;
bool _powered;
char _server[15];

uint16_t _cmdid = 0, _port = 0;

Yeelight::Yeelight()
{
}

Yeelight::~Yeelight()
{
  _udp.stop();
}

void Yeelight::lookup()
{
  #ifdef ESP32
    _udp.beginMulticast(_ipMulti, 1982);
    _udp.beginMulticastPacket();
  #else
    _udp.beginMulticast(WiFi.localIP(), _ipMulti, 1982);
    _udp.beginPacketMulticast(_ipMulti, 1982, WiFi.localIP());
  #endif
  _udp.print("M-SEARCH * HTTP/1.1\r\nHOST: 239.255.255.250:1982\r\nMAN: \"ssdp:discover\"\r\nST: wifi_bulb");
  _udp.endPacket();
  _udp.begin(1982);
}

int Yeelight::feedback()
{
  int packetSize = _udp.parsePacket();
  if (packetSize) {
    int len = _udp.read(_packetBuffer, 550);
    if (len > 0) {
      _packetBuffer[len] = 0;
    }
    parseFeedback(_packetBuffer, len);
  }
  return packetSize;
}

void Yeelight::parseFeedback(char* buffer, size_t len)
{
  int i=0, _i=0;
  char _b[255];
  while (i<len) {
    if (buffer[i] == '\r' &&
        i+1 <= len &&
        buffer[i+1] == '\n') {
        _b[_i]=0;

        // ----
        String _str = String(_b);
        if (_str.startsWith("Location: yeelight://")) {
          int colon = _str.indexOf(':', 21) + 1;
          _location = _str.substring(10);
          _str.substring(21, colon).toCharArray(_server, colon - 21);
          _port = _str.substring(colon).toInt();
        }
        if (_str.startsWith("support: ")) {
          _support = _str.substring(9);
        }
        if (_str.startsWith("power: ")) {
          _powered = _str.substring(7) == "on";
        }
        // ----

        i=i+2;
        _i=0;
    } else {
      _b[_i]=buffer[i];
      i++;
      _i++;
    }
  }
}

String Yeelight::sendCommand(String method, String params)
{
  if (_client.connect(_server, _port)) {
    String payload = String("") + "{\"id\":" + (++_cmdid) + ",\"method\":\"" + method + "\",\"params\":" + params + "}";
    _client.println(payload);
  }

  String result = "";
  while (_client.connected()) {
    result = _client.readStringUntil('\r');
    _client.stop();
  }
  return result;
}

bool Yeelight::isPowered()
{
  return _powered;
}

String Yeelight::getSupport()
{
  return _support;
}

String Yeelight::getLocation()
{
  return _location;
}
