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


  void getServos(ServoManager p[]);

 private:
  ServoManager servos_[kPins];
};

#endif  // __HEXAPOD_MANAGER_H__