#include "GLOBALS.h"
#include "GSM.h"
#include "RFID.h"
#define output Serial

void setup() {
  Serial.begin(9600);
  GSM_setup();
  RFID_setup();
}

void loop() {
//  GSM_post();
  char rfidResponse[128]; 
  if (RFID_check(rfidResponse)) {
    debug("READ");
    debug(rfidResponse);
    /// renaming for the sake of redability and understanding
    char* response = rfidResponse;
    String request = String(caseId) + String(" ") + String(rfidResponse);
    GSM_post("http://amada.orkhanalikhanov.com/api/authenticate/rfid", request.c_str(), response);
    debug("got response");
    debug(response);
    if (strstr(response, ",200,") != NULL) {
      output.println("opening case");
    } else {
      output.println("Unauthoruzed");
    }
  } else {
    debug("no response");
  }

  delay(1000);
}
