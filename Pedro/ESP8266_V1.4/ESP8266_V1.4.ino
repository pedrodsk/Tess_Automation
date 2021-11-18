/***************************************************************************
 * Descrição de funcionamento:                                             *                        
 * O sistema de controle de acionamento de cargas funciona a partir        *
 * de dados recebidos de um servidor via wifi ou quando acontece           *
 * alguma alteração no estado na carga(Carga sendo ligada ou desliga).     *
 * Este atua enviando dados ao servidor ou ligando e desligando as cargas  *
 *                                                                         *
 * Codigo Fonte desenvolvido por: Ricardo Soares Chinarro                  *
 * Data:16/08/2015                                                         *
 * Versão: V1.0                                                            *
 ***************************************************************************/
/******************************************************
 * Arquivos cabeçado necessarios para utilização de   * 
 * comparação de strings e leitura da memoria eeprom  *
 ******************************************************/
 //0A 2E 00 2E 00 2E 0D 02 01
#include <EEPROM.h>
#include <string.h>
#include <IRremote.h>
/* Define os pinos a serem utilizados*/
#define modo_configura_ou_funciona 12

/*enderecos da memoria eeprom*/
#define endereco_ssid 1
#define endereco_senha 16
#define endereco_ip_local 48
#define endereco_ip_servidor 64

/*Define pinos do microcontrolador*/
#define Status_Lampada_1 5
#define Status_Lampada_2 6
#define Status_Lampada_3 7

#define Aciona_rele_1 8 
#define Aciona_rele_2 9
#define Aciona_rele_3 10

#define RECV_PIN 11
IRrecv irrecv(RECV_PIN);
decode_results results;
IRsend irsend;

#define conexao_status 13
#define conexao_TCP_IP_status A0

//Declaração de variaveis
char recepcao_dados_modulo_wifi[30],caractere_imprimir = 0,dado_servidor[10];
int contador_caracteres = 0,ssid_senha_criptografia_IP = 0, tamanho_dado = 0,numero_caracteres = 0,flag_escolhas = 1,aux = 0;
int estado_das_lampadas = 0, IP_endereco[4],receber_dado = 0,IP_endereco_servidor[4];
boolean flag_recepcai_serial_completa = 0, modo = 0,envia_dado_ao_servidor = 0,envia_dados_servidor_mudanca_de_estado = 0;
boolean conexao_aberta = 0;
boolean rele_1 = 0,rele_2 = 0, rele_3 = 0, desliga_ar = 0, decodificacao_completa = 0;

void setup() {
  zera_dados_serial(recepcao_dados_modulo_wifi);
  // initialize both serial ports:
  Serial.begin(57600);
  /**************************************
   * Configuração das saídas do sistemas*
   **************************************/
  //Configura pinos de saída a relé
  pinMode(Aciona_rele_1,OUTPUT);
  pinMode(Aciona_rele_2,OUTPUT);
  pinMode(Aciona_rele_3,OUTPUT);
  pinMode(conexao_TCP_IP_status,OUTPUT);
  //Configura o pino 13 como saída digital para status de conexão completa
  pinMode(conexao_status, OUTPUT);
  //Configura o pino A0 como saída digital que é o status de conexão TCP_IP aberta pelo servidor
  pinMode(conexao_TCP_IP_status, OUTPUT);

  /*****************************************
   * Configuração das entradas do sistemas *
   *****************************************/
  //Configura pinos de leitura do status da lâmpada
  pinMode(Status_Lampada_1,INPUT);
  pinMode(Status_Lampada_2,INPUT);
  pinMode(Status_Lampada_3,INPUT);
  // Configura a entrada do jumper para selecionar modo configura ou run_mode
  pinMode(modo_configura_ou_funciona, INPUT_PULLUP);
  //Configura o pino 13 como saída para estatus de conexão completa
  pinMode(conexao_status, OUTPUT);
  
  /****************************************
   * Define o estado inicial das saídas ***
   ****************************************/
  pinMode(conexao_TCP_IP_status, OUTPUT);
  digitalWrite(conexao_status, LOW);
  digitalWrite(conexao_TCP_IP_status, HIGH);

  /********************************************
   * Verifica o estado dos relés e desliga    *
   * as saídas caso as mesmas estejam ligadas *
   ********************************************/
  if(digitalRead(Status_Lampada_1) == 1)
     rele_1 = !rele_1;
  if(digitalRead(Status_Lampada_2) == 1)
     rele_2 = !rele_2;
  if(digitalRead(Status_Lampada_3) == 1)
     rele_3 = !rele_3;
  /***************************
   * Desliga todas as cargas *
   ***************************/
  digitalWrite(Aciona_rele_1, rele_1);
  digitalWrite(Aciona_rele_2, rele_2);
  digitalWrite(Aciona_rele_3, rele_3);

  //Escolhe o modo de funcionamento a partir de um jumper na placa
  modo = digitalRead(modo_configura_ou_funciona);

  /**************************************************************
   * Faz a leitura dos endereços de IP salvos na memoria eeprom *
   * definidos pelo usuário previamente                         *
   **************************************************************/
  ajusta_endereco_de_ip(endereco_ip_local,IP_endereco);
  ajusta_endereco_de_ip(endereco_ip_servidor , IP_endereco_servidor);

  delay(1000);
  if(modo == 1){
      /****************************************************
       * Realiza a leitura do estado inicial das lâmpadas *
       ****************************************************/
      estado_das_lampadas = 0;
      estado_das_lampadas = (estado_das_lampadas|(0x01&digitalRead(Status_Lampada_3)))<<1;
      estado_das_lampadas = (estado_das_lampadas|(0x01&digitalRead(Status_Lampada_2)))<<1;
      estado_das_lampadas =  estado_das_lampadas|(0x01&digitalRead(Status_Lampada_1));
      /***********************************************
       * Inicia conexão com a rede wifi especificada *
       ***********************************************/
      Inicia_modulo_run_mode_ESP8266();
      }
  else
      /*******************************************
       * Inicia o modo de configuração do modulo *
       *******************************************/
      Inicia_configura_modulo_ESP8266();
}

void loop(){
  
  /*****************************************************
   * Verifica o Modo de funcionamento se é Run_mode ou *
   * modo de configuração                              *
   *****************************************************/
  if(modo == 1){// Run_mode
     leitura_estado_lampadas();
     run_mode();
     trata_dados_de_conexao();
     delay(100);
    }
  else// modo de configuração
     configura_modulo_ESP8266();
     
  
}

void(* resetFunc) (void) = 0; // Função pare reset via software

/********************************************
 * Tela inicial para o modo de configuração *
 ********************************************/
void Inicia_configura_modulo_ESP8266()
{    

  
     Serial.print(F("__________________________________________________\r\n")); 
     Serial.print(F("|                                                |\r\n"));
     Serial.print(F("|Bem Vindo ao modo de Configuracao do modulo Wifi|\r\n"));
     Serial.print(F("|Digite o numeral desejado                       |\r\n"));
     Serial.print(F("|[1] - SSID                                      |\n\r"));
     Serial.print(F("|[2] - Senha                                     |\n\r"));
     Serial.print(F("|[3] - IP do modulo                              |\n\r"));
     Serial.print(F("|[4] - IP do Servidor                            |\n\r"));
     Serial.print(F("|[5] - Configuracao ar condicionado              |\n\r"));
     Serial.print(F("|________________________________________________|\n\r"));
}

/*******************************************************************
 * Modo de configuração no qual o usuário faz as configurações de: *
 * SSID;                                                           *
 * Senha;                                                          *
 * IP do modulo;                                                   *
 * IP do Servidor;                                                 *
 * Recepção controle remoto ar condicionado.                       *
 *******************************************************************/
void configura_modulo_ESP8266()
{
    volatile int valor;
    volatile int endereco;
    
    if (Serial.available())
         trata_dados_serial();
         
    switch(flag_escolhas){
        case 1: 
          if (flag_recepcai_serial_completa == 1 && recepcao_dados_modulo_wifi[0] == '1'){
              Serial.print(F("Digite o SSID da rede\n\r"));
              flag_escolhas = 2;
              ssid_senha_criptografia_IP = 1;
              flag_recepcai_serial_completa = 0;
              }

          if (flag_recepcai_serial_completa == 1 && recepcao_dados_modulo_wifi[0] == '2'){
                Serial.print(F("\n\rDigite a Senha da rede\n\r"));
                flag_escolhas = 2; 
                ssid_senha_criptografia_IP = 2;
                flag_recepcai_serial_completa = 0;
                }
    
          if (flag_recepcai_serial_completa == 1 && recepcao_dados_modulo_wifi[0] == '3'){
                Serial.print(F("\n\rDigite o IP do modulo no seguinte formato\n\r"));
                Serial.print(F("\n\rExemplos 10.0.0.25\r\n 192.168.1.22\n\r"));
                flag_escolhas = 2;
                ssid_senha_criptografia_IP = 3;
                flag_recepcai_serial_completa = 0;
                }
           if (flag_recepcai_serial_completa == 1 && recepcao_dados_modulo_wifi[0] == '4'){
                Serial.print(F("\n\rDigite o IP do servidor\n\r"));
                Serial.print(F("\n\rExemplos 10.0.0.25\r\n192.168.1.22\n\r"));
                flag_escolhas = 2;
                ssid_senha_criptografia_IP = 4;
                flag_recepcai_serial_completa = 0;
                }
           if (flag_recepcai_serial_completa == 1 && recepcao_dados_modulo_wifi[0] == '5'){
                Serial.print(F("\n\rAponte o controle para o receptor infravermelho\n\r"));
                Serial.print(F("\n\rPressione o botão de desligar do controle remoto\n\r"));
                irrecv.enableIRIn(); // Start the receiver
                flag_escolhas = 2;
                ssid_senha_criptografia_IP = 5;
                flag_recepcai_serial_completa = 0;
                }
        break;
        case 2:
            if (flag_recepcai_serial_completa == 1 && ssid_senha_criptografia_IP == 1){
                  EEPROM.write(0,numero_caracteres);
                  endereco = endereco_ssid;
                  for(valor = 0; valor <= numero_caracteres; valor++, endereco++){
                      EEPROM.write(endereco,recepcao_dados_modulo_wifi[valor]);
                      }
                  flag_recepcai_serial_completa = 0;
                  ssid_senha_criptografia_IP = 0;
                  flag_escolhas = 1;
                  Serial.print(F("SSID gravado escolha uma nova opcao\n\r"));
                  }
             if (flag_recepcai_serial_completa == 1 && ssid_senha_criptografia_IP == 2){
                  EEPROM.write(15,numero_caracteres);
                  endereco = endereco_senha;
                  for(valor = 0; valor <= numero_caracteres; valor++, endereco++){
                      EEPROM.write(endereco,recepcao_dados_modulo_wifi[valor]);
                      }
                  flag_recepcai_serial_completa = 0;
                  ssid_senha_criptografia_IP = 0;
                  flag_escolhas = 1;
                  Serial.print(F("Senha gravada escolha uma nova opcao\n\r"));
                  }
             if (flag_recepcai_serial_completa == 1 && ssid_senha_criptografia_IP == 3){
                 endereco = endereco_ip_local;
                 EEPROM.write((endereco_ip_local - 1),numero_caracteres);
                 for(valor = 0; valor <= numero_caracteres; valor++, endereco++)
                      EEPROM.write(endereco,recepcao_dados_modulo_wifi[valor]);
                      
                  flag_recepcai_serial_completa = 0;
                  ssid_senha_criptografia_IP = 0;
                  flag_escolhas = 1;
                  Serial.print(F("Endereco de IP gravado escolha uma nova opcao\n\r"));
                  }
             if (flag_recepcai_serial_completa == 1 && ssid_senha_criptografia_IP == 4){
                 endereco = endereco_ip_servidor;
                 EEPROM.write((endereco_ip_servidor - 1),numero_caracteres);
                 for(valor = 0; valor <= numero_caracteres; valor++, endereco++)
                      EEPROM.write(endereco,recepcao_dados_modulo_wifi[valor]);
                      
                  flag_recepcai_serial_completa = 0;
                  ssid_senha_criptografia_IP = 0;
                  flag_escolhas = 1;
                  Serial.print(F("Endereco de IP do servidor definido\n\r"));
                  }
               if (/*irrecv.decode(&results) && */ssid_senha_criptografia_IP == 5) {
                   /* dump(&results);
                    irrecv.resume(); // Receive the next value
                    ssid_senha_criptografia_IP = 1;
                    flag_escolhas = 1;
                    Serial.print(F("Decodificação Completa\n\r"));*/
                    Serial.print(F("A ser implementado\n\r"));
                    }
          break;
        }
}

/*******************************************************************
 * Configura o módulo wifi ESP8266 e inicia a conexão com a rede   *                    
 * wifi abrinco a porta 502 para conexão com servidor              *
 *******************************************************************/

void Inicia_modulo_run_mode_ESP8266()
{ 
    int valor = 0;
    delay(10000);
    Serial.print (F("AT+RST\r\n"));// Faz um resete inicial no microcontrolador
    delay(10000);
    // Seta o módulo ESP8266 como station mode via comando AT
    Serial.print(F("AT+CWMODE=1\r\n"));
    zera_dados_serial(recepcao_dados_modulo_wifi);

    // Aguarda resposta valida do módulo ESP8266
    do{
        if (Serial.available()){
              trata_dados_serial();
        // Resposta ERROR reseta microcontrolador      
        if(strncmp("ERROR", recepcao_dados_modulo_wifi,5) == 0 && flag_recepcai_serial_completa == 1)
            resetFunc(); 
        }
    } while (strncmp("OK", recepcao_dados_modulo_wifi,2) !=0 || flag_recepcai_serial_completa == 0);

    delay(100);
    Serial.print(F("AT+CWDHCP=1,1\r\n"));//Habilita station mode Desabita o IP por DHCP
    
    zera_dados_serial(recepcao_dados_modulo_wifi);
    
     do{
        
        if (Serial.available())
              trata_dados_serial();
        // Resposta ERROR reseta microcontrolador  
        if(strncmp("ERROR", recepcao_dados_modulo_wifi,5) == 0 && flag_recepcai_serial_completa == 1)
            resetFunc(); 
      
    } while (strncmp("OK", recepcao_dados_modulo_wifi,2) !=0 || flag_recepcai_serial_completa == 0);
    
    delay(100);
    Serial.print(F("AT+CIPMUX=1\r\n"));// Seta oara múltiplas conexões
    
    zera_dados_serial(recepcao_dados_modulo_wifi);
    
    do{   
        if (Serial.available())
              trata_dados_serial();
        // Resposta ERROR reseta microcontrolador  
        if(strncmp("ERROR", recepcao_dados_modulo_wifi,5) == 0 && flag_recepcai_serial_completa == 1)
            resetFunc(); 
      
    } while (strncmp("OK", recepcao_dados_modulo_wifi,2) !=0 || flag_recepcai_serial_completa == 0);
    
    delay(100);
    Serial.print(F("AT+CIPSTA=\""));//Seta o endereço de Ip do modulo
    
    imprime_dados_eeprom(endereco_ip_local);
    
    Serial.print(F("\"\r\n"));
    
    zera_dados_serial(recepcao_dados_modulo_wifi);
    
    do{
          if (Serial.available())
              trata_dados_serial();
          // Resposta ERROR reseta microcontrolador  
          if(strncmp("ERROR", recepcao_dados_modulo_wifi,5) == 0 && flag_recepcai_serial_completa == 1)
              resetFunc();
              
    } while (strncmp("OK", recepcao_dados_modulo_wifi,2) !=0 || flag_recepcai_serial_completa == 0);
    delay(100);

     //Conecta na rede configurada
    Serial.print(F("AT+CWJAP=\""));    
    delay(25);
    
    imprime_dados_eeprom(endereco_ssid); 
    
    Serial.print(F("\",\""));
    
    imprime_dados_eeprom(endereco_senha);  
    
 
    Serial.print(F("\"\r\n"));

    zera_dados_serial(recepcao_dados_modulo_wifi);
    
    do{
          if (Serial.available())
              trata_dados_serial();
          // Resposta Fail reseta microcontrolador  
          if(strncmp("FAIL", recepcao_dados_modulo_wifi,4) == 0 && flag_recepcai_serial_completa == 1)
              resetFunc();
          // Resposta ERROR reseta microcontrolador  
          if(strncmp("ERROR", recepcao_dados_modulo_wifi,5) == 0 && flag_recepcai_serial_completa == 1)
              resetFunc(); 
              
    } while (strncmp("OK", recepcao_dados_modulo_wifi,2) !=0 || flag_recepcai_serial_completa == 0);
    
    delay(100);
        
    Serial.print("AT+CIPSERVER=1,502\r\n"); //Seta a porta de transmissão e recepção de dados

    zera_dados_serial(recepcao_dados_modulo_wifi);
    
    do{
          if (Serial.available())
              trata_dados_serial();
          // Resposta ERROR reseta microcontrolador  
          if(strncmp("ERROR", recepcao_dados_modulo_wifi,5) == 0 && flag_recepcai_serial_completa == 1)
              resetFunc();
              
    } while (strncmp("OK", recepcao_dados_modulo_wifi,2) !=0 || flag_recepcai_serial_completa == 0);

    delay(100);
    Serial.print("AT+CIPSERVER=1,502\r\n"); //Seta a porta de transmissão e recepção de dados

    zera_dados_serial(recepcao_dados_modulo_wifi);
    
    do{
          if (Serial.available())
              trata_dados_serial();
          // Resposta ERROR reseta microcontrolador  
          if(strncmp("ERROR", recepcao_dados_modulo_wifi,5) == 0 && flag_recepcai_serial_completa == 1)
              resetFunc();
              
    } while (strncmp("OK", recepcao_dados_modulo_wifi,2) !=0 || flag_recepcai_serial_completa == 0);
    
    /***********************************************************************
     * Liga led sinalizando que o termino da configuração foi bem sucedido *
     ***********************************************************************/
    digitalWrite(conexao_status, HIGH);  
    zera_dados_serial(recepcao_dados_modulo_wifi);      
}



void run_mode()
{
     int volatile valor = 0,contador_tentativas_de_conexao = 0;
     boolean erro_conexao = 0;
    //AT+CIPSTART=1,"TCP","10.0.0.10",23
    if(envia_dado_ao_servidor == 1 && conexao_aberta == 0){
      
       envia_dado_ao_servidor = 0;
       zera_dados_serial(recepcao_dados_modulo_wifi);
       
       Serial.print("AT+CIPSTART=1,\"TCP\",\"");
       
       imprime_dados_eeprom(endereco_ip_servidor);
       
       Serial.print(F("\""));
       
       delay(25);   
       
       Serial.print(F(",502\r\n"));
       
       delay(100);
       
       do{
         if (Serial.available())
              trata_dados_serial();
          if(strncmp("ERROR", recepcao_dados_modulo_wifi,5) == 0 && flag_recepcai_serial_completa == 1)
              {
                contador_tentativas_de_conexao++;
                Serial.print("AT+CIPSTART=1,\"TCP\",\"");
                imprime_dados_eeprom(endereco_ip_servidor);
                Serial.print(F("\""));
                delay(25);   
                Serial.print(F(",502\r\n"));
                delay(1000);
                zera_dados_serial(recepcao_dados_modulo_wifi);
              }
          if(contador_tentativas_de_conexao == 4){
             erro_conexao = 1;
             }
              
          }while ((strncmp("OK", recepcao_dados_modulo_wifi,2) !=0 || flag_recepcai_serial_completa == 0) && erro_conexao == 0);
          
          if (erro_conexao == 0){
          
              zera_dados_serial(recepcao_dados_modulo_wifi);
              delay(100);
              Serial.print("AT+CIPSEND=1,11\r\n");
          
              do{
                if (Serial.available())
                    trata_dados_serial();
                
                }while (strncmp("OK", recepcao_dados_modulo_wifi,2) !=0 || flag_recepcai_serial_completa == 0);
              
              zera_dados_serial(recepcao_dados_modulo_wifi);
              //Envia pacote de dados para o servidor
              imprime_endereco_de_ip_local(); //Endereco de IP
              Serial.print(1,HEX);//Comando
              leitura_estado_lampadas();
              Serial.print(estado_das_lampadas,HEX);//Estados das lampadas
              Serial.print("\r\n");//Final do Pacote
          
              do{
                if (Serial.available())
                    trata_dados_serial();
    
                }while (strncmp("SEND OK", recepcao_dados_modulo_wifi,7) !=0 || flag_recepcai_serial_completa == 0);
            
              zera_dados_serial(recepcao_dados_modulo_wifi);
              Serial.print("AT+CIPCLOSE=1\r\n");
              delay(100);

              do{
                if (Serial.available())
                    trata_dados_serial();
                if(strncmp("ERROR", recepcao_dados_modulo_wifi,5) == 0 && flag_recepcai_serial_completa == 1){
                    Serial.print("AT+CIPCLOSE=1\r\n");
                    zera_dados_serial(recepcao_dados_modulo_wifi);
                    delay(200);
                  }
                
                }while (strncmp("OK", recepcao_dados_modulo_wifi,2) !=0 || flag_recepcai_serial_completa == 0);
          }
          else{
            erro_conexao = 0;
            Serial.print("Erro Conexao\r\n");// Apenas para teste
            trata_erro_conexao();
            }
            
    }
}
/*************************************************
 * Realiza o tratamento dos dados recebidos pela *
 * porta serial                                  *
 *************************************************/
void trata_dados_serial()
{
  
  int cont = 0;
  if(contador_caracteres == 0)
     zera_dados_serial(recepcao_dados_modulo_wifi);

  recepcao_dados_modulo_wifi[contador_caracteres] = Serial.read();
  
  if(modo == 0)
    Serial.print(recepcao_dados_modulo_wifi[contador_caracteres]);
          
  if((recepcao_dados_modulo_wifi[contador_caracteres-1] == 13 && recepcao_dados_modulo_wifi[contador_caracteres] == 10 && receber_dado == 0) 
  || (conexao_aberta == 1 && recepcao_dados_modulo_wifi[contador_caracteres] == ':' && receber_dado == 0)||
  ((receber_dado == 1 && contador_caracteres == 9) || (receber_dado == 2 && contador_caracteres == 8))){// carriege return e Line feed ou : e recepção dado puro
      
      if(receber_dado == 1 || receber_dado == 2){
          for(cont = 0; cont <= contador_caracteres; cont++)
              dado_servidor[cont] = recepcao_dados_modulo_wifi[cont];
              
          }
            
      if (flag_escolhas == 2)
            numero_caracteres = contador_caracteres - 1;
     
      contador_caracteres = 0;
      flag_recepcai_serial_completa = 1;
      
      }
        else
          contador_caracteres++;
  
   if (contador_caracteres == 30)
       contador_caracteres = 0;
       

}
/*****************************************
 * Limpa array da utilizado para receber * 
 * os dados da porta serial              *
 *****************************************/
void zera_dados_serial(char array[])
{
  
  volatile int valor;

  for (valor = 0; valor < 30; valor++)
      array[valor] = 0;    

  contador_caracteres = 0;
  
  flag_recepcai_serial_completa = 0;

}
/*********************************************
 * Imprime os dados salvos na memoria eeprom *
 *********************************************/
void imprime_dados_eeprom(int endereco_eeprom)
{
    volatile int tam_dado = 0,valor = 0;
    tam_dado  = EEPROM.read(endereco_eeprom - 1);
    for(valor = 0;valor < tam_dado;valor++){
            caractere_imprimir = EEPROM.read(endereco_eeprom+valor);
            delay(25);
            Serial.print(caractere_imprimir);
            delay(25);
            }  
  
}
/***********************************************************
 * Faz a leitura do endereço de IP salvo na memoria EEprom *
 ***********************************************************/
void ajusta_endereco_de_ip(int endereco_eeprom, int endereco[])
{ 
    volatile int tam_dado = 0,valor = 0,aux = 0,conta_pontos = 0;
    
    tam_dado  = EEPROM.read(endereco_eeprom - 1);
    
    for(valor = 0; valor <= tam_dado; valor++){
        if (EEPROM.read(valor+endereco_eeprom) == '.' || (tam_dado - valor) == 0){
            if(aux == 3)
               endereco[conta_pontos] = ((EEPROM.read(endereco_eeprom+valor-3)-0x30)*100) + ((EEPROM.read(endereco_eeprom+valor-2)-0x30)*10) + (EEPROM.read(endereco_eeprom+valor-1)-0x30);
            else if(aux == 2)
               endereco[conta_pontos] = ((EEPROM.read(endereco_eeprom+valor-2)-0x30)*10) + (EEPROM.read(endereco_eeprom+valor-1)-0x30);
            else
               endereco[conta_pontos] = (EEPROM.read(endereco_eeprom+valor-1)-0x30);
            aux = 0;
            conta_pontos++;
         }
         else
            aux++;
    }    
}

void imprime_endereco_de_ip_local()
{

    volatile int valor;
    for(valor = 0; valor < 4; valor++){
        Serial.print(IP_endereco[valor],HEX);  
        if( valor < 3)
          Serial.print('.');
    }
}

/****************************
 * Faz a leitura das cargas *
 ****************************/
void leitura_estado_lampadas()
{

    if((((estado_das_lampadas&0x01)) != digitalRead(Status_Lampada_1)) ||(((estado_das_lampadas&0x02)>>1) != digitalRead(Status_Lampada_2)) || (((estado_das_lampadas&0x04)>>2) != digitalRead(Status_Lampada_3))){ 
            estado_das_lampadas = 0;
            envia_dado_ao_servidor = 1;
            estado_das_lampadas = (estado_das_lampadas|(0x01&digitalRead(Status_Lampada_3)))<<1;
            estado_das_lampadas = (estado_das_lampadas|(0x01&digitalRead(Status_Lampada_2)))<<1;
            estado_das_lampadas =  estado_das_lampadas|(0x01&digitalRead(Status_Lampada_1));
            }
        
}

void trata_erro_conexao()
{
  
}



void trata_dados_de_conexao()
{
  // Recebe os dados da porta serial
  if (Serial.available())
        trata_dados_serial();
  //Aguarda inicio da conexão TCP/IP         
  if(strncmp("0,CONNECT", recepcao_dados_modulo_wifi,9) == 0 && flag_recepcai_serial_completa == 1 && conexao_aberta == 0){
        digitalWrite(conexao_TCP_IP_status, LOW);
        conexao_aberta = 1;
        zera_dados_serial(recepcao_dados_modulo_wifi);
        }
   //Verifica o tamanho da palavra recebida pelo servidor     
  if(strncmp("+IPD,0,9:", recepcao_dados_modulo_wifi,8) == 0 && flag_recepcai_serial_completa == 1 && conexao_aberta == 1 && receber_dado == 0){
        receber_dado = 2;
        zera_dados_serial(recepcao_dados_modulo_wifi);
        }
  else  if(strncmp("+IPD,0,8:", recepcao_dados_modulo_wifi,8) == 0 && flag_recepcai_serial_completa == 1 && conexao_aberta == 1 && receber_dado == 0){
           receber_dado = 1;
           zera_dados_serial(recepcao_dados_modulo_wifi);
           }
  // Se o tamanho da palavra for correto recebe e trata os dados do servidor           
  if (((receber_dado == 1 || receber_dado == 2) && flag_recepcai_serial_completa == 1) && conexao_aberta == 1)
      {
        zera_dados_serial(recepcao_dados_modulo_wifi); 
        receber_dado = 0;
        //Verifica endereço servidor
        if(dado_servidor[0] == IP_endereco_servidor[0] && dado_servidor[2] == IP_endereco_servidor[1] && dado_servidor[4] == IP_endereco_servidor[2] && dado_servidor[6] == IP_endereco_servidor[3]){
              //Verifica Codigo de operação
              if(dado_servidor[7] == 0x00)
                 envia_dado_ao_servidor = 1;
              if(dado_servidor[7] == 0x01){
                    //Liga desliga relé de acordo com dado recebido
                    //Liga ou desliga relé 1 de acordo com a palavra recebida
                    if(((dado_servidor[8]&0x01) == 1)){
                      rele_1 = !rele_1;
                      digitalWrite(Aciona_rele_1,rele_1);
                      }
                    if(((dado_servidor[8]&0x02)>>1)== 1){
                      rele_2 = !rele_2;
                      digitalWrite(Aciona_rele_2,rele_2);
                      }
                    if(((dado_servidor[8]&0x04)>>2) == 1){
                      rele_3 = !rele_3;
                      digitalWrite(Aciona_rele_3,rele_3);
                      }
              }
              if(dado_servidor[7] == 0x02){
                      if(dado_servidor[8] == 0x02){
                          unsigned int raw[200] = {4450,4300,600,1550,600,500,600,1550,600,1550,600,500,600,500,600,1550,600,500,600,500,600,1550,550,550,550,550,550,1550,600,1550,600,500,600,1550,600,500,600,500,600,500,600,1550,600,1550,600,1550,600,1550,600,1550,550,1600,550,1550,600,1550,600,500,600,500,600,500,600,500,600,500,600,500,600,500,600,1550,600,500,600,1550,600,500,600,500,600,500,600,1550,600,1550,550,550,550,1550,600,500,600,1550,600,1550,600,1550,600,5200,4400,4300,600,1550,600,550,550,1550,600,1550,600,500,600,500,600,1550,600,500,600,500,600,1550,600,500,600,500,600,1550,550,1550,600,550,550,1550,600,550,550,550,550,550,550,1550,600,1550,600,1550,600,1550,600,1550,600,1550,550,1600,550,1600,550,550,550,550,550,550,550,550,550,550,550,550,550,500,600,1550,600,550,550,1550,600,500,600,550,550,500,600,1550,600,1550,600,500,600,1550,550,550,550,1550,600,1550,600,1550,600,};
                          irsend.sendRaw(raw,200,38);
                          digitalWrite(3, HIGH);
                          }
                     if(dado_servidor[8] == 0x03){
                          //Liga 23 graus
                          unsigned int raw[200] = {4400,4350,600,1550,600,500,550,1600,550,1550,600,500,600,500,650,1500,600,500,600,500,600,1550,600,500,600,500,600,1550,600,1550,600,500,600,1550,600,500,550,550,600,500,550,1550,600,1550,600,1550,600,1550,600,1550,600,1550,600,1550,600,1550,600,500,600,500,600,500,600,500,550,550,550,550,550,1550,600,500,600,1550,600,1550,600,500,600,500,600,500,600,1550,600,500,600,1550,600,500,600,500,600,1550,600,1550,550,1550,600,5200,4400,4350,600,1550,550,550,600,1550,550,1550,600,500,600,500,600,1550,600,500,600,500,600,1550,600,500,600,500,600,1550,600,1550,600,500,600,1550,600,500,600,500,550,550,550,1550,600,1550,600,1550,600,1550,600,1550,600,1550,600,1550,600,1550,600,500,600,500,550,550,600,500,550,550,550,550,550,1550,600,500,600,1550,600,1550,600,500,600,500,600,500,600,1550,600,500,600,1550,600,500,600,500,600,1550,600,1550,550,1600,550,};
                          irsend.sendRaw(raw,200,38);
                          digitalWrite(3, HIGH);    
                          }
                    if(dado_servidor[8] == 0x04){
                          unsigned int raw[200] = {4500,4500,600,1550,600,500,600,1550,600,1550,600,500,600,500,600,1550,600,500,600,500,600,1550,600,500,600,500,550,1600,550,1550,600,500,600,1550,600,500,650,1500,600,1550,600,1550,600,1550,600,500,600,1550,600,1550,600,1550,550,550,550,500,600,500,600,500,600,1550,600,500,600,500,600,1550,600,1550,600,1550,600,500,600,500,600,500,600,500,600,500,600,500,600,500,600,500,600,1550,600,1550,550,1600,550,1550,600,1550,600,5200,4400,4350,550,1600,550,550,550,1550,600,1550,600,500,600,500,600,1550,600,500,600,500,600,1550,600,500,600,500,600,1550,600,1550,600,500,550,1600,550,550,550,1550,600,1550,600,1550,600,1550,600,500,600,1550,600,1550,600,1550,600,500,600,500,600,500,600,500,600,1550,550,550,550,550,550,1550,600,1550,600,1550,600,500,600,500,600,500,600,500,600,500,600,550,550,500,600,550,550,1550,600,1550,600,1550,550,1600,550,1550,590};
                          irsend.sendRaw(raw,200,38);
                          digitalWrite(3, HIGH);
                          }
                    if(dado_servidor[8] == 0x01){
                          unsigned int raw[200] = {4400,4350,550,1550,600,500,600,1550,600,1550,600,500,600,500,600,1550,600,500,600,500,600,1550,600,500,600,500,600,1550,600,1550,600,500,550,1550,600,500,600,550,550,500,600,1550,600,1550,600,1550,600,1550,600,1550,600,1550,600,1550,600,1550,550,550,600,500,550,550,550,550,550,500,600,500,600,500,600,500,600,500,600,1550,600,500,600,500,600,500,600,1550,650,1500,600,1550,600,1550,600,500,600,1550,600,1500,650,1500,600,5200,4450,4300,600,1550,600,500,600,1500,600,1550,600,500,600,500,650,1500,600,500,600,500,600,1550,600,500,600,500,600,1550,600,1550,600,500,600,1550,600,500,600,500,600,500,600,1550,550,1550,600,1550,650,1500,600,1550,600,1550,600,1550,600,1550,600,500,600,500,600,500,600,500,600,500,600,500,600,500,600,500,600,500,550,1550,600,500,600,500,600,500,600,1550,600,1550,600,1550,600,1550,600,500,600,1550,600,1550,600,1550,600,};
                          irsend.sendRaw(raw,200,38);
                          digitalWrite(3, HIGH);
                          }      
                  }
          }
        //Limpa buffers           
        zera_dados_serial(recepcao_dados_modulo_wifi);
        zera_dados_serial(dado_servidor); 
      }
  //Aguarda a confirmação da conexão TCP/IP ser finalizada   
  if((strncmp("0,CLOSED", recepcao_dados_modulo_wifi,8) == 0 || strncmp("CLOSED", recepcao_dados_modulo_wifi,6) == 0) && flag_recepcai_serial_completa == 1 && conexao_aberta == 1){
        digitalWrite(conexao_TCP_IP_status, HIGH);
        conexao_aberta = 0;
        zera_dados_serial(recepcao_dados_modulo_wifi);
        }
}
/*
void dump(decode_results *results) {
  int c = 0;
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

}*/


