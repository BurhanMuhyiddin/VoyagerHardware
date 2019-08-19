#include "GLOBALS.h"
#include "GSM.h"
#include "GPS.h"
#include "HUMIDITY.h"
#include "RFID.h"
#define trackButton 7
#define buzzer 6
#define doorPin 4
#define ongoingRequest 5
#define unauthorizedLed 10
#define authorizedLed 11
#define trackingLed 12


void updateTrackingWaitingLed();
void postUpdate();

void setup() {
  Serial.begin(9600);
  GSM_setup();
  RFID_setup();

  pinMode(buzzer, OUTPUT);
  pinMode(trackButton, INPUT);
  pinMode(doorPin, INPUT);
  pinMode(ongoingRequest, OUTPUT);
  pinMode(unauthorizedLed, OUTPUT);
  pinMode(authorizedLed, OUTPUT);
  pinMode(trackingLed, OUTPUT);

  tone(buzzer, 900);
  delay(300);
  noTone(buzzer);
}

void loop() {
  char rfidResponse[128];
  if (isDoorClosed && RFID_check(rfidResponse)) {
    debug("READ");
    debug(rfidResponse);
    /// renaming for the sake of redability and understanding
    char* response = rfidResponse;
    String request = String(caseId) + String(" ") + String(rfidResponse);
    turnRequestLedOn();
    GSM_post("http://amada.orkhanalikhanov.com/api/authenticate/rfid", request.c_str(), response);
    turnRequestLedOff();
    debug("got response");
    debug(response);
    if (strstr(response, ",200,") != NULL) {
      output.println("Access granted");
      digitalWrite(authorizedLed, HIGH);
      delay(350);
      digitalWrite(authorizedLed, LOW);
      tone(buzzer, 900);
      delay(300);
      noTone(buzzer);

      delay(300);
      tone(buzzer, 900);
      delay(300);
      noTone(buzzer);


      delay(300);
      tone(buzzer, 900);
      delay(300);
      noTone(buzzer);

      if (isWaitingTracking) {
        isWaitingTracking = false;
        isTracking = true;
        output.println("Stared tracking");

      } else if (isDoorClosed) {
        /// Open door and stop tracking
        unlockDoor();
        isTracking = false;
      }
    } else {
      output.println("Unauthoruzed");
      digitalWrite(unauthorizedLed, HIGH);
      delay(350);
      digitalWrite(unauthorizedLed, LOW);
      tone(buzzer, 2500);
      delay(700);
      noTone(buzzer);

      delay(700);
      tone(buzzer, 2500);
      delay(700);
      noTone(buzzer);

      delay(700);
      tone(buzzer, 2500);
      delay(700);
      noTone(buzzer);
    }
  } else {
    output.print(isDoorClosed ? "Door is close. " : "Door is open. ");
    output.println(isTracking ? "Tracking" : isWaitingTracking ? "Waiting for tracking to be started" : "Idle");
  }

  updateDoorState();
  updateTrackingWaiting();

  if (isTracking) {
    digitalWrite(trackingLed, HIGH);
    GPS_fetchUpdate();
    humidity_fetchUpdate();
    postUpdate();
  } else
  {
    digitalWrite(trackingLed, LOW);
  }

  delay(1000);
}

void updateDoorState() {
  isDoorClosed = digitalRead(doorPin);
  const bool isDirty = isDoorClosed != lastIsDoorClosed;
  lastIsDoorClosed = isDoorClosed;

  if (isDirty && isDoorClosed) {
    lockDoor();
  }
}

void updateTrackingWaiting() {
  if (isDoorClosed && !isWaitingTracking && !isTracking && digitalRead(trackButton) == 1) {
    isWaitingTracking = true;
    tone(buzzer, 900);
    delay(300);
    noTone(buzzer);

    output.println("Waiting for staring tracking");
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
                   + String(lastHumidity, 2) + String(" ")
                   + String(didCollide);

  char response[128];
  turnRequestLedOn();
  GSM_post("http://amada.orkhanalikhanov.com/api/push-gps", payload.c_str(), response);
  turnRequestLedOff();
  debug("got response");
  debug(response);
  if (strstr(response, ",200,") != NULL) {
    /// reset data
    didCollide = false;
    output.println("Pushed successfully");
  } else {
    output.println("Failed to push gms data");
  }
}

void unlockDoor() {
  debug("Unlocked door");
}

void lockDoor() {
  debug("Locked door");
}

void turnRequestLedOn() {
  digitalWrite(ongoingRequest, HIGH);
}

void turnRequestLedOff() {
  digitalWrite(ongoingRequest, LOW);
}
