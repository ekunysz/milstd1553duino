#include <Wire.h>
#include "MIL1553.h"
#include "TransportI2c.h"

TransportI2C transport(0x08, false);
MIL1553_RT rt(transport, 1);

void setup() {
  Serial.begin(9600);
  rt.begin();
  Serial.println("RT ready...");
}

void loop() {
  rt.listen();
}
