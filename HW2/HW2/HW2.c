#include <stdio.h>
#include "pico/stdlib.h"

#define LED_PIN 19
#define BUTTON_PIN 


// Perform initialisation
int pico_led_init(void) {
    // A device like Pico that uses a GPIO for the LED so we can
    // use normal GPIO functionality to turn the led on and off
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    return PICO_OK;
}

// Turn the led on or off
void pico_set_led(bool led_on) {
    // Just set the GPIO on or off
    gpio_put(LED_PIN, led_on);
}

int main()
{
    stdio_init_all();

    // Initialize LED pin
    int rc = pico_led_init();
    hard_assert(rc == PICO_OK);

    while (true) {
        pico_set_led(true);
        sleep_ms(1000);
        pico_set_led(false);
        sleep_ms(1000);
    }
}
