#include "servomanager.h"

#include <Arduino.h>

#include "servo_low_level.h"

#define MAX_POSITION_SERVO 180
#define MIN_POSITION_SERVO 0

ServoManager::ServoManager() {}

ServoManager::ServoManager(unsigned char pin) {
  pin_ = pin;
  resetServo();
}

void ServoManager::setServoAngle(unsigned int angle) {
  // use map function to remap the values 0-180 degree into 500-2500
  // servos'value map(servo_pos, 0, 180, 500, 2500);
  angle_ = angle;
  mapped_angle_ = map(angle, MIN_POSITION_SERVO, MAX_POSITION_SERVO,
                      MIN_SERVO_POSITION, MAX_SERVO_POSITION);
}

void ServoManager::resetServo() { 
  const auto mid_positon = MAX_SERVO_POSITION / 2;
  setServoAngle(mid_positon); 
}
