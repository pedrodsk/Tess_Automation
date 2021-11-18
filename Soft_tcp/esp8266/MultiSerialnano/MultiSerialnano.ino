//com esse sketch vc vai poder escrever os comandos AT pela serial e ler no outro canal a resposta do modulo
#include <SoftwareSerial.h>
#include <string.h>

int espTx = 2; //espTX no pino 2
int espRx = 3; //espRX no pino 3 com o divisor de tensao
SoftwareSerial ESP(espTx, espRx);

void setup() {
  // initialize both serial ports:
  Serial.begin(115200);
  ESP.begin(115200);
}

void loop() {
  // read from port 1, send to port 0:
  
  if (ESP.available()) {
    char inByte = ESP.read();
    Serial.write(inByte);
  }
  
   
  // read from port 0, send to port 1:
  if (Serial.available()) {
    char inByte = Serial.read();
    ESP.write(inByte);
  }
}

