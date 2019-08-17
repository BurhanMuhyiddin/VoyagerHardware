
#include <LiquidCrystal.h>

const int rs = 39, en = 41, d4 = 31, d5 = 33, d6 = 35, d7 = 37;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup_LCD() {
  pinMode(3, OUTPUT);
  analogWrite(3,20);
  lcd.begin(16, 2);
  lcd.display();
}

//void loop() {
//  // Turn off the display:
//  lcd.noDisplay();
//  delay(500);
//  // Turn on the display:
//  lcd.display();
//  delay(500);
//}
