# yeelight-arduino
Arduino lib. to control Yeelight Bulb

[github.com/sylvek/yeelight-arduino](https://github.com/sylvek/yeelight-arduino)

[Yeelight documentation](https://www.yeelight.com/download/Yeelight_Inter-Operation_Spec.pdf)

## How to use ?

Add yeelight.h and yeelight.cpp to your Arduino project.

```
#include "yeelight.h"
```

Create a yeelight object

```
yeelight = new Yeelight();
```

lookup your bulb(s)

```
yeelight->lookup();
```

And listen...

```
void loop() {
  if (yeelight->feedback()) {
    Serial.println(yeelight->getLocation());
    Serial.println(yeelight->sendCommand("set_power", "[\"on\", \"smooth\", 500]"));
  }
}
```

## Warn :

~~If you use yeelight_remote.ino, dont use the last version of ArduinoJson Lib , use older than 5.0~~ Updated to 6.16.1

## Battle tested?

I've tested with my ESP32 device and only with one Bulb.
Tested with ESP8266(Wemos D1 Mini) and with only 1 bulb.
