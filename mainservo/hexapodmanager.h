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
  explicit HexapodManger();
  static HexapodManger* pinstance_;
  typedef Leg* legptr_t;
  legptr_t *legs_{nullptr};
};

#endif  // HEXAPOD_MANAGER_H