#include "ram.h"

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

void spi_ram_init() {

    uint8_t init_msg[2] = {WRITE_RAM_SR, RAM_SEQ_INIT};

    cs_select(PIN_MEM_CS);
    spi_write_blocking(SPI_PORT, init_msg, 2);
    cs_deselect(PIN_MEM_CS);
}

void pack_sin_wave() {

    uint8_t curr_float_buf[4];
    
    for(int i = 0; i < 1000; i++) {
        pack_float_buffer(sin(i * 2*M_PI /1000.0), curr_float_buf);

        spi_write_blocking(SPI_PORT, curr_float_buf, 4);
        
    }

    cs_deselect(PIN_MEM_CS);
}

void begin_ram_write(void) {
    uint8_t begin_write_buf = WRITE_RAM;
    
    cs_select(PIN_MEM_CS);
    spi_write_blocking(SPI_PORT, &begin_write_buf, 1);
}

