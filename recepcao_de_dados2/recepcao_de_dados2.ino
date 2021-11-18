//#include <string.h>
/*
######################################################
##                                                  ##
## C0 2E A8 2E 01 2E 01 00 0D 0A - LEITURA          ##
## C0 2E A8 2E 01 2E 01 01 01 0D 0A - LIGAR LED     ##
## C0 2E A8 2E 01 2E 01 01 00 0D 0A - DESLIGAR LED  ##
##                                                  ##
######################################################
*/
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
int x=0,y,t,h;
String estados;
//char velocidadechar[10];

void setup() {
  pinMode(8,OUTPUT);
  //digitalWrite(8,HIGH);
   //Serial.begin(9600);
   Serial.begin(57600);
   Serial.begin(57600);
   stringFuncao[0]='2'; 
   delay(5000);
   conectar();
   


 // instrucoes();
}
void loop() {
  /* falta ajeitar
  if(h==1){
    delay(1000);
    instrucoes();
    h=0;
  }
  */
   if (Serial.available()) {
        c = Serial.read();
       lerSerial[x] = c;
       x++;
       delay(10);
       
      // Serial.print(c);
   }
  if (c == ':' || c=='\n') {
    y=x;
    stringCompleta=1;
    t=1;
    
 }
  
  if(y==10){
  //t=1;
  PacoteIP();
  PacoteFuncao();
  }
  if(y==11){
  //t=1;
  PacoteIP();
  PacoteFuncao();
  PacoteDados();
  }

  if(stringCompleta == 1){

    if(y==10 && stringFuncao[0] == 0x00){
    Serial.println("Modo leitura");
    Serial.print("IP: ");
    Serial.println(stringIP);
    Serial.print("FUNCAO: ");
    Serial.println(stringFuncao);
    Serial.println("");
    Serial.println(estados);
    ZerarParametros();
    }

    if(y==11 && stringFuncao[0] == 0x01){
    Serial.println("Modo escrita");
    Serial.print("IP: ");
    Serial.println(stringIP);
    Serial.print("FUNCAO: ");
    Serial.println(stringFuncao);
    Serial.print("DADOS: ");
    Serial.println(stringDados);
//Serial.print("ESTADOS: ");
//Serial.println(stringEstados);
    Serial.println("");
    //teste pacote led
    if(stringDados[0] == 0x01){
    digitalWrite(8,HIGH);
    estados = "ligado";
    }
    if(stringDados[0] == 0x00){
    digitalWrite(8,LOW);
    estados = "desligado";
    }
    //fim do teste pacote led
    ZerarParametros();
    }
    


//debug
    if(t==1){ //inicio debug
 //   Serial.println(stringIP);
 //   Serial.println(stringFuncao);
 //   Serial.println(stringDados);
    Serial.print(lerSerial);
    Serial.println(y);
    
   ZerarParametros();
    } 
    // fim debug

ZerarParametros(); //zerar parametros
  } // fim da stringCompleta.
} //fim do loop.


//pacote C0 2E A8 2E 01 2E 01 01 ab 0D 0A
void PacoteIP(){
  for(int a=0;a<7;a++){
    stringIP[a]=lerSerial[a];
  }

}
void PacoteFuncao(){
  stringFuncao[0]=lerSerial[7];
  }
void PacoteDados(){
  stringDados[0]=lerSerial[8];
  
}
/*
void PacoteEstados(){
  stringEstados[0]=lerSerial[18];
  stringEstados[1]=lerSerial[19];

}
*/
void ZerarParametros(){
  stringCompleta=0;
  c=0;
  x=0;
  t=0;
  y=0;
  for(int b=0; b<23;b++)
  { 
  lerSerial[b] = 0;  
}
}
void instrucoes() {
 if (Serial.available()) {
Serial.print(F("AT+CIPSEND=54\r\n"));    
Serial.println(F("######################################################"));
delay(500);
Serial.print(F("AT+CIPSEND=54\r\n"));
Serial.println(F("##                                                  ##"));
delay(500);
Serial.print(F("AT+CIPSEND=54\r\n"));
Serial.println(F("## C0 2E A8 2E 01 2E 01 00 0D 0A - LEITURA          ##"));
delay(500);
Serial.print(F("AT+CIPSEND=54\r\n"));
Serial.println(F("## C0 2E A8 2E 01 2E 01 01 01 0D 0A - LIGAR LED     ##"));
delay(500);
Serial.print(F("AT+CIPSEND=54\r\n"));
Serial.println(F("## C0 2E A8 2E 01 2E 01 01 00 0D 0A - DESLIGAR LED  ##"));
delay(500);
Serial.print(F("AT+CIPSEND=54\r\n"));
Serial.println(F("##                                                  ##"));
delay(500);
Serial.print(F("AT+CIPSEND=54\r\n"));
Serial.println(F("######################################################"));
delay(500);
}
}
 void conectar(){
  if(Serial.available()){
    /*
  Serial1.print(F("AT\r\n"));
  inByte = Serial1.read();
  Serial.print(inByte);
  delay(200);
*/
  
///*
   Serial.print(F("AT+CWMODE=1\r\n"));
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
  Serial.print(F("AT+CWDHCP=1,1\r\n"));
 // inByte = Serial1.read();
 // Serial.print(inByte);
  delay(500);
//*/

///*
  Serial.print(F("AT+CIPSTA=\"10.0.0.14\"\r\n"));
 // inByte = Serial1.read();
 // Serial.print(inByte);
  delay(500);

//*/

///*
  Serial.print(F("AT+CIPSTART=1,\"TCP\",\"10.0.0.13\",23\r\n"));
 // inByte = Serial1.read();
 // Serial.print(inByte);
  delay(500);
 Serial.print(F("AT+CIPSEND=5\r\n"));
 // inByte = Serial1.read();
 // Serial.print(inByte);
  delay(500);
  Serial.println(F("PING."));
  
  }
 }
 

