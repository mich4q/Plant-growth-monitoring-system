#include <ArduinoJson.h>
#include <SD_MMC.h>
#include <FS.h>
#include "constants.h"
class DataHandler{
    public:
    JsonDocument doc;
    
    bool createDataJson();
    bool saveJsonToSDcard();
    String updateJsonDoc(SensorData data);
    
    const char* dataFilePath = "/data.json";

};
extern DataHandler dataHandler;