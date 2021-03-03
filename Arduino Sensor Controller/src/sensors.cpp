#ifndef SIMULATOR

#include "sensors.h"
#include <Arduino.h>
#include "utils.h"
#include <stdlib.h>

#if defined(DTOSTRF_EXT_LIB) || defined(DUE)
char *dtostrf (double val, signed char width, unsigned char prec, char *sout) {
  char fmt[20];
  sprintf(fmt, "%%%d.%df", width, prec);
  sprintf(sout, fmt, val);
  return sout;
}

#endif

namespace Sensors {
    OneWire oneWireTMP[3];
    DallasTemperature tmpSensors[3];
}

void Sensors::init() {
    randomSeed(analogRead(0));

    // initialize temperature sensors
    for (int i = 0; i < NUM_TEMP_SENSORS; ++i) {
        oneWireTMP[i] = OneWire(TMP_PINS[i]);
        tmpSensors[i] = DallasTemperature(&oneWireTMP[i]);
        tmpSensors[i].begin();
    }
}

void Sensors::waterTemperature(const char *buffer, size_t buffer_size, bool unused) {
    // char next[8];
    // Utils::nextWord(buffer, 5, 8, next, 8);

    tmpSensors[0].requestTemperatures();
    float temp = tmpSensors[0].getTempFByIndex(0);
    char send[64];
    char str_tmp[16];
    dtostrf(temp, 4, 2, str_tmp);
    sprintf(send, "TEMP %s", str_tmp);

    Utils::sendSerial(send);
}

size_t Sensors::waterTemperature(int sensorIdx, char *buffer) {
    // bytes written to buffer during this function call
    size_t totalWritten = 0;
    
    // Writes values of all available temperature sensors to the buffer
    if (sensorIdx == -1) {
        size_t written = waterTemperature(0, buffer);
        buffer = Utils::movePointer(buffer, written);
        totalWritten += written;

        written = waterTemperature(1, buffer);
        buffer = Utils::movePointer(buffer, written);
        totalWritten += written;

        written = waterTemperature(2, buffer);
        totalWritten += written;
    }
    // Writes value of particular sensor index to the buffer
    else if (sensorIdx >= 0 && sensorIdx < 3) {
        DallasTemperature *temp = tmpSensors + sensorIdx;

        temp->requestTemperatures();
        float reading = temp->getTempFByIndex(0);
        sprintf(buffer, "TMP:%d %.2f", sensorIdx, reading);
        totalWritten = strlen(buffer) + 1;
    }
    
    return totalWritten;
}

// this is still simulated
void Sensors::ph(const char *buffer, size_t buffer_size) {
    float rand = random(0,1401) * 0.01;
    char send[16];
    char cstring_rand[6];
    dtostrf(rand, 4, 2, cstring_rand);
    sprintf(send, "PHVAL %s", cstring_rand);
    Utils::sendSerial(send);
}

void Sensors::ping(const char *buffer, size_t buffer_size) {
    Utils::sendSerial("PONG");
}

void Sensors::echo(const char *buffer, size_t buffer_size) {
    if (buffer[4] == 0) Utils::sendSerial(0);
    const char *send = buffer + 5;
    // Utils::sendSerial(send);
    Serial.println(send);
}


#endif