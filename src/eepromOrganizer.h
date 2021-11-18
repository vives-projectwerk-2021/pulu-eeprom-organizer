#pragma once

#include "EEPROM_24AA64.h"
#include "eepromConfig.h"
#include "mbed.h"
#include <array>

#define eepromOrganizer_DEBUG(x, ...)   //set as comment to enable debugging
#ifndef eepromOrganizer_DEBUG
#define eepromOrganizer_DEBUG(x, ...) printf("[eepromOrganizer]\t" x "\r\n", ##__VA_ARGS__)
#endif

namespace Pulu {

    class EEPROM_Organizer {
        public:
            EEPROM_Organizer(I2C* i2c, uint8_t address);

            EEPROM_Config read_config(bool* valid = nullptr, bool* error = nullptr);
            bool write_config(EEPROM_Config config);
            bool write_config_wait_time(uint16_t wait_time);

            std::array<uint8_t, EEPROM_24AA64::PAGE_SIZE> read_battery_levels(bool* error);
            bool write_battery_level(uint8_t level);

            bool clear();

        private:
            EEPROM_24AA64 eeprom;
            MbedCRC<POLY_32BIT_ANSI, 32> mbedCRC;
    };

};