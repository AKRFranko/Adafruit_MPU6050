/*!
 *  @file Adafruit_MPU6050.h
 *
 * 	I2C Driver for MPU6050 6-Axis Accelerometer and Magnetometer 
 *
 * 	This is a library for the Adafruit MPU6050 breakout:
 * 	https://www.adafruit.com/products/3886
 * 
 * 	Adafruit invests time and resources providing this open source code,
 *  please support Adafruit and open-source hardware by purchasing products from
 * 	Adafruit!
 *
 *
 *	BSD license (see license.txt)
 */

#ifndef _ADAFRUIT_MPU6050_H
#define _ADAFRUIT_MPU6050_H

#include "Arduino.h"
#include <Wire.h>
#include <Adafruit_I2CDevice.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BusIO_Register.h>

// TODO: Trust but verify
#define MPU6050_I2CADDR_DEFAULT 0x69 ///< MPU6050 default i2c address

// All addresses are for 16bit registers; 
// duplicates are for high or low bytes that aren't used together
#define MPU6050_SMPLRT_DIV   0x19
#define MPU6050_CONFIG       0x1a
#define MPU6050_GYRO_CONFIG  0x1b
#define MPU6050_ACCEL_CONFIG 0x1c
#define MPU6050_WHO_AM_I     0x75
#define MPU6050_PWR_MGMT_1   0x6b
#define MPU6050_TEMP_H       0x41
#define MPU6050_TEMP_L       0x42
#define MPU6050_ACCEL_OUT    0x3B // base address for all data reads. Start here and read 14 bytes to get accel, gyro, and


/**
 * @brief Proximity LED current values
 *
 * Allowed values for `setProximityLEDCurrent`.
 */
// typedef enum led_current {
//   MPU6050_LED_CURRENT_50MA,

// } MPU6050_LEDCurrent;

/** The accelerometer ranges */
typedef enum {
  MPU6050_RANGE_2_G = 0b00,  ///< +/- 2g (default value)
  MPU6050_RANGE_4_G = 0b01,  ///< +/- 4g
  MPU6050_RANGE_8_G = 0b10,  ///< +/- 8g
  MPU6050_RANGE_16_G = 0b11, ///< +/- 16g
} mpu6050_range_t;

/*!
 *    @brief  Class that stores state and functions for interacting with
 *            the MPU6050 I2C Digital Potentiometer
 */
class Adafruit_MPU6050 : public Adafruit_Sensor {

public:
  Adafruit_MPU6050();
  boolean begin(uint8_t i2c_addr=MPU6050_I2CADDR_DEFAULT, TwoWire *wire = &Wire, int32_t sensorID = 0);
  
  mpu6050_range_t getAccelerometerRange(void);
  void setAccelerometerRange(mpu6050_range_t);


  // Adafruit_Sensor API/Interface
  void read(void);
  bool getEvent(sensors_event_t *event);
  void getSensor(sensor_t *sensor);
  // void getAccelEvent(sensors_event_t* event, uint32_t timestamp);
  // void getGyroEvent(sensors_event_t* event, uint32_t timestamp);


private:
  bool _init(int32_t);

  Adafruit_I2CDevice *i2c_dev;
  float temp, accX, accY, accZ, gyroX, gyroY, gyroZ;
  int16_t rawAccX, rawAccY, rawAccZ, rawTemp,
  rawGyroX, rawGyroY, rawGyroZ;
  uint8_t _sensorID;
};

#endif

