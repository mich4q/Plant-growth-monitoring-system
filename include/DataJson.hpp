#include <ArduinoJson.h>
#include <SD_MMC.h>
#include <FS.h>
#include "constants.h"
class DataHandler{
    public:
    JsonDocument data;
    JsonDocument doc;
    
    bool createDataJson();
    bool updateDataJson();
    String addData(SensorData data);
    
    const char* dataFilePath = "/data.json";

};
extern DataHandler dataHandler;