/*CONEXÃO COM O BANCO DE DADOS*/
#include <Ethernet.h>
#include <MySQL_Connection.h>
#include <MySQL_Cursor.h>

byte mac_addr[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
//byte mac_addr[] = { "74", "17", "C1", "4F", "F8", "DD" };
//74-17-C1-4F-F8-DD
IPAddress server_addr(189,14,200,70);
char user[] = "grupo8";
char password[] = "1YHXU0EHqt";
// Sample query
char query[128];
char INSERT_DATA[] = "INSERT INTO zadmin_banco.captador_chamada (rf_cod, data_hora, mac_arduino) VALUES (%s,now(),1)";



EthernetClient client;
MySQL_Connection conn((Client *)&client);
// Create an instance of the cursor passing in the connection
MySQL_Cursor cur = MySQL_Cursor(&conn);



/*LEITOR DO RFID*/
#include <SoftwareSerial.h>
#include <PI_TI.h>

// configuração da da software serial para receber numero dos cartões

          //  RX, TX
SoftwareSerial mySerial(7, 20); // O leitor de RFID está na porta D7 do Arduino
                // e o Arduino UNO não possui uma porta digital D20 o valor foi colocado 
                // apenas para poder utilizar a funcão sem desperdiçar uma porta utilizável. 
RFID sensorAcesso(mySerial);

void setup() 
{
  // put your setup code here, to run once:
  pinMode (9, OUTPUT);

  
  Serial.begin(9600); // configuração da serial para comunicar com PC.
  while (!Serial) {
    ; // aguarda para a porta USB iniciar.
  }

  // seta a velocidade da porta 
  mySerial.begin(9600);
  Serial.begin(9600);
  while (!Serial); // wait for serialport to connect
  Ethernet.begin(mac_addr);
  Serial.println("Connecting...");
  if (conn.connect(server_addr, 3306, user, password)) {
    delay(1000);
  }
  else
    Serial.println("Connection failed.");
    
}

void loop()
{
  sensorAcesso.run(); // A cada execução recebe a próxima parte do código do cartão.

  if(sensorAcesso.codePronto()) // se ele foi todo recebido
  {
    Serial.println(sensorAcesso.getCodeDecimal()); //convertemos de hexadecimal, para descimal e imprimimos na tela.
    ;
    digitalWrite (9, HIGH); 
    delay (2000);
    digitalWrite (9,LOW);
    MySQL_Cursor *cur_mem = new MySQL_Cursor(&conn);
   //  Save
    //dtostrf(1,sensorAcesso.getCodeDecimal(),1,1);
    sprintf(query, INSERT_DATA,sensorAcesso.getCodeDecimal(),mac_addr);
    cur_mem->execute(query);
    delete cur_mem;
    Serial.println("Dados inseridos.");
    
    //delay (1000);
    //Serial.println(cur.execute(query));
    
    
  }
}

/*void loop() {
  // put your main code here, to run repeatedly:
digitalWrite (9, HIGH); / / set o LED*/
/*delay (1000); /* esperar / por um segundo*/
/*digitalWrite (9, LOW); /* / definir o off LED*/
/*delay (200); /* esperar / por um segundo*/
/*Colocar um botão e mostrar uma ação no led*/
/*comprar o botão normalmente fechado
  resistencia de 300 oms
*/



