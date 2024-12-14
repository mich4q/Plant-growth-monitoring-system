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

    // Zapisz JSON do pliku
    if (serializeJson(data, file) == 0) {
        Serial.println("[ERROR] Nie można zapisać JSON do pliku.");
        file.close();
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


bool DataHandler::addData(String timestamp, float temperature, float humidity, float soil_humidity, int co2) {

    JsonObject reading = data.add<JsonObject>();
    reading["temperature"] = temperature;
    reading["humidity"] = humidity;
    reading["soil_humidity"] = soil_humidity;
    reading["CO2"] = co2;
    reading["timestamp"] = timestamp;

    // Aktualizacja pliku JSON
    if (!(updateDataJson())) {
      Serial.println("Failed to update JSON file");
      return false;
    }
    return true;
}