#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/spi.h"
#include <math.h>
#include "timing.h"


// SPI Defines
// We are going to use SPI 0, and allocate it to the following GPIO pins
// Pins can be changed, see the GPIO function select table in the datasheet for information on GPIO assignments
#define SPI_PORT spi0
#define PIN_MISO    16
#define PIN_DAC_CS  17
#define PIN_MEM_CS  1
#define PIN_SCK     18
#define PIN_MOSI    19

#define DATA_A_MASK 0b00110000
#define DATA_B_MASK 0b10110000


static inline void cs_select(uint cs_pin);
static inline void cs_deselect(uint cs_pin);

void pack_buffer(uint8_t* buffer, uint8_t mask, uint16_t num);

int main() {

    stdio_init_all();

    // SPI initialisation. This example will use SPI at 1MHz.
    spi_init(SPI_PORT, 1000*1000);
    gpio_set_function(PIN_MISO, GPIO_FUNC_SPI);
    gpio_set_function(PIN_DAC_CS,   GPIO_FUNC_SIO);
    gpio_set_function(PIN_MEM_CS,   GPIO_FUNC_SIO);
    gpio_set_function(PIN_SCK,  GPIO_FUNC_SPI);
    gpio_set_function(PIN_MOSI, GPIO_FUNC_SPI);
    
    // Chip select is active-low, so we'll initialise it to a driven-high state
    gpio_set_dir(PIN_DAC_CS, GPIO_OUT);
    gpio_put(PIN_DAC_CS, 1);
    gpio_set_dir(PIN_MEM_CS, GPIO_OUT);
    gpio_put(PIN_MEM_CS, 1);

    // Perform the clock cycle counting part of the assignment
    //count_cycles();

    while (true) {
        sleep_ms(1000);
    }
}





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


void pack_buffer(uint8_t* buffer, uint8_t mask, uint16_t num) {
    int new_num = num & 0x3FF;
    buffer[0] = mask | new_num >> 6;
    buffer[1] = (new_num && 0x3F) << 2;
}