#include "eepromOrganizer.h"

namespace Pulu {
    EEPROM_Organizer::EEPROM_Organizer(PinName sda, PinName scl, uint16_t address) :
        eeprom(sda, scl, address)
    {
        
    }

    EEPROM_Config EEPROM_Organizer::read_config(bool* valid, bool* error) {
        eepromOrganizer_DEBUG("Reading config");
        EEPROM_Config config;
        char data[39];
        if(eeprom.read(data, 39, 0)) {
            *error = true;
            eepromOrganizer_DEBUG("Error occurred while reading config");
            return config;
        }
        *error = false;
        eepromOrganizer_DEBUG("Succesfull read config; validating...");
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
            *valid = false;
            eepromOrganizer_DEBUG("Invalid config");
            return config;
        }
        *valid = true;
        eepromOrganizer_DEBUG("Valid config");
        return config;
    }

    bool EEPROM_Organizer::write_config(EEPROM_Config config) {
        eepromOrganizer_DEBUG("Writing config (full)");
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
        
        bool error = eeprom.write(data, 39, 0);
        if(error) {
            eepromOrganizer_DEBUG("Error while writing config");
            return true;
        }
        eepromOrganizer_DEBUG("Succesfull wrote config");
        return false;
    }

    bool EEPROM_Organizer::write_config_wait_time(uint16_t wait_time) {
        eepromOrganizer_DEBUG("Writing config (wait_time)");
        bool valid;
        bool error;
        EEPROM_Config config = read_config(&valid, &error);
        if(error) {
            return true;
        }
        memcpy(&config.wait_time, &wait_time, 2);
        return write_config(config);
    }

    std::array<uint8_t, 32> EEPROM_Organizer::read_battery_levels(bool* error) {
        eepromOrganizer_DEBUG("Reading battery levels");
        std::array<uint8_t, 32> levels;
        levels.fill(0);
        if(eeprom.read((char*)levels.data(), 32, 0x1FFF-64)) {
            *error = true;
            eepromOrganizer_DEBUG("Error while reading battery levels");
            return levels;
        }
        eepromOrganizer_DEBUG("Succesfull read battery levels");
        return levels;
    }

    bool EEPROM_Organizer::write_battery_level(uint8_t level) {
        eepromOrganizer_DEBUG("Writing battery level");
        bool error;
        std::array<uint8_t, 32> oldLevels = read_battery_levels(&error);
        if(error)
        {
            return true;
        }
        char newLevels[32] = {level};
        memcpy(newLevels+1, oldLevels.data(), 31);
        if(eeprom.write(newLevels, 32, 0x1FFF-64)) {
            eepromOrganizer_DEBUG("Error while writing battery levels");
            return true;
        }
        eepromOrganizer_DEBUG("Succesfull wrote battery levels");
        return false;
    }

};