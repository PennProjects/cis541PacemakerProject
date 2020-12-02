#include "mbed.h"
#include "TextLCD.h"
 
TextLCD lcd(p15, p16, p17, p18, p19, p20); // rs, e, d4-d7
 
int main() {
    lcd.printf("Jal Panchal\n");
}