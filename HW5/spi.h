#ifndef SPI_H_
#define SPI_H_

#include "pico/stdlib.h"
#include "hardware/spi.h"

#define SPI_PORT spi0
#define PIN_MISO    16
#define PIN_DAC_CS  17
#define PIN_MEM_CS  1
#define PIN_SCK     18
#define PIN_MOSI    19


void pack_float_buffer(float val, uint8_t* buf);

union FloatInt {
    float f;
    uint32_t i;
};


#endif