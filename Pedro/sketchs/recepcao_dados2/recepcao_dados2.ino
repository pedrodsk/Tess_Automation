#include <string.h>

String stringIP = "";
String stringFuncao = "";
String stringDados = "";
String stringEstados = "";
String stringSerial = "";
int t1,t2,t3;
boolean stringCompleta = false;
char lerSerial[20];
char c;
char separarIP[20];
int x=0;
//char velocidadechar[10];
void setup() {
   Serial.begin(9600);
}

void loop() {

 
/*
separarIP[0]=lerSerial[0];
separarIP[1]=lerSerial[1];
separarIP[2]=lerSerial[2];
separarIP[3]=lerSerial[3];
separarIP[4]=lerSerial[4];
separarIP[5]=lerSerial[5];
separarIP[6]=lerSerial[6];
separarIP[7]=lerSerial[7];
separarIP[8]=lerSerial[8];
separarIP[9]=lerSerial[9];
separarIP[10]=lerSerial[10];
separarIP[11]=lerSerial[11];
separarIP[12]=lerSerial[12];
separarIP[13]=lerSerial[13];
separarIP[14]=lerSerial[14];
*/
if(stringCompleta){
  //Serial.println(separarIP);
  //Serial.println(stringSerial);
  t1 = stringIP.length()-1;
  t2 = stringFuncao.length()-1;
  t3 = stringDados.length()-1;
  //Serial.println(stringIP.length()-1);
  if(x==1){
  Serial.print(stringIP+"tamanho do pacote 1: ");
  Serial.println(stringIP.length()-1);
  }
  if(x==2){
  Serial.print(stringIP+"tamanho do pacote 1: ");
  Serial.println(stringIP.length()-1);
  Serial.print(stringFuncao+"tamanho do pacote 2: ");
  Serial.println(stringFuncao.length()-1);
  Serial.print(stringDados+"tamanho do pacote 3: ");
  Serial.println(stringDados.length()-1);
 // }
 // if(x==3) {
//}
  
  stringCompleta=0;
  c=0;
  stringSerial = "";
  x=0;
  }
}
}
  
 // Serial.println(stringSerial.length());
  //Serial.println(stringSerial.indexOf('>');
  // int detector = stringSerial.indexOf('*');
  //Serial.println(detector +1);
  
  
 // stringSerial = "";

//Serial.println(x);
//velocidadeint = atoi(velocidadechar);
//}
/*
void SerialEvent() {
  if (Serial.available()) {
//  do{
  c=(char)Serial.read();
  inputString += c;
  if(c=='\r'){
    x = 0;
    stringComplete = true;
  }
  else if(c=='\n')
  stringComplete = true;
      else{
        lerSerial[x]=c;
        x++;
        delay(100);
        }
//}while(c!='\r');
}
  
}
*/

void serialEvent() {
  if (Serial.available()) {
    
    c = Serial.read(); 
    stringSerial += c;
    //delay(1000);
  if (c == '\n' && x==0) {
    c=0;
    x++;
    stringIP = stringSerial;
    stringSerial = "";
       
  }
  if (c == '\n' && x==1) {
   // c=0;
    stringFuncao = stringSerial;
    stringSerial = "";
      if(stringFuncao[0] == '0'){
    stringCompleta = true;
    Serial.println("Modo Leitura");
    }
      if(stringFuncao[0] == '1'){
     c=0;    
    Serial.println("Modo escrita");
    x++;
   }
    //stringSerial = "";
    //stringCompleta = true;
   }
  if (c == '\n' && x==2) {
    Serial.println("pacote dados");
    stringDados = stringSerial;
    stringSerial = "";
   stringCompleta = true;
   }
     // stringSerial = "";
    // stringCompleta = true;
    } 
  }


