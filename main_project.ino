#include "GLOBALS.h"
#include "GPS.h"
#include "GSM.h"
//#include "KEYPAD.h"

void setup() {
  Serial.begin(9600);   //This opens up communications to the Serial monitor in the Arduino IDE
  //GPS_setup();
  
}

void loop() {
  //KEYPAD_loop();
  GPS_loop();
  GSM_post();
  
  delay(4000);
}
