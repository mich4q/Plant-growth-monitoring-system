#ifndef CONSTANTS_H
#define CONSTANTS_H

#define DHT_PIN 16
#define DHT_TYPE DHT22
#define DHT_INTERVAL 2000

struct SensorData
{
    float temperature;
    float humidity;
    float soil_humidity;
    int co2;
    String timestamp;
};


#endif