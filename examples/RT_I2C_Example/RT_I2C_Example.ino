#include <Wire.h>
#include <MIL1553.h>
#include <TransportI2c.h>

#define RT_I2C_ADDRESS 0x08
#define RT_1553_ADDRESS 1

TransportI2C transport(RT_I2C_ADDRESS, false);
MIL1553_RT rt(transport, RT_1553_ADDRESS);

void setup() {
  Serial.begin(9600);
  rt.begin();
  Serial.println("RT ready...");

  // Inicializo buffers de ejemplo
  rt.setTxBuffer(1, 0x1234); // subAddress 1 → sensor data
  rt.setTxBuffer(2, 0xABCD); // subAddress 2 → Sensor data
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

}
