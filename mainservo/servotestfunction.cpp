#include "servotestfunction.h"

#include <Arduino.h>

void testservo(const Leg& leg) {
  leg.getComponentLeg("coxa").setServoAngle(75);
  delay(500);
  leg.getComponentLeg("coxa").setServoAngle(90);
  delay(500);
  leg.getComponentLeg("femur").setServoAngle(120);
  delay(500);
  leg.getComponentLeg("femur").setServoAngle(90);
  delay(500);
  leg.getComponentLeg("tibia").setServoAngle(120);
  delay(500);
  leg.getComponentLeg("tibia").setServoAngle(90);
}
