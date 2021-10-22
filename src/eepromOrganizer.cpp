#include "eepromOrganizer.h"

namespace Pulu {
    EEPROM_Organizer::EEPROM_Organizer(EEPROM_24AA64* eeprom) {
        this->eeprom = eeprom;
    }

    bool EEPROM_Organizer::read_config(Config &returnConfig) {
        Config config;
        char data[39];
        if(eeprom->read(data, 39, 0)) {
            return true;
        }
        uint32_t eepromCRC;
        memcpy(&eepromCRC, data, 4);
        memcpy(&config.version, data+4, 1);
        memcpy(config.keys.devEui, data+5, 8);
        memcpy(config.keys.appEui, data+13, 8);
        memcpy(config.keys.appKey, data+21, 16);
        memcpy(&config.wait_time, data+37, 2);
        
        uint32_t computedCRC;
        mbedCRC.compute((void *)(data+4), 35, &computedCRC);
        if(eepromCRC != computedCRC) {
            return true;
        }
        returnConfig = config;
        return false;
    }

    bool EEPROM_Organizer::write_config(Config config) {
        char data[39];
        char version[] = {2};
        memcpy((data+4), version, 1);
        memcpy((data+5), config.keys.devEui, 8);
        memcpy((data+13), config.keys.appEui, 8);
        memcpy((data+21), config.keys.appKey, 16);
        memcpy((data+37), &config.wait_time, 2);
        uint32_t computedCRC;
        mbedCRC.compute((void *)(data+4), 35, &computedCRC);
        memcpy(data, &computedCRC, 4);
        
        return eeprom->write(data, 39, 0);
    }

    bool EEPROM_Organizer::write_config_wait_time(uint16_t wait_time) {
        Config config;
        read_config(config);
        memcpy(&config.wait_time, &wait_time, 2);
        return write_config(config);
    }

};