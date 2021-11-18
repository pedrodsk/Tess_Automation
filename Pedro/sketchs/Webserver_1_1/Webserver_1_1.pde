/* Web Server
*
* A simple web server example using the WiShield 2.0
* that displays Hello World on a web page
*/
 
#include <WiShield.h>
 
#define WIRELESS_MODE_INFRA 1
#define WIRELESS_MODE_ADHOC 2
 
// Wireless configuration parameters ----------------------------------------
unsigned char local_ip[] = {10,0,0,60}; // IP address of WiShield
unsigned char gateway_ip[] = {10,0,0,50}; // router or gateway IP address
unsigned char subnet_mask[] = {255,255,255,0}; // subnet mask for the local network
const prog_char ssid[] PROGMEM = {"LIEC_WIFI"}; // max 32 bytes
 
unsigned char security_type = 3; // 0 - open; 1 - WEP; 2 - WPA; 3 - WPA2
 
// WPA/WPA2 passphrase
const prog_char security_passphrase[] PROGMEM = {"LIEC_123"};
 
// setup the wireless mode
// infrastructure - connect to AP
// adhoc - connect to another WiFi device
unsigned char wireless_mode = WIRELESS_MODE_INFRA;
 
// WEP 128-bit keys
// sample HEX keys
prog_uchar wep_keys[] PROGMEM = { 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, // Key 0
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // Key 1
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // Key 2
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 // Key 3
};
 
unsigned char ssid_len;
unsigned char security_passphrase_len;
//---------------------------------------------------------------------------
 
// This is the webpage that is served up by the webserver
const prog_char webpage[] PROGMEM = "HTTP/1.1 200 OK\r\nContent-Type:text/html\r\n\r\n"
"<html><body style=\"margin:100px\">"
"<h1>Teste</h1>"
"<table>"

"<tr>"
"<td><a href=/L1>Ligar 1</a></td>"
"<td><a href=/D1>Desligar 1</a></td>"
"</tr>"

"<tr>"
"<td><a href=/L2>Ligar 2</a></td>"
"<td><a href=/D2>Desligar 2</a></td>"
"</tr>"

"<tr>"
"<td><a href=/L2>Ligar 3</a></td>"
"<td><a href=/D2>Desligar 3</a></td>"
"</tr>"

"</table>"
"</body></html>";
 
void setup()
{
    WiFi.init();
}
 
void loop()
{
    WiFi.run();
}
