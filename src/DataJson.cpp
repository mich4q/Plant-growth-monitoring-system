#include "DataJson.hpp"

DataHandler dataHandler;

bool DataHandler::createDataJson() {
    // Sprawdź, czy plik już istnieje
    if (SD_MMC.exists(dataFilePath)) {
        Serial.println("[INFO] Plik już istnieje.");
        return true; // Plik już istnieje
    }

    // Utwórz nowy plik
    File file = SD_MMC.open(dataFilePath, FILE_WRITE);
    if (!file) {
        Serial.println("[ERROR] Nie można otworzyć pliku do zapisu.");
        return false;
    }
    file.close();
    Serial.println("[INFO] Plik data.json utworzony.");
    return true;
}

bool DataHandler::updateDataJson() {
    
    File file = SD_MMC.open(dataFilePath, FILE_WRITE);
    if (!file) {
        Serial.println("[ERROR] Nie można otworzyć pliku do zapisu.");
        return false;
    }

    // Zapisz JSON do pliku
    if (serializeJson(data, file) == 0) {
        Serial.println("[ERROR] Nie można zaktualizować JSON w pliku.");
        file.close();
        return false;
    }

    file.close();
    Serial.println("[INFO] Plik data.json zaktualizowany.");
    return true;
}


String DataHandler::addData(SensorData data) {
    JsonDocument doc;
    JsonObject reading = doc.add<JsonObject>();
    reading["temperature"] = data.temperature;
    reading["humidity"] = data.humidity;
    reading["soil_humidity"] = data.soil_humidity;
    reading["CO2"] = data.co2;
    reading["timestamp"] = data.timestamp;
    
    String response;
    serializeJson(doc,response);
    return response;
}