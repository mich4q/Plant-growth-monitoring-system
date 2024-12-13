#include <ArduinoJson.h>
#include <SD_MMC.h>

class DataHandler{
    public:
    JsonDocument data;
    bool createDataJson();
    bool updateDataJson();
    bool addData(String timestamp, float temperature, float humidity, float soil_humidity, int co2);
    
    const char* dataFilePath = "/data.json";

};
extern DataHandler dataHandler;