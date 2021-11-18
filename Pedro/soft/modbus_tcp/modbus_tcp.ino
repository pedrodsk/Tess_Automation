#include <SPI.h>
#include <Ethernet.h>
#include "Mudbus.h"

//#define DEBUG
#define c1 4 //carga 1
#define c2 5 //carga 2
#define c3 6 //carga 3


Mudbus Mb; //classe
int tempo = 500; //definição de um tempo

void setup()
{
  uint8_t mac[]     = { 0x90, 0xA2, 0xDA, 0x00, 0x51, 0x06 }; //mac
  uint8_t ip[]      = { 10, 0, 0, 60 }; //ip
  uint8_t gateway[] = { 10, 0, 0, 1 }; //gateway
  uint8_t subnet[]  = { 255, 255, 255, 0 }; //mascara
  Ethernet.begin(mac, ip, gateway, subnet); //inicia ethernet
  Serial.begin(9600);
  //Avoid pins 4,10,11,12,13 when using ethernet shield

  delay(5000);  //Time to open the terminal
  Serial.begin(9600);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(9, INPUT);
  digitalWrite(9, LOW);
}

void loop()
{
  Mb.Run();
  int x =  Mb.C[0];
  int y =  Mb.C[1];
  int z =  Mb.C[2];

 // Mb.R[2] = 800;
  //Mb.R[0] = 5;
 // Mb.R[1] = 200;
//  int x = Mb.R[0];
//  Serial.println(x); meu debug
  if(x==1){
digitalWrite(c1,HIGH);
Serial.println(F("Carga 1 ligada."));
delay(tempo);  
  }
  if(x==0){
digitalWrite(c1,LOW);
Serial.println(F("Carga 1 desligada."));
delay(tempo);
    }
    
  if(y==1){
digitalWrite(c2,HIGH);
Serial.println(F("Carga 2 ligada."));
delay(tempo);
  }
  if(y==0){
digitalWrite(c2,LOW);
Serial.println(F("Carga 2 desligada."));
delay(tempo);
    }
    
  if(z==1){
digitalWrite(c3,HIGH);
Serial.println(F("Carga 3 ligada."));
delay(tempo);
  }
  if(z==0){
digitalWrite(c3,LOW);
Serial.println(F("Carga 3 desligada."));
delay(tempo);
    }
}// fim do loop

/*
Modpoll commands
  Read the registers Mb.R[0], Mb.R[1], and Mb.R[2]
    ./modpoll -m tcp -t4 -r 1 -c 3 192.168.1.8
  Read the coil Mb.C[0]
    ./modpoll -m tcp -t0 -r 1 -c 1 192.168.1.80        


//Function codes 1(read coils), 3(read registers), 5(write coil), 6(write register)
//signed int Mb.R[0 to 125] and bool Mb.C[0 to 128] MB_N_R MB_N_C
//Port 502 (defined in Mudbus.h) MB_PORT

/*
A minimal Modbus TCP slave for Arduino. 
It has function codes 

Read coils (FC 1) 0x
Read input discretes (FC 2) 1x
Read multiple registers (FC 3) 4x
Read input registers (FC 4) 3x
Write coil (FC 5) 0x
Write single register (FC 6) 4x
Force multiple coils (FC 15) 0x
Write multiple registers (FC 16) 4x

It is set up to use as a library, 
so the Modbus related stuff is 
separate from the main sketch. 
  
 Mb.C[0-63] bool  
 Digital outputs
 
 Mb.I[0-63] bool 
 Digital inputs
 
 Mb.IR[0-15] signed int 
 Input registers (for AD converters, counters etc)
 
 Mb.R[0-15] signed int 
 Holding registers (for DA converters, frequency outputs etc)

 Modpoll commands
 
 Read the registers Mb.R[3], Mb.R[4], and Mb.R[5]
 ./modpoll -m tcp -t4 -r 4 -c 6 192.168.1.8
 
 
 Usage

Usage: modpoll [options] serialport|host
Arguments:
serialport    Serial port when using Modbus ASCII or Modbus RTU protocol
              COM1, COM2 ...                on Windows
              /dev/ttyS0, /dev/ttyS1 ...    on Linux
              /dev/ser1, /dev/ser2 ...      on QNX
host          Host name or dotted ip address when using MODBUS/TCP protocol
General options:
-m ascii      Modbus ASCII protocol
-m rtu        Modbus RTU protocol (default)
-m tcp        MODBUS/TCP protocol
-m enc        Encapsulated Modbus RTU over TCP
-a #          Slave address (1-255, 1 is default)
-r #          Start reference (1-65536, 100 is default)
-c #          Number of values to poll (1-100, 1 is default)
-t 0          Discrete output (coil) data type
-t 1          Discrete input data type
-t 3          16-bit input register data type
-t 3:hex      16-bit input register data type with hex display
-t 3:int      32-bit integer data type in input register table
-t 3:mod      32-bit module 10000 data type in input register table
-t 3:float    32-bit float data type in input register table
-t 4          16-bit output (holding) register data type (default)
-t 4:hex      16-bit output (holding) register data type with hex display
-t 4:int      32-bit integer data type in output (holding) register table
-t 4:mod      32-bit module 10000 type in output (holding) register table
-t 4:float    32-bit float data type in output (holding) register table
-i            Slave operates on big-endian 32-bit integers
-f            Slave operates on big-endian 32-bit floats
-1            Poll only once, otherwise poll every second
-e            Use Daniel/Enron single register 32-bit mode
-0            First reference is 0 (PDU addressing) instead 1
Options for MODBUS/TCP:
-p #          TCP port number (502 is default)
Options for Modbus ASCII and Modbus RTU:
-b #          Baudrate (e.g. 9600, 19200, ...) (9600 is default)
-d #          Databits (7 or 8 for ASCII protocol, 8 for RTU)
-s #          Stopbits (1 or 2, 1 is default)
-p none       No parity
-p even       Even parity (default)
-p odd        Odd parity
-4 #          RS-485 mode, RTS on while transmitting and another # ms after
-o #          Time-out in seconds (0.01 - 10.0, 1.0 s is default)
Usage Examples

To get help on usage run the following command:
modpoll -h
To retrieve continuously 10 Modbus holding registers starting from reference 500 of slave ID number 5 with Modbus RTU at 19200 baud, no parity on COM1 run:
modpoll -b 19200 -p none -m rtu -a 3 -r 500 -c 10 COM1
To retrieve once 5 floating point values starting from reference 100 with Modbus/TCP from slave device with IP 10.0.0.100:
modpoll -m tcp -t4:float -r 100 -c 5 -1 10.0.0.100
Details

Download	
modpoll.3.4.zip	modpoll.3.4.zip
System Requirements	modpoll runs on Windows XP, 2000, NT, 98, Linux kernel 2.6 or 2.4, QNX Neutrino 6 (x86) and Solaris (SPARC).
License	This program is freeware; you can use it and redistribute it under the terms of the accompanying License document LICENSE-FREE.

 */

