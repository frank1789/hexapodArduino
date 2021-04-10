#ifndef HEXAPOD_MANAGER_H
#define HEXAPOD_MANAGER_H

#include "constants.h"
#include "hexapodleg.h"

class HexapodManger {
 public:
  static HexapodManger* getInstance();
  ~HexapodManger();
  HexapodManger(HexapodManger&) = delete;
  void operator=(const HexapodManger&) = delete;

  Leg getLeg(const char* leg_position);

  // setter
  void connectLeg(int index, int pin_coxa, int pin_femur, int pin_tibia);

 private:
  explicit HexapodManger() = default;
  static HexapodManger* pinstance_;
  Leg* legs_[kNumberLegs]{nullptr};
};

#endif  // HEXAPOD_MANAGER_H