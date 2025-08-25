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

// Case BC→RT: read sending data
if (rt.hasNewMessage()) {
  MIL1553_Message msg = rt.getMessage();
  Serial.print("Received Cmd: subAddr=");
  Serial.print(msg.cmd.subAddress);
  Serial.print(" data=0x");
  Serial.println(msg.data, HEX);

}

// Case RT→BC: update sensors buffers TODO
//rt.setTxBuffer(1, analogRead(A0));   // ex. sensor subaddress 1
//rt.setTxBuffer(2, analogRead(A1));   // ex. another sensor
}
