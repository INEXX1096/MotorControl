#ifndef     NRF24L01_H
#define     NRF24L01_H

#include    "mbed.h"

class NRF24L01 {
    public:
        NRF24L01(PinName mosi, PinName miso, PinName sck, PinName csn, PinName ce);
    
        void init();

        void writeRegister(uint8_t reg, uint8_t value);
        uint8_t readRegister(uint8_t reg);

        void setTxAddress(uint8_t* address, uint8_t length);
        void setRxAddress(uint8_t* address, uint8_t length);
        void setRxMode();  //设置为接收模式
        void setTxMode();  //设置为发送模式
        void sendPayload(uint8_t* data, uint8_t length);
        bool dataAvailable();
        void receivePayload(uint8_t* buffer, uint8_t length);
         




    private:
        SPI spi;
        DigitalOut csnPin;
        DigitalOut cePin;
        uint8_t spiTransfer(uint8_t data);

};

#endif