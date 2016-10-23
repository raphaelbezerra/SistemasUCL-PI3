/*Inclusão das bibliotecas*/
/**Conexão com o banco**/
  #include <Ethernet.h>
  #include <MySQL_Connection.h>
  #include <MySQL_Cursor.h>
  byte mac_addr[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xDE };
  //ED
  IPAddress server_addr(189,14,200,70);
  char user[] = "grupo8";
  char password[] = "1YHXU0EHqt";
  // Sample query
  char query[128];
  char INSERT_DATA[] = "INSERT INTO zadmin_banco.captador_chamada (rf_cod, data_hora, mac_arduino) VALUES (%s,now(),1)";
  EthernetClient client;
  MySQL_Connection conn((Client *)&client);
  MySQL_Cursor cur = MySQL_Cursor(&conn);
  #include <SoftwareSerial.h>
  #include <PI_TI.h>

/**Leitor do RFID**/
  SoftwareSerial mySerial(7, 20); // O leitor de RFID está na porta D7 do Arduino
  RFID sensorAcesso(mySerial);

/**Display**/
  #include <LiquidCrystal_I2C.h> 
  LiquidCrystal_I2C lcd(0x3f,2,1,0,4,5,6,7,3, POSITIVE);
void setup() 
{
  lcd.begin (16,2);
  lcd.print("Iniciando o Sistema");
  lcd.clear();
  delay(1000);
  pinMode (9, OUTPUT); 
  Serial.begin(9600); // configuração da serial para comunicar com PC.
  while (!Serial) {    ;  }
  mySerial.begin(9600);
  Serial.begin(9600);
  while (!Serial); // wait for serialport to connect
  Ethernet.begin(mac_addr);
  lcd.print("Conectando...");
  if (conn.connect(server_addr, 3306, user, password)) {
    delay(1000);
    lcd.clear();
    lcd.print("Pronto!");
      }
  else
  lcd.clear();
  lcd.print("Falhou.");    
}

void loop()
{
  sensorAcesso.run(); // A cada execução recebe a próxima parte do código do cartão.

  if(sensorAcesso.codePronto()) // se ele foi todo recebido
  {
    lcd.print(sensorAcesso.getCodeDecimal()); //convertemos de hexadecimal, para descimal e imprimimos na tela.
    ;
    MySQL_Cursor *cur_mem = new MySQL_Cursor(&conn);
   //  Save
    //dtostrf(1,sensorAcesso.getCodeDecimal(),1,1);
    sprintf(query, INSERT_DATA,sensorAcesso.getCodeDecimal(),mac_addr);
    cur_mem->execute(query);
    delete cur_mem;
    lcd.clear();
    lcd.print("Dados inseridos.");
    
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



