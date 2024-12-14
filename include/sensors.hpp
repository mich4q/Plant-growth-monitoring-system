#ifndef SENSORS_HPP
#define SENSORS_HPP

#include <Arduino.h>
#include <DHT.h>
#include <Adafruit_Sensor.h>
#include "constants.h"
#include <time.h>



struct SensorData
{
    float temperature;
    float humidity;
    float soil_humidity;
    int co2;
    String timestamp;
};

class Sensors{
    public:
        void init();
        SensorData getData();
        String getTimestamp();
    private:
        void dhtInit();
        const char* ntpServer = "pool.ntp.org";
        const long  gmtOffset_sec = 3600;
        const int   daylightOffset_sec = 3600;

};
extern Sensors sensors;
#endif

