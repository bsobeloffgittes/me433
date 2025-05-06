#include "io.h"

void write_pin(uint8_t pin, bool val) {
    uint8_t data[2] = {GPIO, val << (pin)};
    i2c_write_blocking(I2C_PORT, MCP_ADDR, data, 2, false);
}


uint8_t read_pin(uint8_t pin) {
    uint8_t data;
    uint8_t reg = GPIO;
    i2c_write_blocking(I2C_PORT, MCP_ADDR, &reg, 1, true);
    i2c_read_blocking(I2C_PORT, MCP_ADDR, &data, 1, false);

    return data & (0b1 << pin);
}

void set_gp7_out() {
    uint8_t data[2] = {IODIR, 0b01111111};
    i2c_write_blocking(I2C_PORT, MCP_ADDR, data, 2, false);
}