#include <mbed.h>
#include "pacemaker.h"
#include "randomheart.h"
#include "TextLCD.h"
//#include "SerialStream.h"
//#include "BufferedSerial.h"

//BufferedSerial serial(USBTX, USBRX, 9600);
//SerialStream<BufferedSerial> pc(serial);
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
    Pacemaker pace;
    RandomHeart rh; 
    
    rh.init(); 
    pace.init(); 
    
    event x;
    //Obs.start(); 
    while (true) {

        x = pace.dispatch(x); 
        if (x == PACE) {
            flash4();
            lcd.cls();  
            lcd.printf("paced \n time = %.2f", pace.CLK);
            flash4(); 
        }
        x = rh.dispatch(x);
        if (x == SENSE) {
            flash1(); 
            lcd.cls(); 
            lcd.printf("self beat \n time = %.2f", pace.CLK);
            flash1(); 
        }
            
    }
}