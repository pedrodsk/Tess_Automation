/* Bibliotecas */
#include <WiServer.h>
//#include <g2100.h>
//void stack_init(void);
//void stack_process(void);
/* Fim Bibliotecas */

/* Define */
#define WIRELESS_MODE_INFRA	1
#define WIRELESS_MODE_ADHOC	2
#define Status_Lampada_1 4
//#define Status_Lampada_2 5
//#define Status_Lampada_3 6
#define Aciona_rele_1 5
//#define Aciona_rele_2 8
//#define Aciona_rele_3 9
#define ledDebug 14
/* Fim Define */

/* Configuração de rede. */
unsigned char local_ip[] = {192,168,1,41};	// IP address of WiShield
unsigned char gateway_ip[] = {192,168,1,1};	// router or gateway IP address
unsigned char subnet_mask[] = {255,255,255,0};	// subnet mask for the local network
const prog_char ssid[] PROGMEM = {"GUIMARAES"}; // max 32 bytes
unsigned char security_type = 3; // 0 - open; 1 - WEP; 2 - WPA; 3 - WPA2
// WPA/WPA2 passphrase
const prog_char security_passphrase[] PROGMEM = {"GUIMARAES"};
// WEP 128-bit keys
// sample HEX keys
prog_uchar wep_keys[] PROGMEM = { 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d,	// Key 0
				  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,	// Key 1
				  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,	// Key 2
				  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00	// Key 3
				};

//unsigned char base64Chars[65];
unsigned char wireless_mode = WIRELESS_MODE_INFRA;
unsigned char ssid_len;
unsigned char security_passphrase_len;
/* Fim Configuração de rede. */

void printData(char* data, int len) {
  
  // Print the data returned by the server
  // Note that the data is not null-terminated, may be broken up into smaller packets, and 
  // includes the HTTP header. 
  while (len-- > 0) {
    Serial.print(*(data++));
  } 
}



boolean sendMyPage(char* URL) {

    
} //fim do sendpage

//client
uint8 ip[] = {192,168,1,10};
GETrequest testeCliente(ip, 23, "www.weather.gov", "/data/METAR/KLAX.1.txt");

void setup() {
  // Initialize WiServer and have it use the sendMyPage function to serve pages
  pinMode(ledDebug, OUTPUT);
  digitalWrite(ledDebug,HIGH);
  //WiServer.init(NULL);
  WiServer.init(sendMyPage);
  testeCliente.setReturnFunc(printData);
 //test.print_P(const char[]);
  
  
  // Enable Serial output and ask WiServer to generate log messages (optional)
  Serial.begin(57600);
  //WiServer.enableVerboseMode(true);
}

void loop(){

  // Run WiServer
  
  //testeCliente.submit();
  WiServer.server_task();
  
//  delay(10);
}
//char getChar(int nibble) {
//	return pgm_read_byte(base64Chars + nibble);
//}
