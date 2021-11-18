#include <IRremote.h>
IRsend irsend;
int RECV_PIN = 11;
IRrecv irrecv(RECV_PIN);
decode_results results;
char c;

void setup() {
//irrecv.enableIRIn(); 
irrecv.blink13(true);
Serial.begin(115200); 
digitalWrite(3, HIGH);
}

void loop() {

//if (irrecv.decode(&results)) {
 // dump(&results);
//  irrecv.resume();
  //Serial.println(results.value,HEX);
//}
//int i = 0;
//int ler_buf[2];
//if(i<2){
if(Serial.available()){
c=Serial.read();
  

if(c == 'a') //a = 17
  {
unsigned int raw[200] = {4400,4350,550,1550,600,500,600,1550,600,1550,600,500,600,500,600,1550,600,500,600,500,600,1550,600,500,600,500,600,1550,600,1550,600,500,550,1550,600,500,600,550,550,500,600,1550,600,1550,600,1550,600,1550,600,1550,600,1550,600,1550,600,1550,550,550,600,500,550,550,550,550,550,500,600,500,600,500,600,500,600,500,600,1550,600,500,600,500,600,500,600,1550,650,1500,600,1550,600,1550,600,500,600,1550,600,1500,650,1500,600,5200,4450,4300,600,1550,600,500,600,1500,600,1550,600,500,600,500,650,1500,600,500,600,500,600,1550,600,500,600,500,600,1550,600,1550,600,500,600,1550,600,500,600,500,600,500,600,1550,550,1550,600,1550,650,1500,600,1550,600,1550,600,1550,600,1550,600,500,600,500,600,500,600,500,600,500,600,500,600,500,600,500,600,500,550,1550,600,500,600,500,600,500,600,1550,600,1550,600,1550,600,1550,600,500,600,1550,600,1550,600,1550,600,};
irsend.sendRaw(raw,200,38);
digitalWrite(3, HIGH);
delay(200);
Serial.println(F(("Temperatura: 17 graus.")));
  }

if(c == 'b') //b = 18
  {
unsigned int raw[200] = {4400,4350,600,1500,650,500,550,1550,600,1550,650,450,600,500,650,1500,600,500,600,500,650,1500,600,500,600,500,600,1550,600,1550,600,500,600,1550,550,550,600,500,550,500,600,1550,600,1550,600,1550,600,1550,600,1550,600,1550,600,1550,600,1550,600,500,600,500,600,500,600,500,550,550,550,550,550,500,600,500,650,1500,600,1550,600,500,650,450,600,500,600,1550,600,1550,600,1550,600,500,600,500,600,1550,600,1550,600,1550,550,5200,4400,4350,600,1550,600,500,600,1550,600,1550,550,500,600,500,650,1500,600,500,600,500,600,1550,600,500,600,500,600,1550,600,1550,600,500,600,1550,600,500,600,500,600,500,600,1550,600,1550,550,1550,600,1550,600,1550,600,1550,600,1550,600,1550,600,500,600,500,600,500,600,500,600,500,600,500,600,500,600,500,600,1550,550,1550,600,500,600,500,600,500,600,1550,600,1550,600,1550,600,500,600,500,600,1550,600,1550,600,1550,600,};
irsend.sendRaw(raw,200,38);

delay(200);
Serial.println(F(("Temperatura: 18 graus.")));
  }
  if(c == 'c') //c=19
  {
unsigned int raw[200] = {4450,4250,650,1500,600,500,650,1500,650,1500,600,500,650,450,600,1550,600,500,600,500,600,1550,600,500,600,500,600,1550,600,1550,550,500,650,1500,650,450,650,450,650,450,650,1500,650,1500,600,1550,600,1550,600,1550,600,1550,600,1550,600,1500,600,500,650,450,600,500,650,450,650,450,650,450,600,500,650,1500,600,1550,650,1500,600,500,600,500,600,500,600,1550,600,1550,600,500,600,500,600,500,600,1500,600,1550,650,1500,650,5150,4450,4300,600,1500,650,500,600,1500,600,1550,650,450,650,450,650,1500,650,450,650,450,600,1550,600,500,600,500,600,1550,600,1550,600,500,600,1550,600,500,600,500,600,450,650,1500,650,1500,600,1550,650,1500,600,1550,600,1550,600,1550,600,1550,600,500,600,500,600,500,600,500,550,550,600,450,600,550,600,1500,650,1500,650,1500,650,450,600,500,650,450,650,1500,600,1550,600,500,600,500,600,500,600,1550,600,1550,600,1500,650,};
irsend.sendRaw(raw,200,38);

delay(200);
Serial.println(F(("Temperatura: 19 graus.")));
  }
  if(c == 'd') //d = 20
  {
unsigned int raw[200] = {4450,4300,600,1550,600,500,600,1550,600,1550,600,500,600,500,600,1550,600,500,600,500,600,1550,550,550,550,550,550,1550,600,1550,600,500,600,1550,600,500,600,500,600,500,600,1550,600,1550,600,1550,600,1550,600,1550,550,1600,550,1550,600,1550,600,500,600,500,600,500,600,500,600,500,600,500,600,500,600,1550,600,500,600,1550,600,500,600,500,600,500,600,1550,600,1550,550,550,550,1550,600,500,600,1550,600,1550,600,1550,600,5200,4400,4300,600,1550,600,550,550,1550,600,1550,600,500,600,500,600,1550,600,500,600,500,600,1550,600,500,600,500,600,1550,550,1550,600,550,550,1550,600,550,550,550,550,550,550,1550,600,1550,600,1550,600,1550,600,1550,600,1550,550,1600,550,1600,550,550,550,550,550,550,550,550,550,550,550,550,550,500,600,1550,600,550,550,1550,600,500,600,550,550,500,600,1550,600,1550,600,500,600,1550,550,550,550,1550,600,1550,600,1550,600,};
irsend.sendRaw(raw,200,38);
delay(200);
Serial.println(F(("Temperatura: 20 graus.")));
  }
  if(c == 'e')//e = 21
  {
unsigned int raw[200] = {4400,4350,600,1550,600,500,550,1600,550,1550,600,500,600,500,600,1550,600,500,600,500,600,1550,650,450,600,500,600,1550,600,1550,600,500,600,1550,600,500,600,500,600,500,550,1600,550,1550,600,1550,600,1550,650,1500,600,1550,600,1550,600,1550,600,500,600,500,600,500,600,500,600,500,550,550,600,1500,600,1550,600,500,600,1550,600,500,600,500,600,500,600,1550,600,500,600,500,600,1550,600,500,600,1550,600,1550,600,1550,550,5200,4400,4350,600,1550,600,500,600,1550,600,1550,550,550,550,550,550,1550,600,500,600,500,600,1550,600,500,600,500,600,1550,600,1550,600,500,600,1550,600,500,600,500,600,500,600,1550,600,1550,550,1600,550,1550,600,1550,600,1550,600,1550,600,1550,600,500,600,500,600,500,600,500,600,500,600,500,600,1550,600,1550,550,550,550,1550,600,550,550,550,550,550,550,1550,600,550,550,550,550,1550,600,550,550,1550,600,1550,600,1550,600,};
irsend.sendRaw(raw,200,38);

delay(200);
Serial.println(F(("Temperatura: 21 graus.")));
  }
  
  if(c == 'f') //f =22
  {
unsigned int raw[200] = {4450,4300,600,1550,600,500,600,1550,600,1550,600,500,600,500,600,1550,550,550,600,500,600,1500,600,500,600,500,650,1500,600,1550,600,500,600,1550,600,500,600,500,600,500,600,1550,600,1550,600,1550,550,1550,600,1550,600,1550,650,1500,600,1550,600,500,600,500,600,500,600,500,600,500,600,500,600,1550,600,1550,600,1550,600,1500,600,500,600,500,600,500,600,1550,600,500,600,500,600,500,600,500,600,1550,600,1550,600,1550,600,5150,4450,4300,600,1550,600,500,600,1550,600,1550,600,500,600,500,600,1550,550,550,550,550,550,1550,600,500,600,500,600,1550,600,1550,600,500,600,1550,600,500,600,500,600,500,600,1550,600,1550,600,1550,550,1550,600,1550,600,1550,600,1550,600,1550,600,500,600,500,600,500,600,500,600,500,600,500,600,1550,600,1550,600,1550,550,1550,600,550,550,500,600,500,600,1550,600,500,600,500,600,500,600,500,600,1550,600,1550,600,1550,600,};
irsend.sendRaw(raw,200,38);
delay(200);
Serial.println(F(("Temperatura: 22 graus.")));
  }

if(c == 'g') //g = 23
  {
unsigned int raw[200] = {4400,4350,600,1550,600,500,550,1600,550,1550,600,500,600,500,650,1500,600,500,600,500,600,1550,600,500,600,500,600,1550,600,1550,600,500,600,1550,600,500,550,550,600,500,550,1550,600,1550,600,1550,600,1550,600,1550,600,1550,600,1550,600,1550,600,500,600,500,600,500,600,500,550,550,550,550,550,1550,600,500,600,1550,600,1550,600,500,600,500,600,500,600,1550,600,500,600,1550,600,500,600,500,600,1550,600,1550,550,1550,600,5200,4400,4350,600,1550,550,550,600,1550,550,1550,600,500,600,500,600,1550,600,500,600,500,600,1550,600,500,600,500,600,1550,600,1550,600,500,600,1550,600,500,600,500,550,550,550,1550,600,1550,600,1550,600,1550,600,1550,600,1550,600,1550,600,1550,600,500,600,500,550,550,600,500,550,550,550,550,550,1550,600,500,600,1550,600,1550,600,500,600,500,600,500,600,1550,600,500,600,1550,600,500,600,500,600,1550,600,1550,550,1600,550,};
irsend.sendRaw(raw,200,38);
delay(200);
Serial.println(F(("Temperatura: 23 graus.")));
  }

  if(c == 'h') //h = 24
  {
unsigned int raw[200] = {4400,4350,550,1600,550,550,600,1550,550,1550,600,550,550,500,600,1550,600,500,600,500,600,1550,600,500,600,500,600,1550,600,1550,600,500,550,1600,600,500,550,550,600,500,600,1550,550,1550,600,1550,600,1550,600,1550,600,1550,550,1600,600,1550,600,500,550,550,600,500,600,500,600,500,600,500,600,1550,550,550,550,500,600,1550,600,500,600,500,600,500,600,1550,600,500,600,1550,550,1600,600,500,550,1600,550,1600,600,1550,550,5200,4400,4350,600,1550,550,550,600,1550,600,1550,550,550,550,500,600,1550,600,500,600,500,600,1550,600,500,600,500,600,1550,550,1600,550,550,550,1600,550,550,600,500,550,550,600,1550,550,1550,600,1550,600,1550,600,1550,600,1550,600,1550,550,1600,550,550,600,500,550,550,600,500,550,550,600,500,550,1600,550,550,550,550,550,1550,600,500,600,500,600,500,600,1550,600,500,600,1550,600,1550,550,550,600,1550,550,1600,550,1600,550,};
irsend.sendRaw(raw,200,38);
delay(200);
Serial.println(F(("Temperatura: 24 graus.")));
  }

  if(c == 'i') //i = 25
  {
unsigned int raw[200] = {4400,4350,550,1550,600,500,600,1550,650,1500,600,500,600,500,600,1550,600,500,600,500,600,1550,600,500,600,500,600,1550,600,1550,550,550,550,1550,600,500,600,500,600,500,600,1550,600,1550,600,1550,600,1550,600,1550,600,1550,600,1550,550,1550,600,500,650,450,600,500,600,500,600,500,650,1500,600,1550,600,500,600,500,600,1550,600,500,600,500,600,500,600,500,600,500,600,1550,600,1550,550,550,600,1500,600,1550,600,1550,600,5200,4400,4350,550,1550,600,500,600,1550,600,1550,600,500,600,500,600,1550,600,500,600,500,600,1550,600,500,600,500,600,1550,600,1550,550,550,550,1550,650,450,600,500,650,450,600,1550,600,1550,600,1550,600,1550,600,1550,600,1550,600,1550,600,1500,600,550,550,500,600,500,600,500,600,500,600,1550,600,1550,600,500,600,500,600,1550,600,500,600,500,600,500,600,500,600,500,600,1550,600,1550,550,550,600,1550,550,1550,600,1550,600,};
irsend.sendRaw(raw,200,38);
delay(200);
Serial.println(F(("Temperatura: 25 graus.")));
  }

  if(c == 'j') //j =26
  {
unsigned int raw[200] = {4400,4350,550,1550,600,500,600,1550,600,1550,600,500,600,500,600,1550,600,500,600,500,600,1550,600,500,600,500,600,1550,550,1550,600,500,600,1550,600,500,600,500,600,500,600,1550,600,1550,600,1550,600,1550,600,1550,600,1550,550,1600,550,1550,600,500,600,500,600,500,600,500,600,500,600,1550,600,1550,600,500,600,1550,600,1550,600,500,600,500,600,500,600,500,600,500,550,1600,550,550,550,550,550,1550,600,1550,600,1550,600,5200,4400,4350,550,1550,600,550,550,1550,600,1550,600,500,600,550,550,1550,600,500,600,500,600,1550,600,500,600,500,600,1550,600,1550,550,550,550,1550,600,550,550,550,550,550,550,1550,600,1550,600,1550,600,1550,600,1550,600,1550,600,1550,550,1550,600,550,550,550,550,550,550,550,550,550,550,1550,600,1550,600,550,550,1550,600,1550,600,500,600,500,600,500,600,500,600,500,550,1600,550,550,550,550,550,1550,600,1550,600,1550,600,};
irsend.sendRaw(raw,200,38);
delay(200);
Serial.println(F(("Temperatura: 26 graus.")));
  }
/*
  if(c == 'k') //27 
  {
unsigned int raw[200] = {4400,4300,600,1550,650,450,600,1550,600,1550,550,600,450,650,500,1600,550,550,550,550,550,1600,500,600,500,600,550,1600,600,1500,650,500,550,1550,600,500,600,500,600,500,600,1550,550,1600,600,1500,650,1550,600,1550,600,1550,600,1550,550,1550,600,500,600,500,600,500,600,500,600,500,550,1650,500,600,500,550,550,1650,500,1600,500,600,550,550,550,550,550,550,550,1550,650,1550,500,600,500,600,500,1650,500,1600,500,1650,550,5200,4400,4400,500,1650,550,500,600,1550,600,1550,550,550,550,550,550,1600,550,550,550,550,550,1600,550,550,550,550,500,1650,550,1600,550,500,600,1550,600,500,600,500,650,450,650,1500,550,1600,600,1550,600,1550,600,1550,600,1500,550,1650,500,1600,550,600,550,550,550,500,550,550,600,500,600,1550,550,550,550,550,600,1550,550,1600,600,500,600,500,600,500,600,500,550,1600,550,1550,600,550,550,550,550,1550,650,1500,600,1550,600,};
irsend.sendRaw(raw,200,38);
delay(200);
Serial.println(F(("Temperatura: 27 graus.")));
  }

    if(c == 'l') //28
  {
unsigned int raw[200] = {4400,4350,600,1550,600,500,600,1550,550,1600,550,550,550,500,600,1550,600,500,600,500,600,1550,600,500,600,500,600,1550,600,1550,600,500,600,1550,600,500,600,500,600,500,600,1550,550,1550,600,1550,600,1550,600,1550,600,1550,600,1550,600,1550,600,500,600,500,600,500,600,500,600,500,600,1550,550,550,550,1550,600,500,600,1550,600,500,600,500,600,500,600,500,600,1550,600,500,600,1550,600,500,600,1550,600,1550,600,1550,550,5200,4400,4350,600,1550,600,500,600,1550,600,1550,550,550,550,550,550,1550,600,500,600,500,600,1550,600,500,600,500,600,1550,600,1550,600,500,600,1550,600,500,600,500,600,500,600,1550,600,1550,550,1550,600,1550,600,1550,600,1550,600,1550,600,1550,600,500,600,500,600,500,600,500,600,500,600,1550,600,500,600,1500,600,550,550,1550,600,500,600,500,600,500,600,500,600,1550,600,500,600,1550,600,500,600,1550,600,1550,600,1550,600,};
irsend.sendRaw(raw,200,38);
delay(200);
Serial.println(F(("Temperatura: 28 graus.")));
  }

    if(c == 'm') //29
  {
unsigned int raw[200] = {4400,4350,550,1550,600,500,600,1550,600,1550,600,500,650,450,600,1550,600,500,600,500,600,1550,600,500,600,500,600,1550,600,1550,600,500,550,1550,600,500,600,500,600,500,600,1550,600,1550,600,1550,600,1550,600,1550,600,1550,600,1550,600,1550,550,500,600,550,550,500,600,500,600,500,600,1550,600,500,650,1500,600,1550,600,1550,600,500,600,500,600,500,600,500,600,1550,600,500,600,500,600,500,550,1550,600,1550,600,1550,600,5200,4400,4350,600,1550,600,450,600,1550,600,1550,600,500,600,500,600,1550,650,450,600,500,600,1550,600,500,600,500,600,1550,600,1550,600,500,550,1550,600,500,600,500,600,500,650,1500,600,1550,600,1550,600,1550,600,1550,600,1550,600,1550,600,1550,600,500,550,550,550,550,550,500,600,500,600,1550,600,500,600,1550,600,1550,600,1550,600,500,600,500,600,500,600,500,600,1550,600,500,600,500,600,500,600,1550,550,1550,600,1550,600,};
irsend.sendRaw(raw,200,38);
delay(200);
Serial.println(F(("Temperatura: 29 graus.")));
  }
  */
  if(c == 'z') //z = desligou
  {
unsigned int raw[200] = {4450,4250,600,1550,600,500,600,1550,600,1550,600,500,600,500,600,1550,600,500,600,500,600,1550,600,500,600,500,550,1600,550,1550,600,500,600,1550,600,500,650,1500,600,1550,600,1550,600,1550,600,500,600,1550,600,1550,600,1550,550,550,550,500,600,500,600,500,600,1550,600,500,600,500,600,1550,600,1550,600,1550,600,500,600,500,600,500,600,500,600,500,600,500,600,500,600,500,600,1550,600,1550,550,1600,550,1550,600,1550,600,5200,4400,4350,550,1600,550,550,550,1550,600,1550,600,500,600,500,600,1550,600,500,600,500,600,1550,600,500,600,500,600,1550,600,1550,600,500,550,1600,550,550,550,1550,600,1550,600,1550,600,1550,600,500,600,1550,600,1550,600,1550,600,500,600,500,600,500,600,500,600,1550,550,550,550,550,550,1550,600,1550,600,1550,600,500,600,500,600,500,600,500,600,500,600,550,550,500,600,550,550,1550,600,1550,600,1550,550,1600,550,1550,600,};
irsend.sendRaw(raw,200,38);
delay(200);
Serial.println(F(("Desligado.")));
  }


}
}
//}








/*
void dump(decode_results *results) {
  int count = results->rawlen;
  Serial.println(c);
  c++;
  Serial.println("For IR Scope: ");
  for (int i = 1; i < count; i++) {
   
  if ((i % 2) == 1) {
    Serial.print("+");
    Serial.print(results->rawbuf[i]*USECPERTICK, DEC);
  }
  else {
    Serial.print(-(int)results->rawbuf[i]*USECPERTICK, DEC);
  }
  Serial.print(" ");
  }
  Serial.println("");
  Serial.println("For Arduino sketch: ");
  Serial.print("unsigned int raw[");
  Serial.print(count, DEC);
  Serial.print("] = {");
  for (int i = 1; i < count; i++) {
   
  if ((i % 2) == 1) {
    Serial.print(results->rawbuf[i]*USECPERTICK, DEC);
  }
  else {
    Serial.print((int)results->rawbuf[i]*USECPERTICK, DEC);
  }
  
  Serial.print(",");
  }
  Serial.print("};");
  Serial.println("");
  Serial.print("irsend.sendRaw(raw,");
  Serial.print(count, DEC);
  Serial.print(",38);");
  Serial.println("");
  Serial.println("");
}
*/
