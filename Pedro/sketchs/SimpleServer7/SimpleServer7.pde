/* Bibliotecas */
#include <WiServer.h>

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
unsigned char local_ip[] = {10,0,0,41};	// IP
unsigned char gateway_ip[] = {10,0,0,50};	//  gateway IP
unsigned char subnet_mask[] = {255,255,255,0};	// mask
const prog_char ssid[] PROGMEM = {"LIEC_WIFI"}; // ssid da rede
unsigned char security_type = 3; // 0 - open; 1 - WEP; 2 - WPA; 3 - WPA2
// WPA/WPA2 passphrase
const prog_char security_passphrase[] PROGMEM = {"LIEC_123"}; // senha
// WEP 128-bit keys
// sample HEX keys
prog_uchar wep_keys[] PROGMEM = { 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d,	// Key 0
				  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,	// Key 1
				  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,	// Key 2
				  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00	// Key 3
				};


unsigned char wireless_mode = WIRELESS_MODE_INFRA;
unsigned char ssid_len;
unsigned char security_passphrase_len;
/* Fim Configuração de rede. */

boolean sendMyPage(char* URL) {
 
   // if (strcmp(URL, "/") == 0 || strcmp(URL, "/l1?") == 0 || strcmp(URL, "/l2?") == 0 || strcmp(URL, "/l3?") == 0 || strcmp(URL, "/d1?") == 0 || strcmp(URL, "/d2?") == 0 || strcmp(URL, "/d3?") == 0  ) {
   if (strcmp(URL, "/") == 0){ 
        paginaHtml();
        return true;
    }
      
    if (strcmp(URL, "/l1?") == 0) {//caso o GET seja igual a /l1, energiza relé e led.
     // WiServer.print("HTTP/1.1 200 OK\r\nContent-Type:text/html\r\n\r\n");
      WiServer.print("<html><META HTTP-EQUIV=REFRESH CONTENT=0.1;URL=/></html>"); //atualiza a pagina.
      digitalWrite(Aciona_rele_1,HIGH); //aciona relé.
      digitalWrite(ledDebug,HIGH); // aciona led de teste.
      
       
      return true;
    if (strcmp(URL, "/d1?") == 0) {//caso o GET seja igual a /d1, desenergiza relé e led.
     // WiServer.print("HTTP/1.1 200 OK\r\nContent-Type:text/html\r\n\r\n");
      WiServer.print("<html><META HTTP-EQUIV=REFRESH CONTENT=0.1;URL=/></html>");
      digitalWrite(ledDebug,LOW);
      digitalWrite(Aciona_rele_1,LOW);
     // WiServer.print("<html><META HTTP-EQUIV=REFRESH CONTENT=2;URL=/></html>");
       
      return true;
    }
      // URL not found
     return false;
    
} //fim do sendpage
   }

void setup() {
  // Initialize WiServer and have it use the sendMyPage function to serve pages
  pinMode(ledDebug, OUTPUT);
  digitalWrite(ledDebug,HIGH);
  WiServer.init(sendMyPage);
   digitalWrite(ledDebug,LOW);
  pinMode(Status_Lampada_1, INPUT);
  pinMode(Status_Lampada_1, HIGH);
  pinMode(Aciona_rele_1, OUTPUT);
  Serial.begin(57600);
  WiServer.enableVerboseMode(true);
}

void loop(){

  WiServer.server_task();
    delay(10);
}
//funções
//paginaHtml
void paginaHtml() {
        WiServer.print("<html>");
        WiServer.print("<h2>LIEC - UFCG</h2>");
        WiServer.print("<table border=1>");
        
        if(digitalRead(Status_Lampada_1) == 0)
          WiServer.print("<tr><td><form method=\"get\" action=\"l1\">Lampada 1&nbsp;&nbsp;<input type=\"submit\" value=\"Ligar\"></input></form></td></tr>");
        else
          WiServer.print("<tr><td><form method=\"get\" action=\"d1\">Lampada 1&nbsp;&nbsp;<input type=\"submit\" value=\"Desligar\"></input></form></td></tr>");
        WiServer.print("</table>");
        WiServer.print("<META HTTP-EQUIV=refresh CONTENT=5;URL=/>");
        WiServer.print("</body></html>");
} //fim paginaHtml

