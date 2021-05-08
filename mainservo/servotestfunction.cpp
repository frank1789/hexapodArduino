#include "servotestfunction.h"

#include <Arduino.h>

void testservo(const Leg& leg) {
  leg["coxa"].setServoAngle(75);
  delay(250);
  leg["coxa"].setServoAngle(90);
  delay(250);
  leg["femur"].setServoAngle(120);
  delay(250);
  leg["femur"].setServoAngle(90);
  delay(250);
  leg["tibia"].setServoAngle(120);
  delay(250);
  leg["tibia"].setServoAngle(90);
}
