#include "dhtData.hpp"
#include "DataJson.hpp"
DHT dht_sensor(DHT_PIN,DHT_TYPE);
DHTData dhtData;


String DHTData::getReadingTimestamp() {
    
    configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
    
    struct tm timeinfo;
    // Pobranie lokalnego czasu
    if (!getLocalTime(&timeinfo)) {
        return "Brak synchronizacji czasu"; // Obsługa błędu
    }

    // Konwersja czasu do formatu "YYYY-MM-DD HH:MM:SS"
    char timeStampBuffer[20];
    strftime(timeStampBuffer, sizeof(timeStampBuffer), "%Y-%m-%d %H:%M:%S", &timeinfo);
    
    return String(timeStampBuffer); // Zwrócenie jako String
}

SensorData DHTData::getDHTData(){
    SensorData data;
    // dht_sensor.begin();
    data.temperature = dht_sensor.readTemperature();
    data.humidity = dht_sensor.readHumidity();
    data.timestamp = getReadingTimestamp();
    data.co2 = 0;
    data.soil_humidity = 0;
    
    return data;
}

void DHTData::dhtInit(){
    dht_sensor.begin();
}
