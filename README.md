# README

5push: 目前stm32L475 用ps2连接（调换了cmd和dat口， 输出从0xFF变成0x00，似乎是有一些变好，不确定是不是gpio的问题），接下来要测试的是

🧪推荐测试步骤
换成 3.3V 供电试试

拔掉手柄后单独测 STM32 的 CLK、CMD、CS 是否能输出

修改 delayUs 为 15~20us，保证时钟频率够慢

用示波器（如果有）查看 CLK 和 CMD 是否有波形

重新验证 CMD / DAT 没接反



同时，要是实在不行，就使用usb作为ps2的接口，暂时放弃spi和gpio。

测试ps2 cs接口时， 电压显示2V，低于3,3V，怀疑可能是ps2手柄内部连线有短路或者其他的问题。



接下来的任务：

1. 用usb ps2测试
2. stlink到了，用stlink测试F103的烧录和编写nrf24l01代码，用来测试nrf24l01 在l475和F103板子上的传输如何
3. 移植L475的代码到F407上
4. 。。。