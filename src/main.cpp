#include <Arduino.h>
#include "main.hpp"

Web web;
Network network;
Sd_card sdCard;
void setup() {

    hardwareInit();
    initFilesystem();
    initWiFi();
    web.setup();

    // for(int i=0;i<5;i++)
    // {
    //     Serial.println("testing firmware updates ota");
    // }

}

void loop() {

}
void initWiFi(){
    handlePreferences.readNetworkValues();
    network.init();
}
void initFilesystem(){
    if (!LittleFS.begin()) {
    Serial.println("Failed to mount filesystem.");
    return;
  }
  Serial.println("Filesystem mounted successfully.");
}

void hardwareInit(){
    Serial.begin(115200);
    // sdCard.init();
    pinMode(OUTPUT,LOW);

}