#ifndef SERVO_MANAGER_H
#define SERVO_MANAGER_H

#include <Wire.h>


// I2C functions
void I2C_SERVOSET(unsigned char servo_num,unsigned int servo_pos);
void I2C_SERVOREVERSE(unsigned char servo_num,unsigned char servo_dir);
void I2C_SERVOOFFSET(unsigned char servo_num,int value);
void I2C_SERVOSPEED(unsigned char value);
void I2C_SERVONUTRALSET(unsigned char servo_num,unsigned int servo_pos);
void I2C_SERVOMIN(unsigned char servo_num,unsigned int servo_pos);
void I2C_SERVOMAX(unsigned char servo_num,unsigned int servo_pos);
char I2C_SERVOEND(void);
int I2C_SERVOGET(int servo_num);
int I2C_SERVOGETOFFSET(int servo_num);


class ServoManager {
 public:
  ServoManager() {};
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
  unsigned char pin_;
};

#endif  // SERVO_MANAGER_H
