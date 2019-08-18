/*
   Modified by Amiraslan Bakhshili
   Created by Amada Digital Voyagers team
*/

#include <dht.h>

dht DHT;

#define DHT11_PIN A0

void humidity_fetchUpdate()
{
  DHT.read11(DHT11_PIN);
  lastTemperature = DHT.temperature;
  lastHumidity = DHT.humidity;
}
