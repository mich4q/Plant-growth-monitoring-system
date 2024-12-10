#include "dhtData.hpp"

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
    JsonDocument doc; // Init and get the time
    String timestamp;

    timestamp = getReadingTimestamp();

    // Sprawdzenie poprawności odczytu
    if (isnan(temperature) || isnan(humidity)) {
        jsonResponse = "{\"error\": \"Błąd odczytu czujnika\"}";
        return jsonResponse;
    }
  // Przygotowanie odpowiedzi JSON
    doc["temperature"] = temperature;
    doc["humidity"] = humidity;
    doc["timestamp"] = timestamp;
    //   Konwersja do stringa
    serializeJson(doc, jsonResponse);
    return jsonResponse;
}

