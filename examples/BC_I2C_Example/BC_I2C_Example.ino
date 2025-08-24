#include <Wire.h>
#include <MIL1553.h>
#include <TransportI2c.h>

TransportI2C transport(0x08, true); //RT Address: 0x08
MIL1553_BC bc(transport);

void setup() {
  Serial.begin(9600);
  bc.begin();

  CommandWord cmd = { .rtAddress = 1, .tr = 0, .subAddress = 2, .wordCount = 1 };
  DataWord data = { .data = 0x1234 };
  Serial.println("Sending command to RT...");
  bc.sendCommand(cmd);
  Serial.println("Sending data to RT...");
  bc.sendData(data);
}

void loop() {
  // Podrías enviar comandos periódicos
  delay(2000);
}
