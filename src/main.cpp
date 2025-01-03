#include <Arduino.h>
#include "main.hpp"
#include "web.hpp"
#include "networkPreferences.hpp"
#include "network.hpp"
#include "DataJson.hpp"
#include "SDcard.hpp"

void setup() {
    hardwareInit();
    initFilesystem();
    initWiFi();

    web.setup();
    dhtData.dhtInit();

}
unsigned long lastmillis = 0;

void loop() {
    unsigned long currentmillis = millis();
    if(currentmillis - lastmillis >= DHT_INTERVAL){
        size_t freeMemory = ESP.getFreeHeap();
        SensorData data;
        data = dhtData.getDHTData();
        Serial.println(dataHandler.updateJsonDoc(data));
        dataHandler.saveJsonToSDcard();

        // Wyświetlenie dostępnej pamięci na serial porcie
        Serial.print("Dostępna pamięć: ");
        Serial.print(freeMemory);
        Serial.println(" bajtów");
        lastmillis = currentmillis;
    }    
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
    // Serial.begin(115200);
    sdCard.init();
    dataHandler.createDataJson();
}