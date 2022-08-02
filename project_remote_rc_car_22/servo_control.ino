#include <Servo.h>

Servo face_direction_servo; 
const int servo_pin = 9;

void servo_setup() {
  face_direction_servo.attach(servo_pin);
  facing_front();
}

void facing_front() {
  face_direction_servo.write(90);
}

void facing_left() {
  face_direction_servo.write(150);
}

void facing_right() {
  face_direction_servo.write(30);
}
