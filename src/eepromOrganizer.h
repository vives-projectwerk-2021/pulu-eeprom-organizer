#pragma once

#include "EEPROM_24AA64.h"
#include "mbed.h"
#include "simple-lorawan-config.h"
#include <array>

#define eepromOrganizer_DEBUG(x, ...)   //set as comment to enable debugging
#ifndef eepromOrganizer_DEBUG
#define eepromOrganizer_DEBUG(x, ...) printf("[eepromOrganizer]\t" x "\r\n", ##__VA_ARGS__)
#endif

namespace Pulu {

    class EEPROM_Organizer {
        public:
            struct Config {
                uint8_t version = 0xFF;
                SimpleLoRaWAN::LoRaWANKeys keys = {
                    {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF},
                    {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF},
                    {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF}
                };
                uint16_t wait_time = 0xFF;
            };

        public:
            EEPROM_Organizer(PinName sda, PinName scl, uint16_t address);

            Config read_config(bool* valid = nullptr, bool* error = nullptr);
            bool write_config(Config config);
            bool write_config_wait_time(uint16_t wait_time);

            std::array<uint8_t, 32> read_battery_levels(bool* error);
            bool write_battery_level(uint8_t level);

        private:
            EEPROM_24AA64 eeprom;
            MbedCRC<POLY_32BIT_ANSI, 32> mbedCRC;
    };

};