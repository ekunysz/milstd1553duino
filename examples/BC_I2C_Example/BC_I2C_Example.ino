#include <Wire.h>
#include <MIL1553.h>
#include <TransportI2c.h>

#define RT_I2C_ADDRESS 0x08

TransportI2C transport(RT_I2C_ADDRESS, true); //RT I2C Address: 0x08
MIL1553_BC bc(transport);

void setup() {
  Serial.begin(9600);
  bc.begin();

  delay(500); //wait for RT
}

void loop() {
  // ---------------------------
  // 1. BC → RT: Send data
  // ---------------------------
  CommandWord cmd = { .rtAddress = 1, .tr = 0, .subAddress = 2, .wordCount = 1 };
  DataWord data = { .data = 0x1234 };
  Serial.println("Sending command to RT...");
  bc.sendCommand(cmd);
  Serial.println("Sending data to RT...");
  bc.sendData(data);

  delay(50);

  // ---------------------------
  // 2. RT → BC: ask for data
  // ---------------------------
  CommandWord cmd2 = { .rtAddress = 1, .tr = 1, .subAddress = 2, .wordCount = 1 };
  bc.sendCommand(cmd2);

  uint16_t received;
  if (bc.requestData(received)) {
    Serial.print("BC received data from RT: 0x");
    Serial.println(received, HEX);
  } else {
    Serial.println("BC: there was no response");
  }


  delay(2000);
}
