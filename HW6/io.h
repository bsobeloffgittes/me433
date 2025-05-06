#ifndef IO_H_
#define IO_H_

#include "hardware/i2c.h"
#include <stdio.h>
#include "pico/stdlib.h"

#define I2C_PORT i2c0
#define I2C_SDA 4
#define I2C_SCL 5
#define MCP_ADDR 0b100000

#define IODIR 0x00
#define IPOL 0x01
#define GPINTEN 0x02
#define DEFVAL 0x03
#define INTCON 0x04
#define IOCON 0x05
#define GPPU 0x06
#define INTF 0x07
#define INTCAP 0x08
#define GPIO 0x09
#define OLAT 0x0A


void write_pin(uint8_t pin, bool val);
uint8_t read_pin(uint8_t pin);

void set_gp7_out(void);




#endif