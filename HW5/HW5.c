#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/spi.h"



int main() {

    stdio_init_all();

    while(!stdio_usb_connected()) {
        sleep_ms(100);
    }

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

    while (true) {
        //printf("Hello, world!\n");
        sleep_ms(1000);
    }
}
