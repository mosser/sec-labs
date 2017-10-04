#include <avr/io.h>
#include <util/delay.h>
#include <Arduino.h>
#include <counter.h>
#include <led.h>
#include <button.h>

// ########## INITIALIZATION #############

void init_button() { pinMode(10, INPUT); }

void setup() {
  init_counter();
  init_led();
  init_button();
}


// ###### Message FLAG framework

boolean is_present(int messageQueue) { return messageQueue == 1; }

// message FLAGs
boolean LED_FLAG   = false;
boolean RESET_FLAG = false;
boolean CONST_FLAG = false;

// ##### Message producers

void button_push() {
  if (digitalRead(10) == HIGH) {
    LED_FLAG = true; RESET_FLAG = true;
  }
}

void const_push() { CONST_FLAG = true; }

// ###### Message consumers

void led_pull() {
  if(!is_present(LED_FLAG)) { return; } // do nothing if no message present
  change_state_led(); // business code
  LED_FLAG = 0;        // remove flag
}

void incr_pull() {
  if(!is_present(CONST_FLAG)) { return; }
  displayCounter(); incrementCounter();
  CONST_FLAG = 0;
}

void reset_pull() {
  if(!is_present(RESET_FLAG)) { return; }
  resetCounter();
  RESET_FLAG = 0;
}

int main(void)
{
  setup();
  while(1) {
    // message producer
    button_push();
    const_push();
    // message consumer
    led_pull();
    incr_pull();
    reset_pull();
    // frequency
    _delay_ms(500);
  }
  return 0;
}
