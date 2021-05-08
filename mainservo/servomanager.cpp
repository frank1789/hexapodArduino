#include "servomanager.h"

#include <Arduino.h>

ServoManager::ServoManager(int pin) {
  servo_.attach(pin);
  resetServo();
}

void ServoManager::setServoAngle(int angle) {
  if (angle >= 180) {
    angle = 179;
    servo_.write(angle);
  } else if (angle <= 0) {
    angle = 0;
    servo_.write(angle);
  } else {
    servo_.write(angle);
  }
	Serial.println("write on motor");
  Serial.println(angle);
}

void ServoManager::resetServo() { servo_.write(120); }
  
