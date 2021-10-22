# EEPROM Organizer

This mbed class is an abstraction of the [EEPROM_24AA64](https://github.com/vives-projectwerk-2021/pulu-EEPROM_24AA64) library.

It handles the structure of the stored data for the pulu project.

## Data Structure

| address | item |
|:---:|:---|
| 0x00-0x03 | CRC |
| 0x04 | version |
| 0x05-0x0C | LoRaWAN.devEui |
| 0x0D-0x14 | LoRaWAN.appEui |
| 0x15-0x23 | LoRaWAN.appKey |
| 0x24-0x25 | wait_time |
