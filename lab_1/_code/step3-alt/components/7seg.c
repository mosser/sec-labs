#include <Arduino.h>

void init_7Seg() {
  for(int i = 0; i < 8 ; i++) { pinMode(i, OUTPUT); }
}

void turnOff() {
  for(int i = 0; i < 8 ; i++) { digitalWrite(i, HIGH); }
}

void displayDigit(int digit)
{
  turnOff();
  //Conditions for displaying segment a
  if(digit!=1 && digit != 4)
    digitalWrite(1,LOW);
 //Conditions for displaying segment b
  if(digit != 5 && digit != 6)
    digitalWrite(2,LOW);
 //Conditions for displaying segment c
  if(digit !=2)
    digitalWrite(3,LOW);
  //Conditions for displaying segment d
  if(digit != 1 && digit !=4 && digit !=7)
    digitalWrite(4,LOW);
 //Conditions for displaying segment e
  if(digit == 2 || digit ==6 || digit == 8 || digit==0)
    digitalWrite(5,LOW);
 //Conditions for displaying segment f
  if(digit != 1 && digit !=2 && digit!=3 && digit !=7)
    digitalWrite(6,LOW);
  if (digit!=0 && digit!=1 && digit !=7)
    digitalWrite(7,LOW);
}
