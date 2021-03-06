#pragma once

#include <Arduino.h>
#include "utils.h"
#include "pair.h"

#ifndef SIMULATOR

#include <OneWire.h>
#include <DallasTemperature.h>
#include "i2cmux.h"
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

#endif

#define NUM_TEMP_SENSORS 3
#define NUM_BME_SENSORS 3
#define SEALEVELPRESSURE_HPA (1013.25)

namespace Sensors {
  
  /**
   * Initializes sensor simulator
   */

#ifndef SIMULATOR
  const unsigned int TMP_PINS[NUM_TEMP_SENSORS] = {22, 24, 26};
  const uint8_t BME280_ADDRESS_LIST[NUM_BME_SENSORS] = { 0x76, 0x77, 0x76};
  const I2CBUS BME280_BUS[NUM_BME_SENSORS] = { 0x00, 0x00, 0x01};

  // OneWire oneWire0(PIN_TMP0);
  // DallasTemperature tmp0(&oneWire0);
  // OneWire oneWire0;
  // DallasTemperature tmp0;

  // temperature sensors
  extern OneWire oneWireTMP[NUM_TEMP_SENSORS];
  extern DallasTemperature tmpSensors[3];


  // bme280
  extern Pair<I2CBUS, Adafruit_BME280> bmeSensors[NUM_BME_SENSORS];

#endif
  
  void init();
  
  /**
   * Performs temperature request
   * 
   * @param buffer: message from UART
   * @param buffer_size: maximum size of buffer
   */
  void waterTemperature(const char *buffer, size_t buffer_size, bool unused=false);

  size_t waterTemperature(int sensorIdx, char *buffer);
  
  /**
   * @brief Writes bme280 sensor reading to byte buffer
   * 
   * @param buffer buffer where sensor readings are written to
   * @param sensorIdx sensor index to request reading. -1 for all sensors
   * @return size_t number of bytes written to sensor
   */
  size_t bme280(char *buffer, int sensorIdx);
  
  void ph(const char *buffer, size_t buffer_size);

  void  ping(const char *buffer, size_t buffer_size);

  void echo(const char *buffer, size_t buffer_size);
}
