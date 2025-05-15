/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/multicore.h"
#include "hardware/gpio.h"
#include "hardware/adc.h"

#define LED_PIN 15
#define ADC_PIN 26

#define FLAG0 0
#define FLAG1 1
#define FLAG2 2

void core1_entry() {


    adc_init();
    adc_gpio_init(ADC_PIN); // ADC0 pin is used as ADC
    adc_select_input(0); // select to read from ADC0

    // printf("in core1\n");

    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    // multicore_fifo_push_blocking(FLAG_VALUE);

    // printf("pushed\n");

    // uint32_t g = multicore_fifo_pop_blocking();

    // if (g != FLAG_VALUE)
    //     printf("Hmm, that's not right on core 1!\n");
    // else
    //     printf("Its all gone well on core 1!");

    while (1) {
        uint32_t g = multicore_fifo_pop_blocking();

        char msg[50];

        sleep_ms(100);

        // sprintf(msg, "flag recieved: %d", g);
        printf(msg);

        if(g == FLAG0) {
            uint32_t adc_val = (uint32_t) adc_read();
            multicore_fifo_push_blocking((uint32_t) adc_val);
        } else if (g == FLAG1) {
            gpio_put(LED_PIN, true);
        } else if (g == FLAG2) {
            gpio_put(LED_PIN, false);
        }
    }
        // tight_loop_contents();
}

int main() {
    stdio_init_all();


    while (!stdio_usb_connected()) {
        sleep_ms(100);
    }


    printf("Hello, multicore!\n");


    /// \tag::setup_multicore[]

    multicore_launch_core1(core1_entry);

    // Wait for it to start up

    printf("Launched Core 1\n");

    // uint32_t g = multicore_fifo_pop_blocking();

    // if (g != FLAG_VALUE)
    //     printf("Hmm, that's not right on core 0!\n");
    // else {
    //     multicore_fifo_push_blocking(FLAG_VALUE);
    //     printf("It's all gone well on core 0!");
    // }

    while(1) {
        char msg[50];
        uint32_t flag_num;

        scanf("%d", &flag_num);

        sprintf(msg, "%d\n", flag_num);
        printf(msg);

        multicore_fifo_push_blocking(flag_num);

        if(flag_num == FLAG0) {
            // printf("flag0");
            uint32_t g = multicore_fifo_pop_blocking();
            sprintf(msg, "Voltage: %0.2f\n", (3.3 * ((float) g))/4095.0);
            printf(msg);
        }
    }

    /// \end::setup_multicore[]
}
