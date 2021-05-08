#ifndef HEXAPODLEG_H
#define HEXAPODLEG_H

#include "constants.h"
#include "servomanager.h"

#include <Arduino.h>


class Leg {
 public:
  explicit Leg() = default;
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

  inline ServoManager operator[](const char *component) const {
    ServoManager c;
    if (component == kComponentLegCoxa) {
      c =  *tibia_;
    }
    if (component == kComponentLegFemur) {
      c = *femur_;
    }
    if (component == kComponentLegTibia) {
      c = *tibia_;
    }
    Serial.println("access by name");
    Serial.println(component);
    return c;
  }

 private:
  ServoManager *coxa_ = nullptr;
  ServoManager *femur_ = nullptr;
  ServoManager *tibia_ = nullptr;
};

#endif  // HEXAPODLEG_H
