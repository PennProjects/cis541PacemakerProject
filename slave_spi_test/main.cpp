#include "mbed.h"
#include "TextLCD.h"
 
SPISlave device(p11, p12, p13, p14); // mosi, miso, sclk, ChipSelect
TextLCD lcd(p15, p16, p17, p18, p19, p20, TextLCD::LCD16x2);  // SETUP LCD 
Serial pc(USBTX, USBRX); // tx, rx
 
int main() {
 
    int counter = 1;
 
    device.format(8,3);        // Setup:  bit data, high steady state clock, 2nd edge capture
    device.frequency();  // 1MHz clockrate 
 
    // int reply = 99;
    device.reply(16);              // Prime SPI with first reply
    device.reply(16);              // Prime SPI with first reply, again
 
    pc.printf("======================================================\r\n");
    pc.printf("Startup Next reply will be %d\r\n", reply);
 
    while (1) {
        if (device.receive()) {
            int valueFromMaster = device.read(); // read value from master 
            int slaveValue = valueFromMaster*2;
            device.reply(slaveValue);              // Prime SPI with next reply
            pc.printf("    Received value from Master (%d) Next reply will be %d \r\n", valueFromMaster, slaveValue);
            lcd.cls(); // clear LCD screen      
            lcd.printf("Return : %d\r", valueFromMaster);
            lcd.printf("sent :  %d ",slaveValue);
        }
    }
}
