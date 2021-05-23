#include "hexapodleg.h"

#include <Arduino.h>

Leg::Leg(int pin_coxa, int pin_femur, int pin_tibia) {
  coxa_ = new ServoManager(pin_coxa);
  femur_ = new ServoManager(pin_femur);
  tibia_ = new ServoManager(pin_tibia);
}

Leg::~Leg() {
  if (coxa_) {
    delete coxa_;
    coxa_ = nullptr;
  }
  if (femur_) {
    delete femur_;
    femur_ = nullptr;
  }
  if (tibia_) {
    delete tibia_;
    tibia_ = nullptr;
  }
}

ServoManager Leg::getComponentLeg(const char *component) const {
  ServoManager c;
  if (component == kComponentLegCoxa) {
    c = *tibia_;
  }
  if (component == kComponentLegFemur) {
    c = *femur_;
  }
  if (component == kComponentLegTibia) {
    c = *tibia_;
  }
  auto str = String("access by name: ") + component;
  Serial.println(str);
  return c;
}