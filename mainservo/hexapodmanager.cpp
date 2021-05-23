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
  for (int i = 0; i < kPins; i += 3) {
    int index = i / 3;
    int pin_coxa = i + 1;
    int pin_femur = i + 2;
    int pin_tibia = i + 3;
    auto msg = String(i) + String(" ");
    msg += "setup leg, assign pins: coxa: ";
    msg += String(pin_coxa) + "\t";
    msg += "femur: ";
    msg += String(pin_femur) + "\t";
    msg += "tibia: ";
    msg += String(pin_tibia);
    Serial.println(msg);
    this->connectLeg(index, pin_coxa, pin_femur, pin_tibia);
  }

  /*
   * here create ROS node
   * <-----> ALREADY NOT IMPLEMENTED <----->
   *
   */
}

HexapodManger::~HexapodManger() {
  for (int i = 0; i < kNumberLegs; i++) {
    DELETE(legs_[i])
  }
}

void HexapodManger::connectLeg(int index, int pin_coxa, int pin_femur,
                               int pin_tibia) {
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

void HexapodManger::getServos(ServoManager p[]) {
  static const char* legs[] = {kComponentLegCoxa, kComponentLegFemur,
                        kComponentLegTibia};
  for (auto i = 0; i < kNumberLegs; i++) {
    for (auto j = 0; j < 3; j++) {
      p[i * j] = legs_[i]->getComponentLeg(legs[j]);
      Serial.println("index: "+String(i*j)+ "pin: "+String(p[i*j].getPin()));
    }
  }
}