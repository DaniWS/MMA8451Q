#ifndef MMA8451Q_H
#define MMA8451Q_H

#include "mbed.h"

//!Library for the MMA8451Q motion sensor.
class MMA8451Q
{
public:
  //!Creates an instance of the class.
  /*
  * Connect module at I2C address addr using I2C port pins sda and scl.
  * MMA8451Q
  * \param sda SDA pin
  * \param sdl SCL pin
  * \param addr addr of the I2C peripheral
  */
  MMA8451Q(PinName sda, PinName scl, int addr);

  /*
  * Destroys instance.
  */
  ~MMA8451Q();

  /*
   * Get the value of the WHO_AM_I register
   *
   * \returns WHO_AM_I value
   */
  uint8_t getWhoAmI();

  /*
   * Get X axis acceleration
   *
   * \returns X axis acceleration
   */
  int16_t getAccX();

  /*
   * Get Y axis acceleration
   *
   * \returns Y axis acceleration
   */
  int16_t getAccY();

  /*
   * Get Z axis acceleration
   *
   * \returns Z axis acceleration
   */
  int16_t getAccZ();

  /*
   * Get XYZ axis acceleration
   *
   * \param res array where acceleration data will be stored
   */
  void    getAccAllAxis(int16_t * res);

  I2C m_i2c;

private:
  int m_addr;
  void read_regs(int addr, uint8_t * data, int len);
  void write_regs(uint8_t * data, int len);
  int16_t getAccAxis(uint8_t addr);

};

#endif
