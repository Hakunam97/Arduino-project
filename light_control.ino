const int front_left_pin = 11;
const int front_right_pin = 16; //A2
const int rear_left_pin = 12;
const int rear_right_pin = 15; //A1

void light_setup() {
  pinMode(front_left_pin, OUTPUT);
  pinMode(front_right_pin, OUTPUT);
  pinMode(rear_left_pin, OUTPUT);
  pinMode(rear_right_pin, OUTPUT);

  digitalWrite(front_left_pin, LOW);
  digitalWrite(front_right_pin, LOW);
  digitalWrite(rear_left_pin, LOW);
  digitalWrite(rear_right_pin, LOW);
}

void light_loop() {
  process_light_onoff();
  process_light_blink();
  process_rear_left_blink();
  process_rear_right_blink();
}

void process_light_onoff() {
  if(light_onoff_changed ) {
    light_onoff_changed = false;
    
    if(light_onoff == FRONTLIGHTON) {
      front_light_on();     
    } else if(light_onoff == FRONTLIGHTOFF) {
      front_light_off();    
    } else if(light_onoff == REARLIGHTON) {
      rear_light_on();  
    } else if(light_onoff == REARLIGHTOFF) {
      rear_light_off();  
    } else if(light_onoff == ALLLIGHTON) {
      all_light_on();
    } else if(light_onoff == ALLLIGHTOFF) {
      all_light_off();
    } 
  }
}

void front_light_on() {
  digitalWrite(front_left_pin, HIGH);
  digitalWrite(front_right_pin, HIGH);
}

void front_light_off() {
  digitalWrite(front_left_pin, LOW);
  digitalWrite(front_right_pin, LOW);
}

void rear_light_on() {
  digitalWrite(rear_left_pin, HIGH);
  digitalWrite(rear_right_pin, HIGH);
}
    
void rear_light_off() {
  digitalWrite(rear_left_pin, LOW);
  digitalWrite(rear_right_pin, LOW);
}

void all_light_on() {
  front_light_on();
  rear_light_on();
}
    
void all_light_off() {
  front_light_off();
  rear_light_off();
} 

bool rear_left_blink = false;
bool rear_right_blink = false;

void process_light_blink() {  
  if(light_blink_changed ) {
    light_blink_changed = false;
  
    if(light_blink == REARLEFTBLINK) {
      rear_left_blink = true;
      rear_right_blink = false;      
    } else if(light_blink == REARRIGHTBLINK) {
      rear_left_blink = false;
      rear_right_blink = true;       
    }
  }
}

void process_rear_left_blink() {  
  static unsigned long prev_millis = 0;
  const unsigned long interval_millis = 500;

  static int blink_cnt = 0;
  
  if(rear_left_blink) {
  unsigned long curr_millis = millis();
    if(curr_millis - prev_millis >= interval_millis) {
      prev_millis = curr_millis;
  
      blink_cnt++;
      if(blink_cnt == 10) {
        blink_cnt = 0;
        rear_left_blink = false;
      light_onoff_changed = true;
      } else {
        digitalWrite(rear_left_pin, blink_cnt%2);
      }
    }    
  }  
}

void process_rear_right_blink() {
  static unsigned long prev_millis = 0;
  const unsigned long interval_millis = 500;

  static int blink_cnt = 0;
  
  if(rear_right_blink) {
    unsigned long curr_millis = millis();
    if(curr_millis - prev_millis >= interval_millis) {
      prev_millis = curr_millis;
  
      blink_cnt++;
      if(blink_cnt == 10) {
        blink_cnt = 0;
        rear_right_blink = false;
        light_onoff_changed = true;
      } else {
        digitalWrite(rear_right_pin, blink_cnt%2);
      }
    }    
  }    
}
