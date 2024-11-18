#include <Arduino.h>
#include "main.hpp"

Web web(80);
Network network;

void setup() {

    hardwareInit();
    initFilesystem();
    initWiFi();
    web.setup();

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
}