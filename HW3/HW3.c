#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/adc.h"

#define LED_PIN 19
#define BUTTON_PIN 16



bool button_pressed;


void gpio_callback(uint gpio, uint32_t events) {
    // Do what needs to happen when button pressed
    button_pressed = true;
}

// Perform initialisation
int pico_led_init(void) {
    // A device like Pico that uses a GPIO for the LED so we can
    // use normal GPIO functionality to turn the led on and off
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    return PICO_OK;
}

int main()
{
    button_pressed = false;

    stdio_init_all();

    // Initialize LED pin
    int rc = pico_led_init();
    hard_assert(rc == PICO_OK);

    // turn off LED
    gpio_put(LED_PIN, false);



    while(!stdio_usb_connected()) {
        sleep_ms(100);
    }



    // Init interrupt on button
    gpio_init(BUTTON_PIN);
    gpio_pull_up(BUTTON_PIN);
    gpio_set_irq_enabled_with_callback(BUTTON_PIN, GPIO_IRQ_EDGE_FALL, true, &gpio_callback);



    // turn on LED
    gpio_put(LED_PIN, true);

    // turn LED off when button pressed
    while(!button_pressed) {
        sleep_ms(10);
    }
    gpio_put(LED_PIN, false);


    // Initialize ADC
    adc_init();
    adc_gpio_init(26); // ADC0 pin is used as ADC
    adc_select_input(0); // select to read from ADC0


    while(1) {

        // ask user for num of ADC samples
        int16_t num_samples;
        printf("Enter a number of samples: \n");
        scanf("%d", &num_samples);

        for(int16_t i = num_samples; i > 0; i--) {
            uint16_t adc_val = adc_read();
            printf("%.2f V\n", (3.3/4095.0)*((float)adc_val));
            sleep_ms(10);
        }
    }
}
