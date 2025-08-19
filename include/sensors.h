#ifndef SENSORS_H
#define SENSORS_H

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_ADS1X15.h>
#include <RTClib.h>
#include <MPU9250_WE.h>
#include <Adafruit_HMC5883_U.h>

// Direcciones I2C conocidas
#define ADDR_HMC5883 0x0D
#define ADDR_OLED 0x3C
#define ADDR_ADS1115 0x48
#define ADDR_EEPROM 0x57
#define ADDR_RTC 0x68
#define ADDR_MPU 0x69
#define ADDR_BME280 0x76

// Pantalla
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

// Objetos globales de sensores
extern Adafruit_SSD1306 display;
extern Adafruit_BME280 bme;
extern Adafruit_ADS1115 ads;
extern RTC_DS3231 rtc;
extern MPU9250_WE mpu;
extern Adafruit_HMC5883_Unified mag;

bool scanI2CDevices();
bool initSensors();
bool checkRTC();

#endif
