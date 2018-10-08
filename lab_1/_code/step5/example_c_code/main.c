#include <avr/io.h>
#include <util/delay.h>
#include <Arduino.h>
#include <fsm.h>

// ########## INITIALIZATION #############

void init_led() { pinMode(13, OUTPUT); }
void init_button() { pinMode(10, INPUT); }
void setup() { init_led(); init_button(); }

// ##### ELECTRONICS AND LOGICAL COMPONENTS

// ## LED Helper
boolean led_on = true;
void change_state_led(){
  if (led_on){ digitalWrite(13, LOW); }
  else { digitalWrite(13, HIGH); }
  led_on = !led_on;
}

// ###### Message FLAG framework
boolean is_present(int messageQueue) { return messageQueue == 1; }
boolean LED_FLAG   = false;

void button_push() {
  if (digitalRead(10) == HIGH) { LED_FLAG = true; }
}

// ###### Message consumers
void led_pull() {
  // do nothing if no message present
  if(!is_present(LED_FLAG)) { return; }
  change_state_led(); // business code
  LED_FLAG = 0;        // remove flag
}

int main(void)
{
  setup();
  while(1) {
    // message producer
    button_push();
    // message consumer
    led_pull();
    // frequency
    _delay_ms(100);
  }
  return 0;
}
