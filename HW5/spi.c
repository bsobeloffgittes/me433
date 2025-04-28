#include "spi.h"




void pack_float_buffer(float val, uint8_t* buf) {
    union FloatInt pack_num;
    pack_num.f = val;

    for(int i = 0; i < 4; i++) {
        buf[i] = (pack_num.i >> 8*i) & 0xFF;

    }
}