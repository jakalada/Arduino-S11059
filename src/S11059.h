/**********************************************************************
  Sensor Datasheet:
    - EN: http://www.hamamatsu.com/resources/pdf/ssd/s11059-02dt_etc_kpic1082e.pdf
          (Cat. No. KPIC1082E05 Nov. 2015 DN)
    - JP: http://www.hamamatsu.com/resources/pdf/ssd/s11059-02dt_etc_kpic1082j.pdf
          (Cat. No. KPIC1082J05 Nov. 2015 DN)
**********************************************************************/

#ifndef S11059_h
#define S11059_h

#include "Arduino.h"
#include <Wire.h>

#define S11059_GAIN_HIGH      1
#define S11059_GAIN_LOW       0

#define S11059_MODE_MANUAL    1
#define S11059_MODE_FIXED     0

#define S11059_TINT0    0
#define S11059_TINT1    1
#define S11059_TINT2    2
#define S11059_TINT3    3

#define S11059_MANUAL_TIMING_MAX   65535
#define S11059_MANUAL_TIMING_MIN   0

class S11059 {
  private:
    TwoWire *_wire;
    uint16_t _rgbir[4];
    uint8_t _gain;
    uint8_t _mode;
    uint8_t _tint;
    uint16_t _manualTiming;

    uint8_t getControlBits();
    bool write(uint8_t value);
    bool write(uint8_t *values, size_t size);
    bool read(uint8_t *values, int size);
    bool readRegister(uint8_t address, uint8_t *value);
    bool readRegisters(uint8_t address, uint8_t *values, uint8_t size);
    bool writeRegister(uint8_t address, uint8_t value);
    bool writeRegisters(uint8_t address, uint8_t *values, uint8_t size);

  public:
    S11059(TwoWire *wire=&Wire);
    void setGain(uint8_t gain);
    void setMode(uint8_t mode);
    void setTint(uint8_t tint);
    void setManualTiming(uint16_t manualTiming);
    void delay();
    bool reset();
    bool standby();
    bool start();
    bool update();
    bool isStandby();
    uint16_t getRed();
    uint16_t getGreen();
    uint16_t getBlue();
    uint16_t getIR();
};

#endif
