#ifndef HEXAPODLEG_H
#define HEXAPODLEG_H

#include "servomanager.h"

class Leg {
  public:
  /**
   * @brief Construct a new Leg object
   *
   * @param pin_coxa Integer corresponding to the board pin
   * @param pin_femur Integer corresponding to the board pin
   * @param pin_tibia Integer corresponding to the board pin
   */
  explicit Leg(int pin_coxa, int pin_femur, int pin_tibia);

  /**
   * @brief Destroy the Leg object
   *
   */
  ~Leg();

 private:
  ServoManager *coxa_ = nullptr;
  ServoManager *femur_ = nullptr;
  ServoManager *tibia_ = nullptr;
};

#endif  // HEXAPODLEG_H
