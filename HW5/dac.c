#include "dac.h"

static inline void cs_select(uint cs_pin);
static inline void cs_deselect(uint cs_pin);

static inline void cs_select(uint cs_pin) {
    asm volatile("nop \n nop \n nop"); // FIXME
    gpio_put(cs_pin, 0);
    asm volatile("nop \n nop \n nop"); // FIXME
}

static inline void cs_deselect(uint cs_pin) {
    asm volatile("nop \n nop \n nop"); // FIXME
    gpio_put(cs_pin, 1);
    asm volatile("nop \n nop \n nop"); // FIXME
}

void pack_dac_buffer(uint8_t* buffer, uint8_t mask, uint16_t num) {
    int new_num = num & 0x3FF;
    buffer[0] = mask | new_num >> 6;
    buffer[1] = (new_num && 0x3F) << 2;
}

void set_dac_volt_a(float volts) {
    uint16_t output_int = (uint16_t) (1023*(volts / 3.3));
    
    uint8_t output_buffer[2];

    pack_dac_buffer(output_buffer, DATA_A_MASK, output_int);

    cs_select(PIN_DAC_CS);
    spi_write_blocking(SPI_PORT, output_buffer, 2);
    cs_deselect(PIN_DAC_CS);
}