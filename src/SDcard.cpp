#include <Arduino.h>
#include "SDcard.hpp"

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