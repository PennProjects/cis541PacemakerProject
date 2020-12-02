#include "mbed.h"
 
SPISlave device(p11, p12, p13, p14); // mosi, miso, sclk, ChipSelect
Serial pc(USBTX, USBRX); // tx, rx
 
int main() {
 
    int counter = 1;
 
    device.format(8,3);        // Setup:  bit data, high steady state clock, 2nd edge capture
    device.frequency();  // 1MHz clockrate 
 
    int reply = 99;
    device.reply(reply);              // Prime SPI with first reply
    device.reply(reply);              // Prime SPI with first reply, again
 
    pc.printf("======================================================\r\n");
    pc.printf("Startup Next reply will be %d\r\n", reply);
 
    while (1) {
        if (device.receive()) {
            int valueFromMaster = device.read(); // read value from master 
            pc.printf("%d Something rxvd, and should have replied with %d\n\r", counter++, reply);
            device.reply(++reply);              // Prime SPI with next reply
            pc.printf("    Received value from Master (%d) Next reply will be %d \r\n", valueFromMaster, reply);
        }
    }
}
