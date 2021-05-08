#include "servotestfunction.h"

#include <Arduino.h>

void testservo(Leg& leg) {
    leg["coxa"]->setServoAngle(75);
    delay(500);
    leg["coxa"]->setServoAngle(90);
    delay(500);
    leg["femur"]->setServoAngle(120);
    delay(500);
    leg["femur"]->setServoAngle(90);
    delay(500);
    leg["tibia"]->setServoAngle(120);
    delay(500);
    leg["tibia"]->setServoAngle(90);
}
