#include <avr/io.h>
#include <util/delay.h>
#include <Arduino.h>

//Blinks the led one cycle over two.
//Now ports can be accessed by digitalWrite/digitalRead

// declaration of global variables
int led = 13;    // Synchronized with the shield led
boolean led_on;  // it is C++ you have access to boolean vars.

int button = 10; 

//Global variables for 7 segment
int a = 1;  //For displaying segment "a"
int b = 2;  //For displaying segment "b"
int c = 3;  //For displaying segment "c"
int d = 4;  //For displaying segment "d"
int e = 5;  //For displaying segment "e"
int f = 6;  //For displaying segment "f"
int g = 7;  //For displaying segment "g"


void setup() {               
  //Setup for LED on pin 13
  pinMode(led, OUTPUT);  
  led_on=true;
  //do not forget to setup the 7 seg and the button
  int i;
  for (i = a; i <= g; i++){
    pinMode(i, OUTPUT);  // A
  }
  // and global state variables
}

void change_state_led(){
  if (led_on){
    digitalWrite(led, LOW);
  } else
    digitalWrite(led, HIGH);
  led_on = !led_on;
}

void turnOff() //turn off the 7seg (CC) 
{
  int i;
  for (i = a; i <= g; i++){ // this could be prettier
    digitalWrite(i,HIGH); // change into HIGH for common anode
  }
}


void displayDigit(int digit)
{
  turnOff();
  //Conditions for displaying segment a
  if (digit != 1 && digit != 4)
    digitalWrite(a,LOW); // change into HIGH for common cathode
  if (digit != 5 && digit != 6)
    digitalWrite(b, LOW);
  if (digit != 2)
    digitalWrite(c, LOW);
  if (digit != 4 && digit != 1 && digit != 7)
    digitalWrite(d, LOW);
  if (digit == 2 | digit == 6 | digit == 8 | digit == 0)
    digitalWrite(e, LOW);
  if (digit != 1 && digit != 2 && digit != 3 && digit != 7)
    digitalWrite(f, LOW);
  if (digit != 1 && digit != 7 && digit != 0)
    digitalWrite(g, LOW);
}

bool buttonPressed(){
  if (digitalRead(button)) 
    return true;
  else 
    return false;
}

int main(void)
{
  setup();
  int digit = 0;
  while(1)
    { 
      digit = (digit + 1) % 10;
      displayDigit(digit);

      if (buttonPressed()) {
        change_state_led();
      }

      _delay_ms(1000);
      
    }
  return 0;
}
