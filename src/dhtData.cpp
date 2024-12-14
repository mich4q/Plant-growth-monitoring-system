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

String DHTData::getDHTData(){
    temperature = dht_sensor.readTemperature();
    humidity = dht_sensor.readHumidity();
    String jsonResponse;
    String timestamp;

    timestamp = getReadingTimestamp();
    // Sprawdzenie poprawności odczytu
    if (isnan(temperature) || isnan(humidity)) {
        jsonResponse = "{\"error\": \"Błąd odczytu czujnika\"}";
        return jsonResponse;
    }
    
    dataHandler.doc["temperature"] = temperature;
    dataHandler.doc["humidity"] = humidity;
    dataHandler.doc["soil_humidity"] = 0;
    dataHandler.doc["CO2"] = 0;
    dataHandler.doc["timestamp"] = timestamp;

    serializeJson(dataHandler.doc, jsonResponse);
    return jsonResponse;
}
void DHTData::dhtInit(){
    dht_sensor.begin();
}