void setup() {
  // initialize both serial ports:
  Serial.begin(57600);
  Serial1.begin(57600);
  Serial.flush();
  
 // delay(5000);
 // conectar();
}
char lerSerial2[23]="";
char lerSerial[23]="";
int x,t,y;
char c;
boolean stringCompleta = false;

void loop() {
if(Serial.available()){
 
  c=Serial.read();
  Serial.flush();
  lerSerial[x]=c;
  x++;
  delay(10);
  
  y=x; 
}
if (c == ':' || c=='\n') {
    c=0;
    x=0;
    t=1;
 }
if(x == 10){
stringCompleta=1;
x=0;
c=0;
}


 //zera o caracter

    
if(stringCompleta==1){
  Serial.println(lerSerial);
  //Serial.println(lerSerial2);
  Serial.println(y);
  //Serial.println(sizeof(lerSerial));
  stringCompleta=0;
  t=1;
 //for(int y=0;y<22;y++){
 // lerSerial[y]='0';
  //}
  //Serial.println(lerSerial);
 
 
}
if(t==1){
ZerarParametros();
t=0;  
}

  // read from port 0, send to port 1:
//  if (Serial.available()) {
  //  Serial1.write(Serial.read());
 // }
}
void ZerarParametros(){
  stringCompleta=0;
  c=0;
  x=0;
  Serial.flush();
  for(int x=0; x<23;x++)
{
lerSerial[x] = 0;  
}
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
 
