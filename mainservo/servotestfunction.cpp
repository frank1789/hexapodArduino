#include "servotestfunction.h"

#include <Arduino.h>

void testservo(const Leg& leg) {
  auto str = String("testLeg, for angles 75, 90, 120");
  Serial.println(str);
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
