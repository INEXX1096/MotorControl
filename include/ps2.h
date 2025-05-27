#ifndef __PS2_H
#define __PS2_H

#include "mbed.h"
// 按键掩码定义（低电平有效）
#define PS2_KEY_SELECT     0x0001  // SELECT
#define PS2_KEY_L3         0x0002  // L3
#define PS2_KEY_R3         0x0004  // R3
#define PS2_KEY_START      0x0008  // START
#define PS2_KEY_UP         0x0010  // ↑
#define PS2_KEY_RIGHT      0x0020  // →
#define PS2_KEY_DOWN       0x0040  // ↓
#define PS2_KEY_LEFT       0x0080  // ←

#define PS2_KEY_L2         0x0100  // L2
#define PS2_KEY_R2         0x0200  // R2
#define PS2_KEY_L1         0x0400  // L1
#define PS2_KEY_R1         0x0800  // R1
#define PS2_KEY_TRIANGLE   0x1000  // △
#define PS2_KEY_CIRCLE     0x2000  // ○
#define PS2_KEY_CROSS      0x4000  // ×
#define PS2_KEY_SQUARE     0x8000  // □


class PS2{
    public:
        PS2(PinName clk, PinName cmd, PinName dat, PinName cs);

        void init();
        bool setInit();
        uint8_t readAnalog(uint8_t channel);
        uint16_t readKey();
        bool isPressed(uint16_t keyData, uint16_t KeyMask);
        uint8_t transferByte(uint8_t dataByte);


    private:
        DigitalOut clk;
        DigitalOut cmd;
        DigitalInOut data;
        DigitalOut cs;

        void writeByte(uint8_t data);
        uint8_t readByte();
        void sendCommand(uint8_t* cmd, uint8_t len);
        void delayUs(uint32_t us);

};

#endif