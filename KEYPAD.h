#include <Keypad.h>

const byte ROWS = 4; //four rows
const byte COLS = 3; //three columns

char keys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'#','0','*'}
};
byte rowPins[ROWS] = {KEYPAD_ROW_4, KEYPAD_ROW_3, KEYPAD_ROW_2, KEYPAD_ROW_1}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {KEYPAD_COL_3, KEYPAD_COL_2, KEYPAD_COL_1}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

void KEYPAD_loop(){
  char key = keypad.getKey();

  if (key != NO_KEY){
    Serial.println(key);
  }
}
