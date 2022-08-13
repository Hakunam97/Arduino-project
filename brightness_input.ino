void brightness_sensor_loop() {
  check_brightness_sensor_input();
  distribute_brightness_sensor_input();
}

int brightness_input;
bool brightness_input_changed = false;

void check_brightness_sensor_input() {
  static unsigned long prev_millis = 0;
  const unsigned long interval_millis = 500;

  unsigned long curr_millis = millis();
  if(curr_millis - prev_millis >= interval_millis) {
    prev_millis = curr_millis;
    
    brightness_input = analogRead(A0);
    brightness_input_changed = true;
    
    Serial.print("brightness:");
    Serial.println(brightness_input);
  }  
}

enum {
  DIM = 300,
  BRIGHT = 700,
};

char light_onoff_by_brightness = ALLLIGHTOFF;

void distribute_brightness_sensor_input() {  
  if(brightness_input_changed) {
    brightness_input_changed = false;
  
    Serial.println(light_onoff_by_brightness);
    Serial.println(brightness_input);
  
    if(light_onoff_by_brightness == ALLLIGHTOFF) {
      if(brightness_input <= DIM) {
        light_onoff_by_brightness = ALLLIGHTON;
        light_onoff = ALLLIGHTON;
        light_onoff_changed = true;
      }
    } else if(light_onoff_by_brightness == ALLLIGHTON) {
      if(brightness_input >= BRIGHT) {
        light_onoff_by_brightness = ALLLIGHTOFF;
        light_onoff = ALLLIGHTOFF;
        light_onoff_changed = true;
      }
    }
  }
}
