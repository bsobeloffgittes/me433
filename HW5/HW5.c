#include <stdio.h>
#include "pico/stdlib.h"

#include "timing.h"
#include "ram.h"
#include "dac.h"
#include "spi.h"



// SPI Defines
// We are going to use SPI 0, and allocate it to the following GPIO pins
// Pins can be changed, see the GPIO function select table in the datasheet for information on GPIO assignments
#define SPI_PORT spi0
#define PIN_MISO    16
#define PIN_DAC_CS  17
#define PIN_MEM_CS  1
#define PIN_SCK     18
#define PIN_MOSI    19






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
