#include "mbed.h"
#include "nrf24l01.h"

//NRF24L01(mosi,  miso,  sck,  csn,  ce)
NRF24L01 radio(D11, D12, D13, D2, D3);

BufferedSerial pc(USBTX, USBRX, 115200);

int main(){
    pc.write("Starting NRF24L01...\n", strlen("Starting NRF24L01...\n"));
    radio.init();

    uint8_t TX_address[5] = {'N','R','F','2','4'};
    uint8_t RX_address[5] = {'N','R','F','2','4'};
    radio.setTxAddress(TX_address, 5);
    radio.setRxAddress(RX_address, 5);

    u_int8_t text_message[5] = {'H','E','L','L','O'};
    
    // while (true){
    //     radio.sendPayload(text_message, 5);
    //     pc.write("Send: HELLO \n", strlen("Send: HELLO \n"));

    //     ThisThread::sleep_for(500ms);
    //     if (radio.dataAvailable()){
    //         uint8_t buffer[32] = {0};
    //         radio.receivePayload(buffer, 5);
            
    //         pc.write("Received: ", strlen("Received: "));
    //         pc.write((char*)buffer, 5);
    //         pc.write("\n", 1);
    //     }else{
    //         pc.write("No data received\n", strlen("No data received\n"));
    //     }

    //     ThisThread::sleep_for(1000ms);
    // }


    while (true) {
    // 设置为发射模式
    radio.setTxMode();
    radio.sendPayload(text_message, 5);
    pc.write("Send: HELLO \n", strlen("Send: HELLO \n"));
    ThisThread::sleep_for(10ms);


    // 设置为接收模式
    radio.setRxMode();
    ThisThread::sleep_for(10ms); // 给接收模式一点切换时间

    if (radio.dataAvailable()) {
        uint8_t buffer[32] = {0};
        radio.receivePayload(buffer, 5);
        pc.write("Received: ", strlen("Received: "));
        pc.write((char*)buffer, 5);
        pc.write("\n", 1);
    } else {
        pc.write("No data received\n", strlen("No data received\n"));
    }

    ThisThread::sleep_for(1000ms);
}


      




}



