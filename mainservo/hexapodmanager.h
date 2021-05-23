#ifndef __HEXAPOD_MANAGER_H__
#define __HEXAPOD_MANAGER_H__

#include "hexapodleg.h"

class HexapodManger {
 public:
  /**
   * @brief Construct a new Hexapod Manger object
   *
   */
  explicit HexapodManger();

  /**
   * @brief Destroy the Hexapod Manger object
   *
   */
  ~HexapodManger();

  /**
   * @brief ConnectLeg builds each leg separately and assigns correct pins to
   * servo motors
   *
   * @param[in] index integer
   * @param[in] pin_coxa integer represents the pin
   * @param[in] pin_femur integer represents the pin
   * @param[in] pin_tibia integer represents the pin
   */
  void connectLeg(int index, int pin_coxa, int pin_femur, int pin_tibia);

  /**
   * @brief Get the Leg object
   *
   * @param[in] leg_position string leg name's joint
   * @return Leg
   */
  Leg getLeg(const char* leg_position);

  void getServos(ServoManager p[]);

 private:
  typedef Leg* legptr_t;
  legptr_t legs_[kNumberLegs]{};
};

#endif  // __HEXAPOD_MANAGER_H__