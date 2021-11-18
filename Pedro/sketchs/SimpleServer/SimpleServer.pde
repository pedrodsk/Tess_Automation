/*
 * A simple sketch that uses WiServer to serve a web page
 */

#include <WiServer.h>

#define WIRELESS_MODE_INFRA	1
#define WIRELESS_MODE_ADHOC	2
 
#define Status_Lampada_1 3
#define Status_Lampada_2 4
#define Status_Lampada_3 5

#define Aciona_rele_1 6 
#define Aciona_rele_2 7
#define Aciona_rele_3 8

boolean Status_lampadas[3] = {0,0,0};
boolean saida_rele[3] = {0,0,0};


// Wireless configuration parameters ----------------------------------------
unsigned char local_ip[] = {10,0,0,30};	// IP address of WiShield
unsigned char gateway_ip[] = {10,0,0,50};	// router or gateway IP address
unsigned char subnet_mask[] = {255,255,255,0};	// subnet mask for the local network
const prog_char ssid[] PROGMEM = {"LIEC_WIFI"}; // max 32 bytes
 
unsigned char security_type = 3; // 0 - open; 1 - WEP; 2 - WPA; 3 - WPA2
 
// WPA/WPA2 passphrase
const prog_char security_passphrase[] PROGMEM = {"LIEC_123"};

// WEP 128-bit keys
// sample HEX keys
prog_uchar wep_keys[] PROGMEM = { 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d,	// Key 0
				  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,	// Key 1
				  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,	// Key 2
				  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00	// Key 3
				};

// setup the wireless mode
// infrastructure - connect to AP
// adhoc - connect to another WiFi device
unsigned char wireless_mode = WIRELESS_MODE_INFRA;

unsigned char ssid_len;
unsigned char security_passphrase_len;
// End of wireless configuration parameters ----------------------------------------


// This is our page serving function that generates web pages
boolean sendMyPage(char* URL) {
    // Check if the requested URL matches "/" 
   // Serial.print("URL = ");
  //  Serial.println(URL);
    
    if (strcmp(URL, "/") == 0) {
        
        // Use WiServer's print and println functions to write out the page content
        WiServer.print("<html><head><META charset=UTF-8><META HTTP-EQUIV=refresh CONTENT=1><title>LIEC</title></head> <body style=\"margin:100px\"> <h1>EMBEDDED-LIEC</h1> <html> <table> <td>Lâmpada</td> <td>Acionamento</td> <td>Estado</td> <tr> <td>1</td>");
        
        WiServer.print("<td><a href=/L1>Ligar 5</a></td>");
        if(Status_lampadas[0] == 0)
          WiServer.print("<td>Desligado</td>");
        else
          WiServer.print("<td>Ligado</td>");
          
        WiServer.print("<tr> <td>2</td>");
        
        WiServer.print("<td><a href=/L2>Ligar 2</a></td>");
        if(Status_lampadas[1] == 0)
          WiServer.print("<td>Desligado</td>");
        else
          WiServer.print("<td>Ligado</td>");
          
        WiServer.print("<tr><td>3</td>");
        WiServer.print("<td><a href=/L3>Ligar 3</a></td>");
        if(Status_lampadas[2] == 0)
          WiServer.print("<td>Desligado</td>");
        else
          WiServer.print("<td>Ligado</td>");
          
        WiServer.print("</body></html>");
        
        // URL was recognized
        return true;
    }
    // URL not found
    return false;
}


void setup() {
  
  //Configura pinos de saída do relé
  pinMode(Aciona_rele_1,OUTPUT);
  pinMode(Aciona_rele_2,OUTPUT);
  pinMode(Aciona_rele_3,OUTPUT);
  pinMode(14,OUTPUT);
  //Configura pinos de leitura do status da lâmpada
  pinMode(Status_Lampada_1,INPUT);
  pinMode(Status_Lampada_2,INPUT);
  pinMode(Status_Lampada_3,INPUT);
);
  // Initialize WiServer and have it use the sendMyPage function to serve pages  
  WiServer.init(sendMyPage);
  // Enable Serial output and ask WiServer to generate log messages (optional)
  WiServer.enableVerboseMode(true);
  digitalWrite(14,HIGH);
}


void loop(){

  // Run WiServer
  WiServer.server_task();
  //Faz a leitura das entradas das lâmpadas
  Status_lampadas[0] = digitalRead(Status_Lampada_1);
  Status_lampadas[1] = digitalRead(Status_Lampada_2);
  Status_lampadas[2] = digitalRead(Status_Lampada_3);
  
  //Gera as saídas dos relés
  digitalWrite(Aciona_rele_1,saida_rele[0]);
  digitalWrite(Aciona_rele_2,saida_rele[1]);
  digitalWrite(Aciona_rele_2,saida_rele[2]);
  
  delay(10);
}

