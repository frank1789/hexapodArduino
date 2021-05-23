#include "servotestfunction.h"

#include <Arduino.h>

#include "constants.h"

void testservo(HexapodManger *hmx) {
  static auto test_angle = 0;
  Serial.println("test for angle "+String(test_angle));
  static ServoManager servos[kPins]{};
  hmx->getServos(servos);
  for(short i = 0; i < kPins; i++)
  {
    servos[i].setServoAngle(test_angle);
  }
  test_angle += 15;
  test_angle = test_angle % 180;
}
