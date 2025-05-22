#include "nrf24l01.h"

NRF24L01::NRF24L01(PinName mosi, PinName miso, PinName sck, PinName csn, PinName ce)
    :spi(mosi, miso, sck), csnPin(csn),cePin(ce)
{
    csnPin = 1;
    cePin = 0;

}

void NRF24L01::init(){
    spi.format(8,0);
    spi.frequency(10000000); //SPI 接口最大传输频率 10MHz

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
    
//设置Tx address
void NRF24L01::setTxAddress(uint8_t* address, uint8_t length){
    csnPin = 0;
    spi.write(0x20 | 0x10);
    for(uint8_t i = 0; i < length; i++){
        spi.write(address[i]);
    }
    csnPin = 1;
}

//设置Rx address
void NRF24L01::setRxAddress(uint8_t* address, uint8_t length){
    csnPin = 0;
    spi.write(0x20 | 0x0A);
    for (uint8_t i = 0; i < length; i++){
        spi.write(address[i]);
    }
    csnPin = 1;

}

void NRF24L01::setRxMode(){
    uint8_t config = readRegister(0x00);
    config |= (1 << 0);  
    writeRegister(0x00, config);
    cePin = 1;

}

void NRF24L01::setTxMode(){
    uint8_t config = readRegister(0x00);
    config &= ~(1 << 0);
    writeRegister(0x00, config);
    cePin = 0;
}



//从tx端传输payload的数据
void NRF24L01::sendPayload(uint8_t* data, uint8_t length){
    //清空
    csnPin = 0;
    spi.write(0xE1);
    csnPin = 1;

    //写入payload
    csnPin = 0;
    spi.write(0xA0);
    for (uint8_t i = 0; i < length; i++){
        spi.write(data[i]);
    }
    csnPin = 1;


    //传输数据
    cePin = 1;
    wait_us(15);
    cePin = 0;
}

//判断是否有数据
bool NRF24L01::dataAvailable(){
    uint8_t status = readRegister(0x07);
    if (status & 0x40){
        return true;
    }
    return false;
        
}

//接收payload 的数据
void NRF24L01::receivePayload(uint8_t* buffer, uint8_t length){
    csnPin = 0;
    spi.write(0x61);
    for (uint8_t i = 0; i < length; i++){
        buffer[i] = spi.write(0XFF);
    }
    csnPin = 1;

    writeRegister(0x07, 0x40);
}