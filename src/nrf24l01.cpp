#include "nrf24l01.h"

NRF24L01::NRF24L01(PinName mosi, PinName miso, PinName sck, PinName csn, PinName ce)
    :spi(mosi, miso, sck), csnPin(csn),cePin(ce)
{
    csnPin = 1;
    cePin = 0;

}

void NRF24L01::init(){
    spi.format(8,0);
    spi.frequency(10000000); //10MHz

    writeRegister(0x00, 0x0B);
}

void NRF24L01::writeRegister(uint8_t reg, uint8_t value){
    csnPin = 0;
    spi.write(0x20 | reg);
    spi.write(value);
    csnPin = 1;
}

uint8_t NRF24L01::readRegister(uint8_t reg){
    csnPin = 0;
    spi.write(reg);
    uint8_t val = spi.write(0xFF);
    csnPin = 1;
    return val;
}

uint8_t NRF24L01::spiTransfer(uint8_t data) {
    return spi.write(data);
}
    
    