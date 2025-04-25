#ifndef DAC_H_
#define DAC_H_

#include "spi.h"

#define DATA_A_MASK 0b00110000
#define DATA_B_MASK 0b10110000

void pack_dac_buffer(uint8_t* buffer, uint8_t mask, uint16_t num);

void set_dac_volt_a(float volts);

#endif