#include <SoftwareSerial.h>
#include <string.h>

int espTx = 2;
int espRx = 3;
SoftwareSerial ESP(espTx, espRx);

void setup() {
  Serial.begin(57600);
  ESP.begin(57600);

}

int x=0;
char teste[5];
char inByte;
char c;
int y;
void loop() {

  //while(ESP.available() >= 0 && x<11){
  while (strncmp("OK", teste,2) != 0){
  ESP.print(F("AT\r\n"));
  inByte = ESP.read();
  teste[x] = inByte;
  Serial.println(inByte);
  delay(500);
  x++;
  }

  Serial.println("pegou");
  delay(5000);
  /*
 while (strncmp("OK", teste,2) != 0)

  ESP.print(F("AT+CWMODE=1\r\n"));
  inByte = ESP.read();
  Serial.print(inByte);
  delay(100);

  ESP.print(F("AT+CWJAP=\"LIEC_WIFI\",\"LIEC_123\"\r\n"));
  inByte = ESP.read();
  Serial.print(inByte);
  delay(100);

  ESP.print(F("AT+CWDHCP=1,1"));
  inByte = ESP.read();
  Serial.print(inByte);
  delay(100);

  ESP.print(F("AT+CIPSTA=\"10.0.0.14\"\r\n"));
  inByte = ESP.read();
  Serial.print(inByte);
  delay(100);

  ESP.print(F("AT+CIPSTART=\"TCP\",\"10.0.0.10\",23\r\n"));
  inByte = ESP.read();
  Serial.print(inByte);
  delay(100);
*/

}
void serialEvent() {
  if (ESP.available()) {
        c = ESP.read();
       teste[x] = c;
   x++;
   delay(10);
}
}
/* 
 *  AT+CWMODE=1
 *  AT+CWJAP="LIEC_WIFI","LIEC_123"
 *  AT+CWDHCP=1,1
 *  AT+CIPSTA="10.0.0.14"
 *  AT+CIPSTATUS
 *  AT+CIPSTART="TCP","10.0.0.10",23
*

 */
