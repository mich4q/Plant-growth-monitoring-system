#ifndef SDCARD_HPP
#define SDCARD_HPP

#include <Arduino.h>
#include <ArduinoJson.h>
#include <SD_MMC.h>

class Sd_card{
    public:
    void init();
    void createDataFile();
    void saveDataToCSV();
    void createDataFile(float temperature, float humidity, float CO, float CO2, float soil_humidity);

    private:
    String result;
    const char* dataFilePath = "data.csv";

};
extern Sd_card sdCard;

#endif