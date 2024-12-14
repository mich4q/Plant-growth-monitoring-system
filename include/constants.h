#ifndef CONSTANTS_H
#define CONSTANTS_H

#define DHT_PIN 3
#define DHT_TYPE DHT22
#define DHT_INTERVAL 5000

struct SensorData
{
    float temperature = -1;
    float humidity= -1;
    float soil_humidity= -1;
    int co2= -1;
    String timestamp="-1";
};


#endif