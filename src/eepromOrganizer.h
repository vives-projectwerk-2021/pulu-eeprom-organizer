#pragma once

#include "EEPROM_24AA64.h"
#include "mbed.h"

namespace Pulu {

    class EEPROM_Organizer {
        public:
            struct Config {
                uint8_t version = 0xFF;
                struct Keys {
                    uint8_t devEui[8] = {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF};
                    uint8_t appEui[8] = {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF};
                    uint8_t appKey[16] = {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF};
                } keys;
                uint16_t wait_time = 0xFF;
            };

        public:
            EEPROM_Organizer(EEPROM_24AA64* eeprom);

            bool read_config(Config &config);

            bool write_config(Config config);

            bool write_config_wait_time(uint16_t wait_time);

        private:
            EEPROM_24AA64* eeprom;
            MbedCRC<POLY_32BIT_ANSI, 32> mbedCRC;
    };

};