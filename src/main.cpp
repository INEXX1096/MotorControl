#include "mbed.h"
#include "nrf24l01.h"
#include "ps2.h"

//NRF24L01(mosi,  miso,  sck,  csn,  ce)
NRF24L01 radio(D11, D12, D13, D2, D3);
//PS2(clk, cmd(DO), dat(D1), cs)
PS2 ps2_device(PD_1, PD_4, PD_3, PD_5);
// PS2 ps2_device(PA_0, PA_2, PA_3, PA_1);

BufferedSerial pc(USBTX, USBRX, 115200);

// int main(){
//     pc.write("Starting NRF24L01...\n", strlen("Starting NRF24L01...\n"));
//     radio.init();

//     uint8_t TX_address[5] = {'N','R','F','2','4'};
//     uint8_t RX_address[5] = {'N','R','F','2','4'};
//     radio.setTxAddress(TX_address, 5);
//     radio.setRxAddress(RX_address, 5);

//     uint8_t text_message[5] = {'H','E','L','L','O'};

//     while (true) {
//     // 设置为发射模式
//     radio.setTxMode();
//     radio.sendPayload(text_message, 5);
//     pc.write("Send: HELLO \n", strlen("Send: HELLO \n"));
//     ThisThread::sleep_for(10ms);


//     // 设置为接收模式
//     radio.setRxMode();
//     ThisThread::sleep_for(10ms); // 给接收模式一点切换时间

//     if (radio.dataAvailable()) {
//         uint8_t buffer[32] = {0};
//         radio.receivePayload(buffer, 5);
//         pc.write("Received: ", strlen("Received: "));
//         pc.write((char*)buffer, 5);
//         pc.write("\n", 1);
//     } else {
//         pc.write("No data received\n", strlen("No data received\n"));
//     }

//     ThisThread::sleep_for(1000ms);
// }


      




// }

int main(){
    pc.write("Starting Ps2 Controller...\n", strlen("Starting Ps2 Controller...\n"));
    ps2_device.init();

    if (!ps2_device.setInit()){
        pc.write("PS2 controller initialization failed. Check wiring.\n", strlen("PS2 controller initialization failed. Check wiring.\n"));
        while(1) ThisThread::sleep_for(1s); // 初始化失败，停住
    }

    while (true){
        uint16_t key = ps2_device.readKey();
        char buf[64];

        int len = sprintf(buf, "PS2 Key Data: 0x%04X\n", key);
        pc.write(buf,len);

        uint8_t analog_x = ps2_device.readAnalog(0);
        len = sprintf(buf, "PS2 Analog X: %d\n", analog_x);
        pc.write(buf, len);

        ThisThread::sleep_for(500ms);
    }
}


