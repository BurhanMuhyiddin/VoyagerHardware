// 12V/2A power supply
// Device Tx to Arduino RX1
// Device Rx to Arduino TX1

void printSerialData();

void GSM_setup()
{
  Serial1.begin(9600); //This opens up communications to the GPS
  Serial1.println("AT+CMEE=2");
  delay(100);
  
  printSerialData();
   Serial1.println("AT+CSQ");
  delay(100);
  printSerialData();

  Serial1.println("AT+CIPCSGP=1,\"v-internet\",\"\",\"\"");//setting the SAPBR,connection type is GPRS
  delay(100);
  printSerialData();

  Serial1.println("AT+SAPBR=3,1,\"Contype\",\"GPRS\"");//setting the APN, 2nd parameter empty works for all networks
  delay(100);
  printSerialData();

  Serial1.println("AT+SAPBR=3,1,\"APN\",\"v-internet\"");
  delay(100);
  printSerialData();

  Serial1.println("AT+SAPBR=2,1");
  delay(100);
  printSerialData();


  Serial1.println("AT+SAPBR=1,1"); //init the HTTP request
  delay(1000);
  printSerialData();

  Serial1.println("AT+HTTPINIT");
  delay(1000);
  printSerialData();
  Serial.println("GSM Set up"); //Just show to the monitor that the sketch has started
}

void GSM_post(const char* url, const char* body, char * response)
{
  debug("posting");
  Serial1.println("AT+HTTPARA=\"CID\",1");
  delay(100);
  printSerialData();

  String s;

  /// Setting URL
  s = "AT+HTTPPARA=\"URL\",\"";
  s.concat(url);
  s.concat("\"");
  Serial.println(s);
  Serial1.println(s);
  delay(100);
  printSerialData();

  /// SET content type
  Serial1.println("AT+HTTPPARA=\"CONTENT\",\"text/plain\"");
  delay(100);
  printSerialData();

  char httpData[128];
  sprintf(httpData, "AT+HTTPDATA=%i,10000", strlen(body));
  Serial.println(httpData);
  Serial1.println(httpData);
  delay(100);
  printSerialData();

  Serial1.println(body);
  delay(100);
  printSerialData();

  Serial1.println("AT+HTTPACTION=1");// setting the httppara,
  delay(5000);
  
  /// Wait until available
  while (Serial1.available() == 0);

  byte i = 0;
  while (Serial1.available() != 0) {
    response[i++] = Serial1.read();
  }
  response[i] = '\0';
}

void printSerialData()
{
  while (Serial1.available() != 0)
    Serial.write(Serial1.read());
}
