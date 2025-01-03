#ifndef DHTDATA_H
#define DHTDATA_H

#include <Arduino.h>
#include <DHT.h>
#include <Adafruit_Sensor.h>
#include <ArduinoJson.h>
#include "constants.h" 
#include <time.h>


class DHTData{
    public:
    float temperature = 0.0;
    float humidity = 0.0;

    const char* ntpServer = "pool.ntp.org";
    const long  gmtOffset_sec = 3600;
    const int   daylightOffset_sec = 3600;

    SensorData getDHTData();
    String getReadingTimestamp();
    void dhtInit();

};
extern DHTData dhtData;
#endif