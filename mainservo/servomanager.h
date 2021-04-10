#ifndef SERVO_MANAGER_H
#define SERVO_MANAGER_H

#include <Servo.h>

class ServoManager {
 public:
  /**
   * @brief Construct a new Servo Manager object
   *
   * @param pin Integer corresponding to the board pin
   */
  explicit ServoManager(int pin);

  /**
   * @brief Set the Servo Angle object
   *
   * @param angle expressed in deg
   */
  void setServoAngle(int angle);

 protected:
  /**
   * @brief Reset the servo at default position
   *
   */
  void resetServo();

 private:
  Servo servo_;
};

#endif  // SERVO_MANAGER_H
