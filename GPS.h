// Power supply 5V
// Device Rx to Arduino TX2
// Device Tx to Arduino RX2

#include "TinyGPS++.h"
TinyGPSPlus gps;

void GPS_setup()
{
  Serial2.begin(9600);        //This opens up communications to the GPS
  Serial.println("GPS Set up");          //Just show to the monitor that the sketch has started
}

void GPS_loop() {
  while (Serial2.available())    //While there are characters to come from the GPS
  {
    //Serial.println("Available");
    gps.encode(Serial2.read());  //This feeds the serial NMEA data into the library one char at a time
  }
  if (gps.location.isUpdated())            //This will pretty much be fired all the time anyway but will at least reduce it to only after a package of NMEA data comes in
  {

    double tempLat = gps.location.lat();
    double tempLong = gps.location.lng();

    //Serial.println("is updated");
    //Get the latest info from the gps object which it derived from the data sent by the GPS unit
    //Serial.println("Satellite Count:");
    //Serial.println(gps.satellites.value());
    Serial.println("Latitude:");
    Serial.println(gps.location.lat(), 6);
    Serial.println("Longitude:");
    Serial.println(gps.location.lng(), 6);
    //Serial.println("Speed MPH:");
    //Serial.println(gps.speed.mph());
    //Serial.println("Altitude Feet:");
    //Serial.println(gps.altitude.feet());
    Serial.println("");

    if (tempLat != 0 && tempLong != 0) {
      lastLatitude = tempLat;
      lastLongitude = tempLong;
    }

  }

  //Serial.println("Third");
}
