#include "mbed.h"
#include "pacemaker.h"
#include "randomheart.h"
#include "TextLCD.h"

Serial pc(USBTX, USBRX); // tx, rx

SPI spi(p11, p12, p13); // mosi, miso, sclk
DigitalOut cs(p5); // set PIN5 to ChipSelect Pin 
TextLCD lcd(p15, p16, p17, p18, p19, p20, TextLCD::LCD16x2);  // SETUP LCD 

DigitalOut led1(LED1); // PACE
DigitalOut led2(LED2); // TOO LOW 
DigitalOut led3(LED3); // TOO HIGH 
DigitalOut led4(LED4); // SENSE 

Pacemaker pace;
Mutex mux; 
event x;
int beat; 
Timer t; 

void flash1(void) {     // function to call every tick
  led1 = !led1;                 //  toggle the LED
}

void flash4(void) {     // function to call every tick
  led4 = !led4;                 //  toggle the LED
}

void led2_fun() { // Too slow 
    led2 = 1; 
    pc.printf("[ALARM] Heart beating too slow\n"); 
}
void led3_fun() { // too fast 
    led3 = 1; 
    pc.printf("[ALARM] Heart beating too fast\n");
}

void pacemaker_t_func() {
    while (true) {
        mux.lock(); 
        x = pace.dispatch(PACE);
        wait_us(50);  
        mux.unlock(); 
    }
}

void alarm_func() {
    double d_time; 
    while (true) {
        d_time = t.read_ms(); 
        if (d_time >= 5000) { 
            if (beat <= 3) { // too slow alarm
                led2_fun(); 
            } else if (beat >= 8) { // too fast alarm
                led3_fun(); 
            }
            t.stop(); 
            t.reset(); 
            t.start(); 
            beat = 0; 
        }
    }
}


int spi_read, spi_write;


int main()
{
    // SPI Configuration
    spi.format(8,3);        // Setup:  bit data, high steady state clock, 2nd edge capture
    spi.frequency(1000000); //1MHz
     cs = 0; // Select device


    Thread pacemaker_thread, alarm_thread;
    pacemaker_thread.start(pacemaker_t_func); 
    alarm_thread.start(alarm_func);

    
    pace.init(); 

    while (true) {
        t.start(); 
        // SPI code
        spi_write = 2;
        int spi_read =  spi.write(spi_write); //send value
        if (spi_read == 1){
            mux.lock(); 
            x = pace.dispatch(SENSE); 
            beat++; 
            mux.unlock(); 
            flash1();
            lcd.cls();  
            lcd.printf("sensed \n time = %.2f", pace.CLK);
            flash1(); 
        }
        else {
            mux.lock(); 
            x = pace.dispatch(PACE);
            if (x == PACE) {
                beat++; 
                flash4();
                lcd.cls();  
                lcd.printf("paced \n time = %.2f", pace.CLK);
                flash4(); 
                spi_write = 1;
                int spi_read =  spi.write(spi_write); //send value
                }
            mux.unlock(); 
        }   
    }
}
