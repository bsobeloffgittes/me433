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

void pack_buffer(uint8_t* buffer, uint8_t mask, uint16_t num);

void count_cycles(void);

int main() {

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

    // while(!stdio_usb_connected()) {
    //     sleep_ms(100);
    // }

    // Perform the clock cycle counting part of the assignment
    // count_cycles();

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
















void count_cycles() {
    volatile float f1, f2;
    printf("Enter two floats to use:");
    scanf("%f %f", &f1, &f2);
    volatile float f_add, f_sub, f_mult, f_div;

    absolute_time_t t1 = get_absolute_time();
    for(int i = 0; i < 1000; i++) {
        f_add = f1 + f2;
    }
    absolute_time_t t2 = get_absolute_time();
    uint64_t t_add = (to_us_since_boot(t2) - to_us_since_boot(t1))/(6.667);

    t1 = get_absolute_time();
    for(int i = 0; i < 1000; i++) {
        f_sub = f1 - f2;
    }
    t2 = get_absolute_time();
    uint64_t t_sub = (to_us_since_boot(t2) - to_us_since_boot(t1))/(6.667);

    t1 = get_absolute_time();
    for(int i = 0; i < 1000; i++) {
        f_mult = f1 * f2;
    }
    t2 = get_absolute_time();
    uint64_t t_mult = (to_us_since_boot(t2) - to_us_since_boot(t1))/(6.667);

    t1 = get_absolute_time();
    for(int i = 0; i < 1000; i++) {
        f_div = f1 / f2;
    }
    t2 = get_absolute_time();
    uint64_t t_div = (to_us_since_boot(t2) - to_us_since_boot(t1))/(6.667);

    printf("\nResults: \n%f+%f=%f \n%f-%f=%f \n%f*%f=%f \n%f/%f=%f\n", f1,f2,f_add, f1,f2,f_sub, f1,f2,f_mult, f1,f2,f_div);

    printf("\nClock cycles:\nAddition: %llu\nSubtraction: %llu\nMultiplication: %llu\nDivision: %llu", t_add, t_sub, t_mult, t_div);
}