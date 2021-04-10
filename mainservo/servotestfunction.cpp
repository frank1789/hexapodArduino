#include "servotestfunction.h"

#include <Arduino.h>

void testservo(Leg& legs) {
  for (int i = 0; i < 6; i++) {
    legs["coxa"]->setServoAngle(75);
    delay(500);
    legs["coxa"]->setServoAngle(90);
    delay(500);
    legs["femur"]->setServoAngle(120);
    delay(500);
    legs["femur"]->setServoAngle(90);
    delay(500);
    legs["tibia"]->setServoAngle(120);
    delay(500);
    legs["tibia"]->setServoAngle(90);
  }
}
