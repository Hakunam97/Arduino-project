void setup() {
  remote_setup();
  motor_setup();
  light_setup();
  horn_setup();
  servo_setup();
  distance_sensor_setup();
}

void loop() {
  remote_loop();
  motor_loop();
  light_loop(); 
  brightness_sensor_loop(); 
  horn_loop();
  distance_sensor_loop(); 
  emergency_loop();
  automatic_driving_loop();
}

void remote_setup() {
  Serial.begin(9600);  
}

void remote_loop() {
  check_remote_input();
  distribute_remote_input();
}

char remote_input;
bool remote_input_changed = false;

enum {
  AUTOMATIC = 'X',
  MANUAL = 'x',
}; /*AUTOMAITC DRIVING*/

bool AUTOMATIC_DRIVING_ENABLE = false;

void check_remote_input() {
  if(Serial.available()) {
    char r_data = Serial.read();
  
    if(r_data == AUTOMATIC) {
      AUTOMATIC_DRIVING_ENABLE = true;
      return;
    }
  
    if(AUTOMATIC_DRIVING_ENABLE) {
      if(r_data == MANUAL) {
        AUTOMATIC_DRIVING_ENABLE = false;
      } else return;
    } 
  
    // 비상시 사용자 입력 막기
    extern bool EMERGENCY_STATE_ENABLE;
    if(EMERGENCY_STATE_ENABLE) return;
    
    if(r_data != remote_input) {
      remote_input = r_data;
      remote_input_changed = true;
    }
  }
}

enum {
  GOFORWARD = 'f',
  GOBACKWARD = 'b',
  TURNLEFT = 'l',
  TURNRIGHT = 'r',
  STOP = 's', 
  GOFORWARDLEFT = 'g',
  GOFORWARDRIGHT = 'i',
  GOBACKWARDLEFT = 'h',
  GOBACKWARDRIGHT = 'j',
}; /*SERIAL*/

enum { 
  GOFORWARDBLUETOOTH = 'F',
  GOBACKWARDBLUETOOTH = 'B',
  TURNLEFTBLUETOOTH = 'L',
  TURNRIGHTBLUETOOTH = 'R',
  STOPBLUETOOTH = 'S', 
  GOFORWARDLEFTBLUETOOTH = 'G',
  GOFORWARDRIGHTBLUETOOTH = 'I',
  GOBACKWARDLEFTBLUETOOTH = 'H',
  GOBACKWARDRIGHTBLUETOOTH = 'J',
}; /*BLUETOOTH*/ 

enum {
  SPEED_0 = '0',
  SPEED_1 = '1',
  SPEED_2 = '2',
  SPEED_3 = '3',
  SPEED_4 = '4',
  SPEED_5 = '5',
  SPEED_6 = '6',
  SPEED_7 = '7',
  SPEED_8 = '8',
  SPEED_9 = '9',
  SPEED_10 = 'q',   
}; /*SPEED*/

enum {
  FRONTLIGHTON = 'W',
  FRONTLIGHTOFF = 'w',
  REARLIGHTON = 'U',
  REARLIGHTOFF = 'u',
  ALLLIGHTON = 'A',
  ALLLIGHTOFF = 'a',
  REARLEFTBLINK = 'z',
  REARRIGHTBLINK = 'c',      
}; /*LIGHT*/

 enum {
  HORN = 'V',
}; /*HORN*/

#define MAX_SPEED 255
#define MIN_SPEED 0

char driving_action = STOP;
bool driving_action_changed = false;

char driving_speed_input = SPEED_0;
int driving_speed = MIN_SPEED;
bool driving_speed_changed = false;

char light_onoff = ALLLIGHTOFF;
bool light_onoff_changed = false;

char light_blink;
bool light_blink_changed = false;

bool horn_state_changed = false;

void distribute_remote_input() {
  if(remote_input_changed) {
    remote_input_changed = false;
  
    // 대문자를 소문자로 변경
    if(remote_input == GOFORWARDBLUETOOTH ||
      remote_input == GOBACKWARDBLUETOOTH ||
      remote_input == TURNLEFTBLUETOOTH ||
      remote_input == TURNRIGHTBLUETOOTH ||
      remote_input == STOPBLUETOOTH ||
      remote_input == GOFORWARDLEFTBLUETOOTH ||
      remote_input == GOFORWARDRIGHTBLUETOOTH ||
      remote_input == GOBACKWARDLEFTBLUETOOTH ||
      remote_input == GOBACKWARDRIGHTBLUETOOTH) {
      remote_input = remote_input - 'A' + 'a';
    }

    if(remote_input == GOFORWARD ||
      remote_input == GOBACKWARD ||
      remote_input == TURNLEFT ||
      remote_input == TURNRIGHT ||
      remote_input == STOP ||
      remote_input == GOFORWARDLEFT ||
      remote_input == GOFORWARDRIGHT ||
      remote_input == GOBACKWARDLEFT ||
      remote_input == GOBACKWARDRIGHT) {
      driving_action = remote_input;
      driving_action_changed = true; 
    } else if(remote_input == SPEED_0 ||
      remote_input == SPEED_1 ||
      remote_input == SPEED_2 ||
      remote_input == SPEED_3 ||
      remote_input == SPEED_4 ||
      remote_input == SPEED_5 ||
      remote_input == SPEED_6 ||
      remote_input == SPEED_7 ||
      remote_input == SPEED_8 ||
      remote_input == SPEED_9 ||
      remote_input == SPEED_10) {
      driving_speed_input = remote_input;
      driving_speed_changed = true;        
    } else if(remote_input == FRONTLIGHTON ||
      remote_input == FRONTLIGHTOFF ||
      remote_input == REARLIGHTON ||
      remote_input == REARLIGHTOFF ||
      remote_input == ALLLIGHTON ||
      remote_input == ALLLIGHTOFF) {
      light_onoff = remote_input;
      light_onoff_changed = true;
    } else if(remote_input == REARLEFTBLINK ||
      remote_input == REARRIGHTBLINK) {
      light_blink = remote_input;
      light_blink_changed = true;
    } else if(remote_input == HORN) {        
       horn_state_changed = true;
    }
  }
}
