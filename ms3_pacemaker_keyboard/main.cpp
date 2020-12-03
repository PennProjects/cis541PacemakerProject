#include <mbed.h>
#include "pacemaker.h"
#include "randomheart.h"
#include "TextLCD.h"
//#include "SerialStream.h"
//#include "BufferedSerial.h"

//BufferedSerial serial(USBTX, USBRX, 9600);
//SerialStream<BufferedSerial> pc(serial);
SPI spi(p11, p12, p13); // mosi, miso, sclk
DigitalOut cs(p5); // set PIN5 to ChipSelect Pin 
TextLCD lcd(p15, p16, p17, p18, p19, p20, TextLCD::LCD16x2);  // SETUP LCD 
Serial pc(USBTX, USBRX); // tx, rx

DigitalOut led1(LED1); // define the LED pin
DigitalOut led4(LED4);
Ticker myTick; 

void flash1(void) {     // function to call every tick
  led1 = !led1;                 //  toggle the LED
}

void flash4(void) {     // function to call every tick
  led4 = !led4;                 //  toggle the LED
}

Timer Obs; 

int spi_read, spi_write;

int main()
{
    Pacemaker pace;
    RandomHeart rh; 

    // SPI Configuration
    spi.format(8,3);        // Setup:  bit data, high steady state clock, 2nd edge capture
    spi.frequency(1000000); //1MHz
    cs = 0; // Select device

    
    rh.init(); 
    pace.init(); 
    
    event x;
    //Obs.start(); 
    while (true) {


        // SPI code
        spi_write = 2;
        // int spi_read =  spi.write(spi_write); //send value
        spi_read = pc.getc(); 
        
        if (spi_read == '1'){

            x = pace.dispatch(SENSE); 
            flash1();
            lcd.cls();  
            lcd.printf("sensed \n time = %.2f", pace.CLK);
            pc.printf("sensed \n time = %.2f", pace.CLK);
            flash1();


        }
        else {
            x = pace.dispatch(PACE);
            if (x == PACE) {

            //SPI code
            spi_write = 1;
            int spi_read =  spi.write(spi_write); //send value

            flash4();
            lcd.cls();  
            lcd.printf("paced \n time = %.2f", pace.CLK);
            pc.printf("paced \n time = %.2f", pace.CLK);
            flash4(); 

            }
        }        
            
    }
}