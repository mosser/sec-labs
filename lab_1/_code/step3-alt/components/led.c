

boolean led_on = true;

void init_led() { pinMode(13, OUTPUT); }

void change_state_led(){
  if (led_on){ digitalWrite(13, LOW); } else { digitalWrite(13, HIGH); }
  led_on = !led_on;
}
