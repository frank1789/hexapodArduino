#ifndef HEXAPOD_MANAGER_H
#define HEXAPOD_MANAGER_H

#include "constants.h"
#include "hexapodleg.h"

class HexapodManger {
 public:
 explicit HexapodManger();
 ~HexapodManger();


  Leg getLeg(const char* leg_position);

  // setter
  void connectLeg(int index, int pin_coxa, int pin_femur, int pin_tibia);

 private:
  typedef Leg* legptr_t;
  legptr_t legs_[kNumberLegs];
};

#endif  // HEXAPOD_MANAGER_H