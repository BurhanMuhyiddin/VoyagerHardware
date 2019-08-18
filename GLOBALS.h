
bool isTracking = false;

const char caseId[] = "caseid-1";

double lastLatitude = 40.405624;
double lastLongitude = 49.847888;

double lastTemperature = 20;
double lastHumidity = 30;

const short KEYPAD_ROW_1 = 5;
const short KEYPAD_ROW_2 = 4;
const short KEYPAD_ROW_3 = 3;
const short KEYPAD_ROW_4 = 2;

const short KEYPAD_COL_1 = 12;
const short KEYPAD_COL_2 = 9;
const short KEYPAD_COL_3 = 6;

#define output Serial
#define debug(...) \
            do {Serial.println(__VA_ARGS__);} while (0)
         
