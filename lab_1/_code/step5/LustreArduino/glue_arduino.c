//Interfacing with arduino led + 7segment

#include "glue_arduino.h"

int led = 13; // Synchronized with the shield led
int led_on = 1; // led state
int button = 10; //button
int button_state= 0;

// TODO : add some more global variables

void setup() {               
  //Setup for LED on pin 
  pinMode(led, OUTPUT);  
  
  led_on=1;//true

  //TODO implement the rest !
  return;
}

void turnOff() //TODO (copy paste from one preceding step !)
{
  return;
}


void displayDigit(int digit)
{
  return; // TODO!
}
