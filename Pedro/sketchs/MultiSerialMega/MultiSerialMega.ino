void setup() {
  // initialize both serial ports:
  Serial.begin(57600);
  Serial1.begin(57600);
  //delay(5000);
  //conectar();
   char teste[20];
}

void loop() {
  // read from port 1, send to port 0:
  
  if (Serial1.available()) {
    char inByte = Serial1.read();
    Serial.write(inByte);
  }
  
   
  // read from port 0, send to port 1:
  if (Serial.available()) {
    char inByte = Serial.read();
    Serial1.write(inByte);
  }
}

