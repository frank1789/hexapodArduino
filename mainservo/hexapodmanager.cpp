#include "hexapodmanager.h"

#include <Arduino.h>

#include "constants.h"

#define DELETE(ptr)  \
  if (ptr != NULL) { \
    delete ptr;      \
    ptr = NULL;      \
  }

#define DELETE_TABLE(ptr) \
  if (ptr != NULL) {      \
    delete[] ptr;         \
    ptr = NULL;           \
  }

HexapodManger::HexapodManger() {
  // assemble pins and legs to correctly initialize the robot
  Serial.print("initialize legs connected to pin\n");
  for (int i = 0; i < kPins; i++) {
    auto pin_index = i + 1;
    servos_[i] = ServoManager((unsigned char)pin_index);
  }

  /*
   * here create ROS node
   * <-----> ALREADY NOT IMPLEMENTED <----->
   *
   */
}

HexapodManger::~HexapodManger() {}

void HexapodManger::getServos(ServoManager p[]) { p = servos_; }