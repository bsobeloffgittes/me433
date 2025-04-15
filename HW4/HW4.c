#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/spi.h"
#include <math.h>

// SPI Defines
// We are going to use SPI 0, and allocate it to the following GPIO pins
// Pins can be changed, see the GPIO function select table in the datasheet for information on GPIO assignments
#define SPI_PORT spi0
#define PIN_MISO 16
#define PIN_CS   17
#define PIN_SCK  18
#define PIN_MOSI 19

#define DATA_A_MASK 0b00110000
#define DATA_B_MASK 0b10110000


static inline void cs_select(uint cs_pin);
static inline void cs_deselect(uint cs_pin);

uint16_t get_sin_val();
uint16_t get_tri_val();

void pack_buffer(uint8_t* buffer, uint8_t mask, uint16_t num);

uint16_t out_a;
uint16_t out_b;

int main()
{
    stdio_init_all();

    // SPI initialisation. This example will use SPI at 1MHz.
    spi_init(SPI_PORT, 1000*1000);
    gpio_set_function(PIN_MISO, GPIO_FUNC_SPI);
    gpio_set_function(PIN_CS,   GPIO_FUNC_SIO);
    gpio_set_function(PIN_SCK,  GPIO_FUNC_SPI);
    gpio_set_function(PIN_MOSI, GPIO_FUNC_SPI);
    
    // Chip select is active-low, so we'll initialise it to a driven-high state
    gpio_set_dir(PIN_CS, GPIO_OUT);
    gpio_put(PIN_CS, 1);
    // For more examples of SPI use see https://github.com/raspberrypi/pico-examples/tree/master/spi

    while (true) {
        // printf("Hello, world!\n");
        // sleep_ms(1000);
        // uint8_t data_a[] = {0b00110100, 0};
        // uint8_t data_b[] = {0b10111000, 0};

        uint8_t data_a[2];
        uint8_t data_b[2];

        pack_buffer(data_a, DATA_A_MASK, 750);
        pack_buffer(data_b, DATA_B_MASK, 500);

        // Write over spi
        cs_select(PIN_CS);
        spi_write_blocking(SPI_PORT, data_a, 2);
        cs_deselect(PIN_CS);
        cs_select(PIN_CS);
        spi_write_blocking(SPI_PORT, data_b, 2);
        cs_deselect(PIN_CS);

        // Loop at 1 kHz
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


uint16_t get_sin_val() {
    static uint16_t t = 0;

    uint16_t output = (uint16_t) ((1023/2)*sin((((float) t) * 2 * M_PI)/1000) + 1023/2);
    
    t = (t+1)%1000;

    return output;
}


void pack_buffer(uint8_t* buffer, uint8_t mask, uint16_t num) {
    int new_num = num & 0x3FF;
    buffer[0] = mask | new_num >> 6;
    buffer[1] = (new_num && 0x3F) << 2;
}