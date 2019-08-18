/*
   Modified by Amiraslan Bakhshili
   Created by Amada Digital Voyagers team
*/

#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 20
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.

void RFID_setup()
{
  SPI.begin();          // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
}

bool RFID_check(char* response)
{
  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent())
  {
    return false;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial())
  {
    return false;
  }

  String content = "";
  for (byte i = 0; i < mfrc522.uid.size; i++)
  {
    content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
    content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
 
  content.toUpperCase();
  content.replace(" ", ":");
  strcpy(response, content.c_str());
  
  return true;
}
