# yeelight-arduino
Arduino lib. to control Yeelight Bulb

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

## Battle tested?

I've tested with my ESP32 device and only with one Bulb.
