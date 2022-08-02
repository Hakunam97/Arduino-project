// 왼쪽 바퀴 - 전후진

const int DIRFL = 2; 
const int PWMFL = 3; 
const int DIRBL = 7; 
const int PWMBL = 6; 

// 오른쪽 바퀴 - 전후진

const int DIRFR =4; 
const int PWMFR =5; 
const int DIRBR =19; 
const int PWMBR =10; 

void motor_setup() {
  // 왼쪽 바퀴 초기화
  pinMode(DIRFL, OUTPUT);
  pinMode(DIRBL, OUTPUT);

  digitalWrite(DIRFL, LOW);
  analogWrite(PWMFL, 0);
  digitalWrite(DIRBL, LOW);
  analogWrite(PWMBL, 0);

  // 오른쪽 바퀴 초기화
  pinMode(DIRFR, OUTPUT);
  pinMode(DIRBR, OUTPUT);

  digitalWrite(DIRFR, LOW);
  analogWrite(PWMFR, 0);
  digitalWrite(DIRBR, LOW);
  analogWrite(PWMBR, 0); 
}

void motor_loop() {
  process_driving_action();
  process_driving_speed();
}

void process_driving_action() {
  if(driving_action_changed) {
    driving_action_changed = false;
    
    if(driving_action == GOFORWARD) {
      go_forward();
    } else if(driving_action == GOBACKWARD) {
      go_backward();
    } else if(driving_action == TURNLEFT) {
      turn_left();
    } else if(driving_action == TURNRIGHT) {
      turn_right();
    } else if(driving_action == STOP) {
      stop_driving();
    } else if(driving_action == GOFORWARDLEFT) {
      go_forward_left();
      light_blink = REARLEFTBLINK;
      light_blink_changed = true;
    } else if(driving_action == GOFORWARDRIGHT) {
      go_forward_right();
      light_blink = REARRIGHTBLINK;
      light_blink_changed = true;
    } else if(driving_action == GOBACKWARDLEFT) {
      go_backward_left();
    } else if(driving_action == GOBACKWARDRIGHT) {
      go_backward_right();
    }
  }
}

void go_forward() {
  // 전진
  // 왼쪽 전진
  digitalWrite(DIRFL, HIGH);  
  analogWrite(PWMFL, MAX_SPEED - driving_speed);
  digitalWrite(DIRBL, HIGH);  
  analogWrite(PWMBL, MAX_SPEED - driving_speed);
  // 오른쪽 전진
  digitalWrite(DIRFR, HIGH);  
  analogWrite(PWMFR, MAX_SPEED - driving_speed);
  digitalWrite(DIRBR, HIGH);  
  analogWrite(PWMBR, MAX_SPEED - driving_speed);
}

void go_backward() {
  // 후진
  // 왼쪽 후진
  digitalWrite(DIRFL, LOW);  
  analogWrite(PWMFL, MIN_SPEED + driving_speed);
  digitalWrite(DIRBL, LOW);  
  analogWrite(PWMBL, MIN_SPEED + driving_speed);
  // 오른쪽 후진
  digitalWrite(DIRFR, LOW);  
  analogWrite(PWMFR, MIN_SPEED + driving_speed);
  digitalWrite(DIRBR, LOW);  
  analogWrite(PWMBR, MIN_SPEED + driving_speed);
}

void turn_left() {
  // 좌회전
  // 왼쪽 후진
  digitalWrite(DIRFL, LOW);  
  analogWrite(PWMFL, MIN_SPEED + driving_speed);
  digitalWrite(DIRBL, LOW);  
  analogWrite(PWMBL, MIN_SPEED + driving_speed);
  // 오른쪽 전진
  digitalWrite(DIRFR, HIGH);  
  analogWrite(PWMFR, MAX_SPEED - driving_speed);
  digitalWrite(DIRBR, HIGH);  
  analogWrite(PWMBR, MAX_SPEED - driving_speed);
}

void turn_right() {
  // 우회전
  // 왼쪽 전진
  digitalWrite(DIRFL, HIGH);  
  analogWrite(PWMFL, MAX_SPEED - driving_speed);
  digitalWrite(DIRBL, HIGH);  
  analogWrite(PWMBL, MAX_SPEED - driving_speed);
  // 오른쪽 후진
  digitalWrite(DIRFR, LOW);  
  analogWrite(PWMFR, MIN_SPEED + driving_speed);
  digitalWrite(DIRBR, LOW);  
  analogWrite(PWMBR, MIN_SPEED + driving_speed);
}

void stop_driving() {
  // 정지
  // 왼쪽 정지
  digitalWrite(DIRFL, LOW); 
  analogWrite(PWMFL, MIN_SPEED );
  digitalWrite(DIRBL, LOW); 
  analogWrite(PWMBL, MIN_SPEED );
  // 오른쪽 정지
  digitalWrite(DIRFR, LOW); 
  analogWrite(PWMFR, MIN_SPEED );
  digitalWrite(DIRBR, LOW); 
  analogWrite(PWMBR, MIN_SPEED );
}

void go_forward_left() {
  turn_left();
}

void go_forward_right() {
  turn_right();
}

void go_backward_left() {
  turn_right();
}

void go_backward_right() {
  turn_left();
}

void process_driving_speed() {
  if(driving_speed_changed) {
    driving_speed_changed = false;
     
    change_driving_speed();   
  }
}

void change_driving_speed() {
  int clac_speed = driving_speed_input;
  if(clac_speed != SPEED_10) clac_speed -= SPEED_0;
  else clac_speed = 10;
  
  driving_speed = clac_speed*(MAX_SPEED/10.0);

  driving_action_changed = true;
}
