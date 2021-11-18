void setup() {
  // initialize both serial ports:
  Serial.begin(115200);
  Serial1.begin(57600);
  delay(5000);
  
 // conectar();
}
char lerSerial[22]="";
int x,t;
char c;

void loop() {
  // read from port 1, send to port 0:
  /*
  if (Serial1.available()) {
    int inByte = Serial1.read();
    Serial.write(inByte);
  }
  */
   if (Serial.available()) {
  do{
  c=Serial.read();
  lerSerial[x]=c; 
   x++; 
  delay(1); 
while(c!='\n')
}
   }
    x=0;
  
    
if(t==1){
  Serial.println("oi");
  t=0;
}
  // read from port 0, send to port 1:
//  if (Serial.available()) {
  //  Serial1.write(Serial.read());
 // }
}
void conectar(){
  if(Serial1.available()){
    /*
  Serial1.print(F("AT\r\n"));
  inByte = Serial1.read();
  Serial.print(inByte);
  delay(200);
*/
  
///*
   Serial1.print(F("AT+CWMODE=1\r\n"));
 // inByte = Serial1.read();
  //Serial.print(inByte);
  delay(500);
//*/
  
/*
  Serial1.print(F("AT+CWJAP=\"LIEC_WIFI\",\"LIEC_123\"\r\n"));
  inByte = Serial1.read();
  Serial.print(inByte);
  delay(500);
*/

///*
  Serial1.print(F("AT+CWDHCP=1,1\r\n"));
 // inByte = Serial1.read();
 // Serial.print(inByte);
  delay(500);
//*/

///*
  Serial1.print(F("AT+CIPSTA=\"10.0.0.14\"\r\n"));
 // inByte = Serial1.read();
 // Serial.print(inByte);
  delay(500);

//*/

///*
  Serial1.print(F("AT+CIPSTART=\"TCP\",\"10.0.0.13\",23\r\n"));
 // inByte = Serial1.read();
 // Serial.print(inByte);
  delay(500);
 Serial1.print(F("AT+CIPSEND=20\r\n"));
 // inByte = Serial1.read();
 // Serial.print(inByte);
  delay(500);
  Serial1.print(F("PING."));

//*/
//x=2;
  }
 }
