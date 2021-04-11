#include "hexapodmanager.h"

#include <Arduino.h>

#define DELETE( ptr ) \
if (ptr != NULL)      \
{                     \
    delete ptr;       \
    ptr = NULL;       \
}

#define DELETE_TABLE( ptr ) \
if (ptr != NULL)            \
{                           \
    delete[] ptr;           \
    ptr = NULL;             \
}

HexapodManger* HexapodManger::pinstance_{nullptr};

HexapodManger* HexapodManger::getInstance() {
  if (pinstance_ != nullptr) {
    pinstance_ = new HexapodManger;
  }
  return pinstance_;
}

HexapodManger::HexapodManger() {
  legs_ = new legptr_t[kNumberLegs];
}

HexapodManger::~HexapodManger() {
  DELETE(pinstance_)
  for(int i = 0; i < kNumberLegs; i++){
    DELETE(legs_[i])
  }
  DELETE_TABLE(legs_)
}

void HexapodManger::connectLeg(int index, int pin_coxa, int pin_femur,
                               int pin_tibia) {
  legs_[index] = new Leg(pin_coxa, pin_femur, pin_tibia);
}

Leg HexapodManger::getLeg(const char* leg_position) {
  Leg leg;
  if (leg_position == kLeftFrontLeg) {
    leg = *getInstance()->legs_[0];
  }
  if (leg_position == kLeftMidLeg) {
    leg = *getInstance()->legs_[1];
  }
  if (leg_position == kLeftBackLeg) {
    leg = *getInstance()->legs_[2];
  }
  if (leg_position == kRightFrontLeg) {
    leg = *getInstance()->legs_[3];
  }
  if (leg_position == kRightMidLeg) {
    leg = *getInstance()->legs_[4];
  }
  if (leg_position == kRightBackLeg) {
    leg = *getInstance()->legs_[5];
  }

  return leg;
}