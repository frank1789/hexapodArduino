#ifndef HEXAPODLEG_H
#define HEXAPODLEG_H

#include "servomanager.h"

constexpr char kComponentLegCoxa[] = "coxa";
constexpr char kComponentLegFemur[] = "femur";
constexpr char kComponentLegTibia[] = "tibia";

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

  ServoManager *operator[](const char *component) {
    if (component == kComponentLegCoxa) {
      return tibia_;
    }
    if (component == kComponentLegFemur) {
      return femur_;
    }
    if (component == kComponentLegTibia) {
      return tibia_;
    }
    return nullptr;
  }

 private:
  ServoManager *coxa_ = nullptr;
  ServoManager *femur_ = nullptr;
  ServoManager *tibia_ = nullptr;
};

#endif  // HEXAPODLEG_H
