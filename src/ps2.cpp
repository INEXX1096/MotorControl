#include "ps2.h"

PS2::PS2(PinName clkPin, PinName cmdPin, PinName datPin, PinName csPin)
    : clk(clkPin), cmd(cmdPin), data(datPin), cs(csPin)
{
    // data 是双向，需要先设置成输入模式
    data.input();
}


void PS2::delayUs(uint32_t us) {
    wait_us(us);  // MbedOS 中推荐使用 wait_us
}


void PS2::init(){
    clk = 1;
    cmd = 1;
    cs = 1;
    data.input();
    printf("Ps2 pins initialized. \n");
}

uint8_t PS2::transferByte(uint8_t dataByte) {
    uint8_t recev = 0;
    data.output();  // 发送前设data输出

    for (uint8_t i = 0; i < 8; i++) {
        clk = 0;
        delayUs(10);

        if (dataByte & 0x01) {
            cmd = 1;
        } else {
            cmd = 0;
        }
        delayUs(10);

        clk = 1;
        delayUs(10);

        data.input();  // 切换成输入读数据
        recev <<= 1;
        if (data.read()) {
            recev |= 0x01;
        }

        data.output(); // 切回输出准备发下一bit
        dataByte >>= 1;
    }
    data.input();  // 完成后切输入
    return recev;
}

void PS2::sendCommand(uint8_t *cmdBuf, uint8_t len) {
    cs = 0;
    delayUs(10);
    for (uint8_t i = 0; i < len; i++) {
        cmdBuf[i] = transferByte(cmdBuf[i]);
    }
    cs = 1;
    delayUs(10);
}


void PS2::writeByte(uint8_t dataByte){
    data.output();
    for (uint8_t i = 0; i < 8; i++){
        clk = 0;
        delayUs(5);

        if (dataByte & 0x01){
            cmd = 1;
        }else cmd = 0;

        delayUs(5);
        clk = 1;
        delayUs(10);

        dataByte >>= 1;
        
    }
    data.input();
    
}

uint8_t PS2::readByte(){
    uint8_t recev = 0;

    for (uint8_t i = 0; i < 8; i++){
        clk = 0;
        delayUs(10);

        clk = 1;
        delayUs(10);

        data.input();
        recev <<= 1;  // 先左移

        if (data.read()){
            recev |= 0x01; // 设置最低位
        }
        delayUs(10);
    }

    return recev;
}


bool PS2::setInit(){
    uint8_t initCmd[] = {0x01, 0x42, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}; 
    sendCommand(initCmd, sizeof(initCmd));
    delayUs(50000);


    printf("Init response: ");
    for (int i = 0; i < sizeof(initCmd); i++){
        printf("0x%02X ", initCmd[i]);
    }
    printf("\n");
    
    if (initCmd[2] == 0x5A){
        printf("Ps2 controller init success. \n");
        return true;
    }else{
        printf("PS2 controller init failed, response: 0x%02X\n", initCmd[2]);
        return false;
    }
    
}

uint8_t PS2::readAnalog(uint8_t channel){
    uint8_t cmdBuf[] = {0x01, 0x42, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}; 
    sendCommand(cmdBuf, sizeof(cmdBuf));
    if (cmdBuf[2] == 0x5A)return 0xFF;
    
    switch (channel){
        case 0: return cmdBuf[7];  // 左摇杆 X
        case 1: return cmdBuf[8];  // 左摇杆 Y
        case 2: return cmdBuf[5];  // 右摇杆 X
        case 3: return cmdBuf[6];  // 右摇杆 Y
        default: return 0xFF;
    }
}

uint16_t PS2::readKey(){
    uint8_t cmdBuf[] = {0x01, 0x42, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    sendCommand(cmdBuf, sizeof(cmdBuf));
    if (cmdBuf[2] != 0x5A) return 0xFFFF;

    uint16_t keyData = (cmdBuf[4] << 8)| cmdBuf[3];
    return keyData;
}

bool PS2::isPressed(uint16_t keyData, uint16_t keyMask){
    return !(keyData & keyMask);
}

