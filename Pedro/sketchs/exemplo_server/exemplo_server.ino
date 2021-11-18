void conectar(){
  if(Serial.available()){
  
  Serial1.print(F("AT\r\n"));
  inByte = Serial1.read();
  Serial.print(inByte);
  delay(200);

   Serial.print(F("AT+CWMODE=1\r\n"));
  inByte = Serial1.read();
  Serial.print(inByte);
  delay(500);

  Serial1.print(F("AT+CWJAP=\"LIEC_WIFI\",\"LIEC_123\"\r\n"));
  inByte = Serial1.read();
  Serial.print(inByte);
  delay(500);

  Serial.print(F("AT+CWDHCP=1,1\r\n"));
  inByte = Serial1.read();
  Serial.print(inByte);
  delay(500);

  Serial.print(F("AT+CIPSTA=\"10.0.0.14\"\r\n"));
  inByte = Serial1.read();
  Serial.print(inByte);
  delay(500);

  Serial.print(F("AT+CIPMUX=1\r\n"));
  inByte = Serial1.read();
  Serial.print(inByte);
  delay(500);
 
 Serial.print(F("AT+CIPSERVER=1,502"));
  inByte = Serial1.read();
  Serial.print(inByte);
  delay(500);
  }
