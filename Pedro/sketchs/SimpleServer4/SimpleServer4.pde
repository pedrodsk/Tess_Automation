/*
 * A simple sketch that uses WiServer to serve a web page
 */


#include <WiServer.h>
//#include <String.h>
#define WIRELESS_MODE_INFRA	1
#define WIRELESS_MODE_ADHOC	
#define botao_ligar 7
// Wireless configuration parameters ----------------------------------------
unsigned char local_ip[] = {10,0,0,40};	// IP address of WiShield
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
    if (strcmp(URL, "/") == 0) {
        // Use WiServer's print and println functions to write out the page content
//        WiServer.print("HTTP/1.1 200 OK\r\nContent-Type:text/html\r\n\r\n");
        WiServer.print("<html><body style=\"margin:100px\">");
        WiServer.print("<h1>Teste</h1>");
        WiServer.print("<html>");
        WiServer.print("<table><tr>");
        
        if(digitalRead(botao_ligar) == 1)
          WiServer.print("<td><a href=/L>Ligar 1</a></td>");
        else
          WiServer.print("<td><a href=/L>Funciona</a></td>");
          
        WiServer.print("<td><a href=/D1>Desligar 1</a></td>");
        WiServer.print("</tr>");
        WiServer.print("<tr>");
        WiServer.print("<td><a href=/L2>Ligar 2</a></td>");
        WiServer.print("<td><a href=/D2>Desligar 2</a></td>");
        WiServer.print("</tr>");
        WiServer.print("<tr>");
        WiServer.print("<td><a href=/L2>Ligar 3</a></td>");
        WiServer.print("<td><a href=/D2>Desligar 3</a></td>");
        WiServer.print("</tr>");
        WiServer.print("</table>");
        WiServer.print("<META HTTP-EQUIV=refresh CONTENT=0.5>");
        WiServer.print("</body></html>");
        
        // URL was recognized
        return true;
    }
    // URL not found
    return false;
}


void setup() {
  // Initialize WiServer and have it use the sendMyPage function to serve pages
  WiServer.init(sendMyPage);
  pinMode(botao_ligar,INPUT);
  digitalWrite(botao_ligar, HIGH);
  
  // Enable Serial output and ask WiServer to generate log messages (optional)
  Serial.begin(57600);
  WiServer.enableVerboseMode(true);
}

void loop(){

  // Run WiServer
  WiServer.server_task();
  //Serial.println(botao_ligar);
  

  delay(10);
}

