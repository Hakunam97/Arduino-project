#include <PinChangeInterrupt.h>

const int trig_pin = 8;
const int echo_pin = 13;

void distance_sensor_setup() {
  pinMode(trig_pin, OUTPUT);
  pinMode(echo_pin, INPUT);

  attachPCINT(digitalPinToPCINT(echo_pin), echoIsr, CHANGE);
}

void distance_sensor_loop() {
  triggering_distance_sensor();
  check_distance_sensor_input();
}

unsigned long distance_input = 60; // cm
bool distance_input_changed = false;

void echoIsr(void) {    
  static volatile unsigned long echo_begin = 0;
  static volatile unsigned long echo_end = 0;

  unsigned int echo_pin_state = digitalRead(echo_pin);
  
  if(echo_pin_state == HIGH) {
    echo_begin = micros();
  } else {
    echo_end = micros();
    unsigned long echo_duration = echo_end - echo_begin;
    distance_input = echo_duration / 58;
    distance_input_changed = true;
  }
}

void triggering_distance_sensor() {
  static unsigned long prev_millis = 0;
  const unsigned long interval_millis = 20;

  unsigned long curr_millis = millis();
  if(curr_millis - prev_millis >= interval_millis) {
    prev_millis = curr_millis;
  
    // 비상시 거리 센서 입력 막기
    extern bool EMERGENCY_STATE_ENABLE;
    if(EMERGENCY_STATE_ENABLE) return;
  
    // triggering
    ultrasonic_sensor_triggering();
  } 
}

void ultrasonic_sensor_triggering() {
  digitalWrite(trig_pin, LOW);  
  delayMicroseconds(2); 
  digitalWrite(trig_pin, HIGH);
  delayMicroseconds(10); 
  digitalWrite(trig_pin, LOW);
}

enum {
  SOMETHING_NEAR = 30, //cm
};

bool EMERGENCY_STATE_ENABLE = false;

void check_distance_sensor_input() {
  if(distance_input_changed) {
    distance_input_changed = false;
  
//    Serial.print("distance(cm):");
//    Serial.println(distance_input);
  
    static int emergency_level = 0;
    if(distance_input <= SOMETHING_NEAR) {
      emergency_level ++;
      if(emergency_level == 7) {
        emergency_level = 0;
        
//        remote_input = STOP;
//        remote_input_changed = true;
//
//        light_onoff = ALLLIGHTON;
//        light_onoff_changed = true;        
//          
//        horn_state_changed = true;
    
        EMERGENCY_STATE_ENABLE = true;
      }
    } else {
      if(emergency_level>0) {
        emergency_level --;
//        if(emergency_level == 0) {
//          light_onoff = ALLLIGHTOFF;
//          light_onoff_changed = true;
//        }
      }
    }
    
//    Serial.print("#emergency:");
//    Serial.println(emergency_level);
  }  
}

void emergency_loop() {
  static unsigned long prev_millis = 0;
  const unsigned long interval_millis = 1;
  static int process_emergency_state = 0;
  
  if(EMERGENCY_STATE_ENABLE) {
    unsigned long curr_millis = millis();
    if(curr_millis - prev_millis >= interval_millis) {
      prev_millis = curr_millis;
  
      process_emergency_state++;
      // 비상 상태 처리
      if(process_emergency_state == 1) {
        // 1. 정지한다.
        driving_action = STOP;
        driving_action_changed = true;
        // 2. 불을 켠다.
        light_onoff = ALLLIGHTON;
        light_onoff_changed = true;
        // 3. 경적을 울린다.
        horn_state_changed = true;
      } else if(process_emergency_state == 500) {
        // 4. 후진한다.        
        driving_action = GOBACKWARD;
        driving_action_changed = true;
      } else if(process_emergency_state == 2000) {
        // 멈춘다.
        driving_action = STOP;
        driving_action_changed = true;
        // 5. 좌우를 살핀다.
        facing_left();
      } else if(process_emergency_state == 3000) {
        ultrasonic_sensor_triggering();
      } else if(process_emergency_state == 3030) {
        check_left_distance();
      } else if(process_emergency_state == 4000) {
        facing_right();
      } else if(process_emergency_state == 5000) {
        ultrasonic_sensor_triggering();
      } else if(process_emergency_state == 5030) {
        check_right_distance();
      } else if(process_emergency_state == 6000) {
        facing_front();
        // 6. 물체가 없는 쪽으로 회전한다.
        turn_left_or_right();
      } else if(process_emergency_state == 8000) {
        // 전진한다.
        driving_action = GOFORWARD;
        driving_action_changed = true;
      } else if(process_emergency_state == 9000) {
        // 멈춘다.
        driving_action = STOP;
        driving_action_changed = true;
      } else if(process_emergency_state == 10000) {
        process_emergency_state = 0;     
        // 7. 비상 상태를 해제한다.
        EMERGENCY_STATE_ENABLE = false;
        // 8. 불을 끈다.
        light_onoff = ALLLIGHTOFF;
        light_onoff_changed = true;
        // 9. 주행 명령을 기다린다.
      }
    }
  }  
}

long left_distance = 0;
long right_distance = 0;

void check_left_distance() {
  left_distance = distance_input;
  Serial.print("#left(cm):");
  Serial.println(left_distance);
}

void check_right_distance() {
  right_distance = distance_input;
  Serial.print("right(cm):");
  Serial.println(right_distance);
}

void turn_left_or_right() {
  if(left_distance >= right_distance) {
    //좌회전
    driving_action = GOFORWARDLEFT;
    driving_action_changed = true;
  } else {
    //우회전
    driving_action = GOFORWARDRIGHT;
    driving_action_changed = true;
  }
}
