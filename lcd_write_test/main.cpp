
// Connections
// As shown in link bellow
//Changes: Connect Vcc/All +ve V to : VU ( 2nd pin on right for 5V)
//Vo is connected through a 10k pot to VCC and GND OR directly to ground for max contrast.


//Library : https://os.mbed.com/components/HD44780-Text-LCD/


#include "mbed.h"
#include "TextLCD.h"
 
TextLCD lcd(p15, p16, p17, p18, p19, p20); // rs, e, d4-d7
 
int main() {
    lcd.printf("CIS 541 Test\n");
}