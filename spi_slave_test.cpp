/*
 * Copyright (c) 2006-2020 Arm Limited and affiliates.
 * SPDX-License-Identifier: Apache-2.0
 */
#include "mbed.h"
#include "TextLCD.h"

SPI spi(p11, p12, p13); // mosi, miso, sclk
DigitalOut cs(p5); // set PIN5 to ChipSelect Pin 
TextLCD lcd(p15, p16, p17, p18, p19, p20, TextLCD::LCD16x2);  // SETUP LCD 
Serial pc(USBTX, USBRX); // tx, rx

int main() {
 
    int valueToSendToSlave = 20; // Starting value only, this increments
    spi.format(8,3);        // Setup:  bit data, high steady state clock, 2nd edge capture
    spi.frequency(1000000); //1MHz
 
    pc.printf("======================================================\r\n");
    pc.printf("Press any key to start...\r\n");
    pc.getc(); // wait for keyboard
 
    int counter = 1;
    while (1) {

        cs = 0; // Select device
        int dataFromSlave =  spi.write(valueToSendToSlave); //send value
        cs = 1; // Deselect device
        lcd.cls(); // clear LCD screen 
        lcd.printf("Value to send = %d ",valueToSendToSlave);
        lcd.printf("returns %d\r", dataFromSlave);
        
        valueToSendToSlave++;
        
        wait_us(2000000); // Wait for 2 seconds for readability only
        
    }
}
