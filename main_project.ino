#include "GLOBALS.h"
#include "LCD.h"
//#include "KEYPAD.h"
#include "HUMIDITY.h"
#include "RFID.h"
#include "GPS.h"
#include "GSM.h"

int trackButton = 7;
int buzzer = 6;

void setup() {
  Serial.begin(115200);   //This opens up communications to the Serial monitor in the Arduino IDE

  //turn off the screen
  setup_LCD();
  GPS_setup();
  RFID_setup();
  GSM_setup();

  pinMode(buzzer, OUTPUT);

  lcd.print("Turned Off");
  pinMode(trackButton, INPUT);
}

String rfidString = "";
//char keypadInput = NO_KEY

void loop() {

  //  keypadInput = KEYPAD_loop()
  //  if (KEYPAD_loop() != NO_KEY) {
  //
  //    lcd.setCursor(0, 0);
  //    lcd.print("Enter password...");
  //
  //    if (keypadInput) {
  //      Data[data_count] = keypadInput;
  //      lcd.setCursor(data_count, 1);
  //      lcd.print(Data[data_count]);
  //      data_count++;
  //    }
  //
  //    if (data_count == Password_Length - 1) {
  //      lcd.clear();
  //
  //      // Replace this with Auth Request
  //      if (!strcmp(Data, Master)) {
  //        lcd.print("Correct");
  //        delay(5000);
  //      }
  //      else {
  //        lcd.print("Incorrect");
  //        delay(3000);
  //      }
  //
  //      lcd.clear();
  //      clearData();
  //    }
  //
  //  }

  rfidString = RFID_check();
  if (rfidString.length() > 3002) {
    //lcd.print(rfidString);
    Serial.println(rfidString);
    delay(3000);
  }

  if (digitalRead(trackButton) == 1 && !isTracking) {
    isTracking = true;

    tone(buzzer, 900); // Send 1KHz sound signal...
    delay(300);        // ...for 1 sec
    noTone(buzzer);

    Serial.println("Tracking started");
    lcd.clear();
    lcd.print("Tracking...");
    // Print "Tracking..."
  }

  if (isTracking) {
    ///GPS_loop();

    tone(buzzer, 1700); // Send 1KHz sound signal...
    delay(300);        // ...for 1 sec
    noTone(buzzer);
    delay(300);
    tone(buzzer, 1700);
    delay(300);
    noTone(buzzer);

    GSM_post();

    tone(buzzer, 2800); // Send 1KHz sound signal...
    delay(300);        // ...for 1 sec
    noTone(buzzer);
    delay(300);
    tone(buzzer, 2800);
    delay(300);
    noTone(buzzer);

    updateTempAndPressure();

    delay(7000);
  }
}
