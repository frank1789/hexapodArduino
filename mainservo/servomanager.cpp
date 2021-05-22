#include "servomanager.h"

#include <Arduino.h>

#include "servo_low_level.h"


// use map function to remap the values 0-180 degree into 500-2500 servos'value
// map(servo_pos, 0, 180, 500, 2500);



ServoManager::ServoManager() { }

ServoManager::ServoManager(int pin) {
  pin_ = pin;
  resetServo();
}

void ServoManager::setServoAngle(int angle) {
  LowLevelControllerServo((unsigned char)pin_, (unsigned int)angle); 
	Serial.println("write on motor");
  Serial.println(angle);
}

void ServoManager::resetServo() { setServoAngle(90); }
  
