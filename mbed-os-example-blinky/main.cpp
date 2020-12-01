/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"
#include <cstdio>


// Blinking rate in milliseconds
#define BLINKING_RATE     1000ms


int main()
{
    // Initialise the digital pin LED1 as an output
    DigitalOut led(LED1);

    while (true) {
        printf("testing");
        led = !led;
        ThisThread::sleep_for(BLINKING_RATE);
    }
}
