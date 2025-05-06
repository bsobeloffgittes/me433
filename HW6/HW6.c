#include <stdio.h>
#include "pico/stdlib.h"
#include "io.h"

// I2C defines
// This example will use I2C0 on GPIO8 (SDA) and GPIO9 (SCL) running at 400KHz.
// Pins can be changed, see the GPIO function select table in the datasheet for information on GPIO assignments


#define ONBOARD_LED 25

void heartbeat(void);


int main()
{
    stdio_init_all();
    while(!stdio_usb_connected) {
        sleep_ms(100);
    }

    sleep_ms(10000);

    printf("here1");

    // I2C Initialisation. Using it at 400Khz.
    i2c_init(I2C_PORT, 400*1000);
    
    gpio_set_function(I2C_SDA, GPIO_FUNC_I2C);
    gpio_set_function(I2C_SCL, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_SDA);
    gpio_pull_up(I2C_SCL);
    // For more examples of I2C use see https://github.com/raspberrypi/pico-examples/tree/master/i2c



    gpio_init(ONBOARD_LED);
    gpio_set_dir(ONBOARD_LED, GPIO_OUT);


    printf("here2");
    set_gp7_out();



    while (true) {
        heartbeat();
        sleep_ms(5);
        read_pin(1);
        printf("test");
    }
}







void heartbeat() {
    static uint16_t i = 0;
    i = (i+1)%100;
    if(i==0) {
        gpio_put(ONBOARD_LED, 0);
        write_pin(7, 1);
    }
    else if(i==50) {
        gpio_put(ONBOARD_LED, 1);
        write_pin(7, 0);
    }
}