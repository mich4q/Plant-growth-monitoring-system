#include <Arduino.h>
#include "SDcard.hpp"

Sd_card sdCard;
 
void Sd_card::init(){
    if (!SD_MMC.begin()) {
      result = "SD Card Mount Failed";
    }
    if (SD_MMC.cardType() == CARD_NONE) {
      result = "No SD Card attached";
    }
    result = "SD card initialized succesfully";
    Serial.println(result);
}

void Sd_card::createDataFile(){
  if(!SD_MMC.exists(dataFilePath))
  {
      File file = SD_MMC.open("/data.json", FILE_WRITE);
      if (file)
      {
        file.println("Timestamp,Temperature,Humidity,Soil Humidity,CO,CO2");
        file.close();
        Serial.println("Created data.csv with headers");
      } else
      {
        Serial.println("Failed to create data.csv");
      }
  }
}
