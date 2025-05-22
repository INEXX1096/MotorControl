#ifndef     NRF24L01_H
#define     NRF24L01_H

#include    "mbed.h"

class NRF24L01 {
    public:
        NRF24L01(PinName mosi, PinName miso, PinName sck, PinName csn, PinName ce);
    
        void init();
        void writeRegister(uint8_t reg, uint8_t value);
        uint8_t readRegister(uint8_t reg);

        

    private:
        SPI spi;
        DigitalOut csnPin;
        DigitalOut cePin;
        uint8_t spiTransfer(uint8_t data);

};

#endif