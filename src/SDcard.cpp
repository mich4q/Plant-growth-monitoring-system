#include <Arduino.h>
#include "SDcard.hpp"

void Sd_card::init(){
  // Start Micro SD card
  Serial.println("Starting SD Card");
  if(!SD_MMC.begin()){
    Serial.println("SD Card Mount Failed");
    return;
  }
  sdcard_type_t cardType = SD_MMC.cardType();
  if(cardType == CARD_NONE){
    Serial.println("No SD Card attached");
    return;
  } else{
    Serial.println(cardType);
  }
}