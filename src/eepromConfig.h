#pragma once

#include "simple-lorawan-config.h"

namespace Pulu {
    struct EEPROM_Config {
        uint8_t version = 0xFF;
        SimpleLoRaWAN::LoRaWANKeys keys = {
            {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF},
            {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF},
            {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF}
        };
        uint16_t wait_time = 0xFF;
    };
};