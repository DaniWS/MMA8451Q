#include "MMA8451Q.h"

#define REG_WHO_AM_I       0x0D
#define REG_CTRL_REG_1     0x2A
#define REG_OUT_X_MSB     0x01
#define REG_OUT_Y_MSB     0x03
#define REG_OUT_Z_MSB     0x05

#define UINT14_MAX 16383

MMA8451Q::MMA8451Q(PinName sda, PinName scl, int addr) : m_i2c(sda, scl), m_addr(addr) {
    // activate the peripheral
    uint8_t data[2] = {REG_CTRL_REG_1, 0x01};
    write_regs(data, 2);
}

MMA8451Q::~MMA8451Q() { }

uint8_t MMA8451Q::getWhoAmI() {
    uint8_t who_am_i = 0;
    read_regs(REG_WHO_AM_I, &who_am_i, 1);
    return who_am_i;
}

int16_t MMA8451Q::getAccX() {
    return getAccAxis(REG_OUT_X_MSB);
}

int16_t MMA8451Q::getAccY() {
    return getAccAxis(REG_OUT_Y_MSB);
}

int16_t MMA8451Q::getAccZ() {
    return getAccAxis(REG_OUT_Z_MSB);
}

void MMA8451Q::getAccAllAxis(int16_t * res) {
    res[0] = getAccX();
    res[1] = getAccY();
    res[2] = getAccZ();
}

int16_t MMA8451Q::getAccAxis(uint8_t addr) {
    int16_t acc;
    uint8_t res[2];
    read_regs(addr, res, 2);

    acc = (res[0] << 6) | (res[1] >> 2);
    if (acc > UINT14_MAX/2)
        acc -= UINT14_MAX;

    return acc;
}

void MMA8451Q::read_regs(int addr, uint8_t * data, int len) {
    char t[1] = {addr};
    m_i2c.write(m_addr, t, 1, true);
    m_i2c.read(m_addr, (char *)data, len);
}

void MMA8451Q::write_regs(uint8_t * data, int len) {
    m_i2c.write(m_addr, (char *)data, len);
}
