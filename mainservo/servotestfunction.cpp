#include "servotestfunction.h"

#include <Arduino.h>

#include "constants.h"

void testservo(HexapodManger *hmx) {
  static auto test_angle = 0;
  auto *servos = hmx->getServos();
  for (short i = 0; i < kPins; i++) {
    Serial.println("==> set pin: "+ String(servos[i].getPin()) + " test for angle " + String(test_angle));
    servos[i].setServoAngle(test_angle);
  }
  test_angle += 15;
  test_angle = test_angle % 180;
}
