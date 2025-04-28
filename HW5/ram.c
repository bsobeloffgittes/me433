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

    // Send stuff to start writing
    begin_ram_write(0);
    
    for(int i = 0; i < 1000; i++) {
        pack_float_buffer(sin(i * 2*M_PI /1000.0), curr_float_buf);

        spi_write_blocking(SPI_PORT, curr_float_buf, 4);
        
    }

    // end communication
    cs_deselect(PIN_MEM_CS);
}

void begin_ram_write(uint16_t addr) {
    uint8_t begin_write_buf = WRITE_RAM;
    uint8_t addr_buf[2];

    pack_addr_buf(addr, addr_buf);
    
    
    cs_select(PIN_MEM_CS);
    spi_write_blocking(SPI_PORT, &begin_write_buf, 1);
    spi_write_blocking(SPI_PORT, addr_buf, 2);
}

void pack_addr_buf(uint16_t addr, uint8_t* buf) {
    buf[0] = (uint8_t) (addr & 0xFF);
    buf[1] = (uint8_t) (addr >> 8) & 0xFF;
}

void read_ram_bytes(uint16_t addr, uint8_t len, uint8_t* dst_buf) {
    uint8_t begin_read_buf = READ_RAM;
    uint8_t addr_buf[2];

    pack_addr_buf(addr, addr_buf);

    cs_select(PIN_MEM_CS);
    spi_write_blocking(SPI_PORT, &begin_read_buf, 1);
    spi_write_blocking(SPI_PORT, addr_buf, 2);

    spi_read_blocking(SPI_PORT, 0, dst_buf, len);

    cs_deselect(PIN_MEM_CS);
}