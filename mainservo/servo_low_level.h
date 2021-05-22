#ifndef __I2C_LOWLEVEL_SERVO_H__
#define __I2C_LOWLEVEL_SERVO_H__

void I2C_SERVOSET(unsigned char servo_num, unsigned int servo_pos);

void I2C_SERVOREVERSE(unsigned char servo_num, unsigned char servo_dir);

void I2C_SERVOOFFSET(unsigned char servo_num, int value);

void I2C_SERVOSPEED(unsigned char value);

void I2C_SERVONUTRALSET(unsigned char servo_num, unsigned int servo_pos);

void I2C_SERVOMIN(unsigned char servo_num, unsigned int servo_pos);

void I2C_SERVOMAX(unsigned char servo_num, unsigned int servo_pos);

char I2C_SERVOEND(void);

int I2C_SERVOGET(int servo_num);

int I2C_SERVOGETOFFSET(int servo_num);

void CheckEndMovement(void);

void LEDToggle(void);

void LowLevelControllerServo(unsigned char servo_num, unsigned int servo_position);

#endif  // __I2C_LOWLEVEL_SERVO_H__
