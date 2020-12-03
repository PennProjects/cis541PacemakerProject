#include <mbed.h>
#include "pacemaker.h"
#include "randomheart.h"
#include "TextLCD.h"
//#include "SerialStream.h"
//#include "BufferedSerial.h"

//BufferedSerial serial(USBTX, USBRX, 9600);
//SerialStream<BufferedSerial> pc(serial);
SPISlave device(p11, p12, p13, p14); // mosi, miso, sclk, ChipSelect
TextLCD lcd(p15, p16, p17, p18, p19, p20, TextLCD::LCD16x2);  // SETUP LCD 

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

int main()
{
    RandomHeart rh; 
    int slaveWrite;

    // SPI Coonfiguration 
    device.format(8,3);        // Setup:  bit data, high steady state clock, 2nd edge capture
    device.frequency();  // 1MHz clockrate 
    
    rh.init(); 
    
    event x;
    //Obs.start(); 
    while (true) {

        // x = pace.dispatch(x); 
        // if (x == PACE) {
        //     flash4();
        //     lcd.cls();  
        //     lcd.printf("paced \n time = %.2f", pace.CLK);
        //     flash4(); 
        // }

        //  SPI communiation
        // if (device.receive()) {
            int valueFromMaster = device.read(); // read value from master 

            if(valueFromMaster != 1){
                //2 = Pacemaker wants to read
                x = rh.dispatch(SENSE);
                if (x == SENSE) {
                    flash1(); 
                    lcd.cls(); 
                    lcd.printf("self beat \n time = %.2f", rh.sinceBeat);
                     flash1(); 
                    device.reply(1);  //Reply sense   
                }
            }
            else if (valueFromMaster ==1 ) { //Pace Signal
                x = rh.dispatch(PACE); 

                flash4(); 
                lcd.cls(); 
                lcd.printf("paced \n time = %.2f", rh.sinceBeat);
                flash4(); 
            } 
        // }             
    }
            
}
