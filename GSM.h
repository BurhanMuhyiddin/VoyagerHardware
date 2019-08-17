// 12V/2A power supply
// Device Tx to Arduino RX1
// Device Rx to Arduino TX1

void printSerialData();

void GSM_setup()
{
  Serial1.begin(9600);        //This opens up communications to the GPS
  Serial.println("GSM Set up");          //Just show to the monitor that the sketch has started
}

void GSM_post()
{
 Serial1.begin(9600);  
 
 delay(100);
 
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
 delay(100); 
 printSerialData();
 
 Serial1.println("AT+HTTPINIT");// setting the httppara, 
 //the second parameter is the website from where you want to access data 
 delay(100);
 printSerialData();
 
 Serial1.println("AT+HTTPARA=\"CID\",1");// setting the httppara, 
 //the second parameter is the website from where you want to access data 
 delay(100);
 printSerialData();

 Serial1.println("AT+HTTPPARA=\"URL\",\"http://amada.orkhanalikhanov.com/api/push-gps\"");// setting the httppara, 
 //the second parameter is the website from where you want to access data 
 delay(100);
 printSerialData();

// char param[50];
// strcpy(param, );
// strcat(param, content);
// strcat(param, "\"");
  
 Serial1.println("AT+HTTPPARA=\"CONTENT\",\"text/plain\"");// setting the httppara, 
 //the second parameter is the website from where you want to access data 
 delay(100);
 printSerialData();

char body[128];
sprintf(body, "%s %s %s", caseId,String(lastLatitude, 6).c_str(), String(lastLongitude, 6).c_str()); 
//Serial.print(caseId);
//Serial.print(lastLatitude);
//Serial.println(body);

char httpData[50];  
sprintf(httpData, "AT+HTTPDATA=%i,10000", strlen(body)); 

 Serial.println(httpData);
 Serial1.println(httpData);
 
 delay(100);
 printSerialData();

 Serial1.println(body);
  delay(100);
 printSerialData();

 Serial1.println("AT+HTTPACTION=1");// setting the httppara, 
 //the second parameter is the website from where you want to access data 
 delay(100);
 printSerialData();

Serial1.println("AT+HTTPREAD");// setting the httppara, 
 //the second parameter is the website from where you want to access data 
 delay(100);
 printSerialData();
}

void printSerialData()
{
 while(Serial1.available()!=0)
 Serial.write(Serial1.read());
}
