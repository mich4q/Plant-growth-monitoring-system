#include <ArduinoJson.h>
#include <SD_MMC.h>
#include <FS.h>

class DataHandler{
    public:
    JsonDocument data;
    JsonDocument doc;
    
    bool createDataJson();
    bool updateDataJson();
    bool addData(String timestamp, float temperature, float humidity, float soil_humidity, int co2);
    
    const char* dataFilePath = "/data.json";

};
extern DataHandler dataHandler;