//counts, resets when button is pressed 
//led on and off every two cycles.
#ifndef _GLUE_ARDUINO
#define _GLUE_ARDUINO

#include <Arduino.h>

extern int a,b,c,d,e,f,g;//7seg
extern int led;
extern int button;
extern int i;
extern int led_on;
extern int button_state ;

void setup();
void turnOff(); // Not Yet Implemented
void displayDigit(int digit); // Not Yet Implemented
#endif
