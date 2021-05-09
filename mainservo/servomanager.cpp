#include "servomanager.h"

#include <Arduino.h>

#define servo1	(16>>1)
#define servo2	(18>>1)
#define UART_BAUD_RATE	115200
#define SERIAL_BUFFER_SIZE 256

// use map function to remap the values 0-180 degree into 500-2500 servos'value
// map(servo_pos, 0, 180, 500, 2500);

void I2C_SERVOSET(unsigned char servo_num,unsigned int servo_pos)
{
	if(servo_pos<500)
		servo_pos = 500;
	else if(servo_pos>2500)
		servo_pos=2500;

	if(servo_pos>501)
		servo_pos=(((servo_pos-2)*2)-1000);
	else
		servo_pos=0;

	if(servo_num<19)
		Wire.beginTransmission(servo1);
	else
		Wire.beginTransmission(servo2);
	Wire.write(servo_num-1);
	Wire.write(servo_pos>>8);
	Wire.write(servo_pos & 0XFF);
	Wire.endTransmission();
}

void I2C_SERVOMIN(unsigned char servo_num,unsigned int servo_pos)
{
	if(servo_pos<500)
		servo_pos = 500;
	else if(servo_pos>2500)
		servo_pos=2500;
	servo_pos=((servo_pos*2)-1000);

	if(servo_num<19)
		Wire.beginTransmission(servo1);
	else
		Wire.beginTransmission(servo2);
	Wire.write((servo_num-1)+(18*4));
	Wire.write(servo_pos>>8);
	Wire.write(servo_pos & 0XFF);
	Wire.endTransmission();
	// delay(20);
}

void I2C_SERVOMAX(unsigned char servo_num,unsigned int servo_pos)
{
	if(servo_pos<500)
		servo_pos = 500;
	else if(servo_pos>2500)
		servo_pos=2500;
	servo_pos=((servo_pos*2)-1000);

	if(servo_num<19)
		Wire.beginTransmission(servo1);
	else
		Wire.beginTransmission(servo2);
	Wire.write((servo_num-1)+(18*3));
	Wire.write(servo_pos>>8);
	Wire.write(servo_pos & 0XFF);
	Wire.endTransmission();
	// delay(20);
}

void I2C_SERVONUTRALSET(unsigned char servo_num,unsigned int servo_pos)
{
	if(servo_pos<500)
		servo_pos = 500;
	else if(servo_pos>2500)
		servo_pos=2500;
	servo_pos=((servo_pos*2)-1000);

	if(servo_num<19)
		Wire.beginTransmission(servo1);
	else
		Wire.beginTransmission(servo2);
	Wire.write((servo_num-1)+(18*5));
	Wire.write(servo_pos>>8);
	Wire.write(servo_pos & 0XFF);
	Wire.endTransmission();
}

void I2C_SERVOSPEED(unsigned char value)
{
	Wire.beginTransmission(servo1);
	Wire.write(18*2);
	Wire.write(value);
	Wire.write(0);
	Wire.endTransmission();
	Wire.beginTransmission(servo2);
	Wire.write(18*2);
	Wire.write(value);
	Wire.write(0);
	Wire.endTransmission();
	// delay(20);
}

void I2C_SERVOOFFSET(unsigned char servo_num,int value)
{
	value=3000-value;
	value=value-1500;

	if (value<-500)
		value=-500;
	else if (value>500)
		value=500;

	if(value>0)
		value=2000+(value*2);
	else if(value<=0)
		value=-value*2;

	
	if(servo_num<19)
		Wire.beginTransmission(servo1);
	else
		Wire.beginTransmission(servo2);
	Wire.write((servo_num-1)+(18*6));
	Wire.write(value>>8);
	Wire.write(value & 0XFF);
	Wire.endTransmission();
  // delay(20);
}

void I2C_SERVOREVERSE(unsigned char servo_num,unsigned char servo_dir)
{
	if(servo_dir>0)
		servo_dir=1;
	if(servo_num<19)
		Wire.beginTransmission(servo1);
	else
		Wire.beginTransmission(servo2);
	Wire.write((servo_num-1)+(18*7));
	Wire.write(servo_dir);
	Wire.write(0);
	Wire.endTransmission();
  // delay(20);
}

char I2C_SERVOEND(void)
{
	int i, n;
	char buffer;
	Wire.beginTransmission(servo1);
	n = Wire.write(181);
	if (n != 1)
		return (-10);

	n = Wire.endTransmission(false);
	if (n != 0)
		return (n);

	// delayMicroseconds(350);
	Wire.requestFrom(servo1, 1, true);
	while(Wire.available())
		buffer=Wire.read();

	return(buffer);
}

int I2C_SERVOGET(int servo_num)
{
	int i, n, error;
	uint8_t buffer[2];
	Wire.beginTransmission(servo1);

	n = Wire.write((servo_num-1)+(18*8));
	if (n != 1)
		return (-10);

	n = Wire.endTransmission(false);
	if (n != 0)
		return (n);

	// delayMicroseconds(240);
	Wire.requestFrom(servo1, 2, true);
	i = 0;
	while(Wire.available() && i<2)
	{
		buffer[i++]=Wire.read();
	}
	if ( i != 2)
		return (-11);
	return (((buffer[0]*256 + buffer[1])+4)/2 +500);
}

int I2C_SERVOGETOFFSET(int servo_num)
{
	int i, n, error;
	uint8_t buffer[2];
	Wire.beginTransmission(servo1);

	n = Wire.write((servo_num-1)+(182));
	if (n != 1)
		return (-10);

	n = Wire.endTransmission(false);
	if (n != 0)
		return (n);

	// delayMicroseconds(240);
	Wire.requestFrom(servo1, 2, true);
	i = 0;
	while(Wire.available() && i<2)
	{
		buffer[i++]=Wire.read();
	}
	if ( i != 2)
		return (-11);
	i=((buffer[0]*256 + buffer[1]));
	if(i>2000)
		return(3000-(((i-2000)/2)+1500));
	else
		return(3000-((-i/2)+1500));
}







///////////////////////////////////////////////////////////////////////////////

ServoManager::ServoManager() { }

ServoManager::ServoManager(int pin) {
  pin_ = (unsigned char)pin;
  resetServo();
}

void ServoManager::setServoAngle(int angle) {
  if (angle >= 180) {
    angle = 179;
    I2C_SERVOSET(pin_, angle);
  } else if (angle <= 0) {
    angle = 0;
    I2C_SERVOSET(pin_, angle);
  } else {
    I2C_SERVOSET(pin_, angle);
  }
	Serial.println("write on motor");
  Serial.println(angle);
}

void ServoManager::resetServo() { I2C_SERVOSET(pin_, 90); }
  
