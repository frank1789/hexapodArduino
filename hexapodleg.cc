#include "hexapodleg.h"

Leg::Leg(int pin_coxa, int pin_femur, int pin_tibia) {
  coxa_ = new ServoManager(pin_coxa);
  femur_ = new ServoManager(pin_femur);
  tibia_ = new ServoManager(pin_tibia);
}

Leg::~Leg() {
  if (coxa_) {
    delete coxa_;
  }
  if (femur_) {
    delete femur_;
  }
  if (tibia_) {
    delete tibia_;
  }
}