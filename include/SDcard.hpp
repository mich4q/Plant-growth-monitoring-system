#ifndef SDCARD_HPP
#define SDCARD_HPP

#include <Arduino.h>
#include <SD_MMC.h>

class Sd_card{
    public:
    void init();

    private:
    String result;
};
extern Sd_card sdCard;

#endif