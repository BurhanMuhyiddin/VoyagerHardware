// Power supply 5V
// Device Rx to Arduino TX2
// Device Tx to Arduino RX2

#include "TinyGPS++.h"
TinyGPSPlus gps;

void GPS_setup()
{
  Serial2.begin(9600);
  Serial.println("GPS Set up");
}

void GPS_fetchUpdate() {
  while (Serial2.available())
  {
    debug("GPS Available");
    gps.encode(Serial2.read());
  }
  
  if (gps.location.isUpdated())
  {

    double tempLat = gps.location.lat();
    double tempLong = gps.location.lng();
    
    debug("Latitude:");
    debug(tempLat, 6);
    debug("Longitude:");
    debug(tempLong, 6);

    if (tempLat != 0 && tempLong != 0) {
      lastLatitude = tempLat;
      lastLongitude = tempLong;
    }
  }
}
