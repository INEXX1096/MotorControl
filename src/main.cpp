#include "mbed.h"
#include "nrf24l01.h"

//NRF24L01(mosi,  miso,  sck,  csn,  ce)
NRF24L01 radio(D11, D12, D13, D2, D3);

BufferedSerial pc(USBTX, USBRX, 115200);

int main(){
    pc.write("Starting NRF24L01...\n", strlen("Starting NRF24L01...\n"));
    radio.init();

    uint8_t config = radio.readRegister(0x00);

    char buf[64];
    sprintf(buf, "CONFIG register: 0x%02X\n", config);
    pc.write(buf, strlen(buf));
}

//test 1 - pass
// #include "mbed.h"

// BufferedSerial pc(USBTX, USBRX, 115200);

// int main() {
//     pc.write("Hello from STM32!\n", strlen("Hello from STM32!\n"));
//     while (1) {
//         // 留一个死循环，方便看串口有没有挂
//     }
// }

//test 2 - pass
// #include "mbed.h"
// #include "nrf24l01.h"

// BufferedSerial pc(USBTX, USBRX, 115200);

// // 仅创建对象，不初始化
// //NRF24L01(mosi,  miso,  sck,  csn,  ce);
// NRF24L01 radio(D11, D12, D13, D2, D3);

// int main() {
//     pc.write("nRF connected but not used yet\n", strlen("nRF connected but not used yet\n"));
//     while (1) {
//         // 保持循环
//     }
// }
//test 3 - pass
// #include "mbed.h"
// #include "nrf24l01.h"

// BufferedSerial pc(USBTX, USBRX, 115200);

// NRF24L01 radio(D11, D12, D13, D2, D3);

// int main() {
//     pc.write("Trying to init nRF...\n", strlen("Trying to init nRF...\n"));

//     radio.init();  // 👈 如果供电不足，程序可能会卡死在这里

//     pc.write("nRF init done!\n", strlen("nRF init done!\n"));

//     while (1) {}
// }

