#include "dhtData.hpp"
DataHandler dataHandler;
DHT dht_sensor(DHT_PIN,DHT_TYPE);

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
    dht_sensor.begin();
    temperature = dht_sensor.readTemperature();
    humidity = dht_sensor.readHumidity();
    String jsonResponse;
    String timestamp;

    timestamp = getReadingTimestamp();
    if(!dataHandler.addData(timestamp,temperature,humidity,0.0,0)){
        Serial.println("Failed to add data to json file ");
    }

    // Sprawdzenie poprawności odczytu
    if (isnan(temperature) || isnan(humidity)) {
        jsonResponse = "{\"error\": \"Błąd odczytu czujnika\"}";
        return jsonResponse;
    }
    JsonDocument doc; 
    doc["temperature"] = temperature;
    doc["humidity"] = humidity;
    doc["soil_humidity"] = 0;
    doc["CO2"] = 0;
    doc["timestamp"] = timestamp;

    serializeJson(doc, jsonResponse);
    return jsonResponse;
}

