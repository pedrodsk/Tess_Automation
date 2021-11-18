#include <SoftwareSerial.h>
int espTx = 2;
int espRx = 3;
SoftwareSerial ESP(espTx, espRx);

void setup() {
  // initialize both serial ports:
  Serial.begin(57600);
  ESP.begin(57600);
  //delay(5000);
  //conectar();
   char teste[20];
}

void loop() {
  // read from port 1, send to port 0:
  
  if (ESP.available()) {
    char inByte = ESP.read();
    Serial.print(inByte);
  }
  
   
  // read from port 0, send to port 1:
  if (Serial.available()) {
    char inByte = Serial.read();
    ESP.print(inByte);
  }
}

