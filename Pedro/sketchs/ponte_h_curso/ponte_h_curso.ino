
char lerSerial[20];
char c;
char separarIP[20];
int x=0;
//char velocidadechar[10];

void setup() {
   Serial.begin(9600);
}

void loop() {

 

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
//if(c=='\r'){
  Serial.println(separarIP);
  delay(10);
}
//Serial.println(x);
//velocidadeint = atoi(velocidadechar);
//}
void SerialEvent() {
  if(Serial.available()){
//  do{
  c=Serial.read();
  if(c=='\r')
    x = 0;
  else if(c=='\n');
      else{
        lerSerial[x]=c;
        x++;
        }
//}while(c!='\r');
}
  
}


