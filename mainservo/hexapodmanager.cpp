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

HexapodManger::HexapodManger() {
}

HexapodManger::~HexapodManger() {
  for(int i = 0; i < kNumberLegs; i++){
    DELETE(legs_[i])
  }
}

void HexapodManger::connectLeg(int index, int pin_coxa, int pin_femur, int pin_tibia) {
  legs_[index] = new Leg(pin_coxa, pin_femur, pin_tibia);
}

Leg HexapodManger::getLeg(const char* leg_position) {
  Leg leg;
  if (leg_position == kLeftFrontLeg) {
    leg = *legs_[0];
  }
  if (leg_position == kLeftMidLeg) {
    leg = *legs_[1];
  }
  if (leg_position == kLeftBackLeg) {
    leg = *legs_[2];
  }
  if (leg_position == kRightFrontLeg) {
    leg = *legs_[3];
  }
  if (leg_position == kRightMidLeg) {
    leg = *legs_[4];
  }
  if (leg_position == kRightBackLeg) {
    leg = *legs_[5];
  }

  return leg;
}