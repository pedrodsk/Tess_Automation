//#include <string.h>
//pacote C02EA82E012E0101abcd
//pacote C0 2E A8 2E 01 2E 01 ab cd ef
#include <SoftwareSerial.h>
int espTx = 2;
int espRx = 3;
SoftwareSerial ESP(espTx, espRx);


char stringIP[20]="";
char stringFuncao[5]="";
char stringDados[5] = "";
char stringEstados[5] = "";
//char stringSerial[25]="";
boolean stringCompleta = false;
char lerSerial[22]="";
char c;
char separarIP[20];
int x=0,y,t;
//char velocidadechar[10];
void setup() {
   //Serial.begin(9600);
   Serial.begin(57600);
   ESP.begin(57600);
//   delay(5000);
   conectar();
   
}

void loop() {
 
  if(t==1){
    Serial.println(stringIP);
    Serial.println(stringFuncao);
    Serial.println(stringDados);
    Serial.println(y);
    t=0;
  }
if(stringCompleta == 1){
/*if(stringFuncao[1] == '1'){
Serial.println("Modo escrita");
}
if(stringFuncao[1] == '0'){
Serial.println("Modo leitura");
c == '\n';
}  
*/
if(stringFuncao[1] == '1' && y==20){
Serial.print("IP: ");
Serial.println(stringIP);
Serial.print("FUNCAO: ");
Serial.println(stringFuncao);
Serial.print("DADOS: ");
Serial.println(stringDados);
//Serial.print("ESTADOS: ");
//Serial.println(stringEstados);
Serial.println("");
}
if(stringFuncao[1] == '0'){
Serial.print("IP: ");
Serial.println(stringIP);
Serial.print("FUNCAO: ");
Serial.println(stringFuncao);
Serial.println("");
}
//Serial.print("tamanho ");
//Serial.println(x);

ZerarParametros();

}
//x=0;
}

void serialEvent() {
  if (ESP.available()) {
        c = ESP.read();
       lerSerial[x] = c;
   x++;
   delay(10);
  if (c == '\n') {
    
    c=0;
    y=x;
    
 //  t=1; //FLAG DEBUG
  stringCompleta=1;
  if(x==18){
  PacoteIP();
  PacoteFuncao();
  }
  if(x==20){
  PacoteIP();
  PacoteFuncao();
  PacoteDados();
  }
 // PacoteEstados();
  x=0;
  }
  if (c == ':') {
    c=0;
    x=0;
 //   lerSerial[25] = {'0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'};
} 
}
}

void PacoteIP(){
  for(int a=0;a<14;a++){
    stringIP[a]=lerSerial[a];
  }
  /*stringIP[0]=lerSerial[0];
  stringIP[1]=lerSerial[1];
  stringIP[2]=lerSerial[2];
  stringIP[3]=lerSerial[3];
  stringIP[4]=lerSerial[4];
  stringIP[5]=lerSerial[5];
  stringIP[6]=lerSerial[6];
  stringIP[7]=lerSerial[7];
  stringIP[8]=lerSerial[8];
  stringIP[9]=lerSerial[9];
  stringIP[10]=lerSerial[10];
  stringIP[11]=lerSerial[11];
  stringIP[12]=lerSerial[12];
  stringIP[13]=lerSerial[13];
  */
}
void PacoteFuncao(){
  stringFuncao[0]=lerSerial[14];
  stringFuncao[1]=lerSerial[15];
}
void PacoteDados(){
  stringDados[0]=lerSerial[16];
  stringDados[1]=lerSerial[17];

}
void PacoteEstados(){
  stringEstados[0]=lerSerial[18];
  stringEstados[1]=lerSerial[19];

}
void ZerarParametros(){
  stringCompleta=0;
  c=0;
  x=0;
}
 void conectar(){
  if(ESP.available()){
    
    /*
  ESP.print(F("AT\r\n"));
  inByte = ESP.read();
  Serial.print(inByte);
  delay(200);
*/
  
///*
   ESP.print(F("AT+CWMODE=1\r\n"));
 // inByte = ESP.read();
  //Serial.print(inByte);
  delay(500);
//*/
  
/*
  ESP.print(F("AT+CWJAP=\"LIEC_WIFI\",\"LIEC_123\"\r\n"));
  inByte = ESP.read();
  Serial.print(inByte);
  delay(500);
*/

///*
  ESP.print(F("AT+CWDHCP=1,1\r\n"));
 // inByte = ESP.read();
 // Serial.print(inByte);
  delay(500);
//*/

///*
  ESP.print(F("AT+CIPSTA=\"10.0.0.14\"\r\n"));
 // inByte = ESP.read();
 // Serial.print(inByte);
  delay(500);

//*/

///*
  ESP.print(F("AT+CIPSTART=\"TCP\",\"10.0.0.13\",23\r\n"));
 // inByte = ESP.read();
 // Serial.print(inByte);
  delay(500);
 ESP.print(F("AT+CIPSEND=20\r\n"));
 // inByte = ESP.read();
 // Serial.print(inByte);
  delay(500);
  ESP.print(F("ola, conectei! PING."));


//x=2;
  }
 }
 

