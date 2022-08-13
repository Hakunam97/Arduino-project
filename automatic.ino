void automatic_driving_loop() {
  process_automatic_driving();
}

void process_automatic_driving() {
  static unsigned long prev_millis = 0;
  const unsigned long interval_millis = 100;

  // 비상시 자동 입력 막기
  extern bool EMERGENCY_STATE_ENABLE;
  if(EMERGENCY_STATE_ENABLE) return; 
  
  if(AUTOMATIC_DRIVING_ENABLE) {
    unsigned long curr_millis = millis();
    if(curr_millis - prev_millis >= interval_millis) {
      prev_millis = curr_millis;

      driving_action = GOFORWARD;
      driving_action_changed = true; 
    }
  }  
}
