#include "GLOBALS.h"
#include "GPS.h"
#include "GSM.h"
//#include "KEYPAD.h"

int trackButton = 7;

void setup() {
  Serial.begin(9600);   //This opens up communications to the Serial monitor in the Arduino IDE

  lcd.print("Turned Off");
  // turn off the screen

  GPS_setup();
  RFID_setup();
  GSM_setup;

  pinMode(trackButton, INPUT);
}

String rfidString = "";
char keypadInput = NO_KEY

void loop() {

  keypadInput = KEYPAD_loop()
  if (KEYPAD_loop() != NO_KEY) {


    lcd.setCursor(0, 0);
    lcd.print("Enter password...");

    if (keypadInput) {
      Data[data_count] = keypadInput;
      lcd.setCursor(data_count, 1);
      lcd.print(Data[data_count]);
      data_count++;
    }

    if (data_count == Password_Length - 1) {
      lcd.clear();

      // Replace this with Auth Request
      if (!strcmp(Data, Master)) {
        lcd.print("Correct");
        delay(5000);
      }
      else {
        lcd.print("Incorrect");
        delay(3000);
      }

      lcd.clear();
      clearData();
    }

  }

  rfidString = RFID_check()
  if (rfidString.length() > 2) {
    lcd.print(rfidString);
  }

  if (digitalRead(trackButton) == 1) {
    isTracking = true;
    lcd.print("Tracking...");
    // Print "Tracking..."
  }

  if (isTracking) {
    GPS_loop();
    GSM_post();
    delay(3000);
  }

}
