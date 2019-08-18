#include "GLOBALS.h"
#include "GSM.h"
#include "GPS.h"
#include "HUMIDITY.h"
#include "RFID.h"
#define trackButton 7
#define buzzer 6

void updateLockStatus();
void postUpdate();

void setup() {
  Serial.begin(9600);
  GSM_setup();
  RFID_setup();

  
  pinMode(buzzer, OUTPUT);
  pinMode(trackButton, INPUT);
}

void loop() {
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
      output.println("Opening case and stopping tracking");
      isTracking = false;
    } else {
      output.println("Unauthoruzed");
    }
  } else {
      output.println(isTracking ? "Tracking" : "Idle");
  }
  
  updateLockStatus();
  if (isTracking) {
    GPS_fetchUpdate();
    humidity_fetchUpdate();
    postUpdate();
  }
  
  delay(1000);
}

void updateLockStatus() {
   if (!isTracking && digitalRead(trackButton) == 1) {
    isTracking = true;

    tone(buzzer, 900); // Send 1KHz sound signal...
    delay(300);        // ...for 1 sec
    noTone(buzzer);

    output.println("Device locked");
    output.println("Tracking started");
    //lcd.clear();
    //lcd.print("Tracking...");
    // Print "Tracking..."
  }
}

void postUpdate() {
    String payload = String(caseId) + String(" ")
    + String(lastLatitude, 6) + String(" ") 
    + String(lastLongitude, 6) + String(" ")
    + String(lastTemperature, 2) + String(" ") 
    + String(lastHumidity, 2);
    
    char response[128];
    GSM_post("http://amada.orkhanalikhanov.com/api/push-gps", payload.c_str(), response);
    debug("got response");
    debug(response);
    if (strstr(response, ",200,") != NULL) {
      output.println("Pushed successfully");
    } else {
      output.println("Failed to push gms data");
    }
}
