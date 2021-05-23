#ifndef __SERVO_MANAGER_H__
#define __SERVO_MANAGER_H__

class ServoManager {
 public:
  ServoManager();
  /**
   * @brief Construct a new Servo Manager object
   *
   * @param pin Integer corresponding to the board pin
   */
  explicit ServoManager(unsigned char pin);

  /**
   * @brief Set the Servo Angle object
   *
   * @param angle expressed in deg
   */
  void setServoAngle(unsigned int angle);

  /**
   * @brief Get the Pin object
   *
   * @return unsigned char
   */
  inline unsigned char getPin() const { return pin_; }

  /**
   * @brief Get the Angle object expressed in degree
   *
   * @return unsigned int
   */
  inline unsigned int getAngle() const { return angle_; }

  /**
   * @brief Get the Mapped Angle object expresse in value between 500(min) and
   * 2500(Max)
   *
   * @return unsigned int
   */
  inline unsigned int getMappedAngle() const { return mapped_angle_; }

 protected:
  /**
   * @brief Reset the servo at default position
   *
   */
  void resetServo();

 private:
  unsigned char pin_{};
  unsigned int angle_{};
  unsigned int mapped_angle_{};
};

#endif  // __SERVO_MANAGER_H__
