#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"

#define LED_PIN 19
#define BUTTON_PIN 16


static char event_str[128];

uint16_t num_presses;

void gpio_event_string(char *buf, uint32_t events);

void gpio_callback(uint gpio, uint32_t events) {
    // Put the GPIO event(s) that just happened into event_str
    // so we can print it
    gpio_put(LED_PIN, (++num_presses)%2);
    printf("Number of presses: %d\r\n", num_presses);

}


// Perform initialisation
int pico_led_init(void) {
    // A device like Pico that uses a GPIO for the LED so we can
    // use normal GPIO functionality to turn the led on and off
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    return PICO_OK;
}

// // Turn the led on or off
// void pico_set_led(bool led_on) {
//     // Just set the GPIO on or off
//     gpio_put(LED_PIN, led_on);
    
// }

int main()
{
    stdio_init_all();

    // Init interrupt on button
    gpio_init(BUTTON_PIN);
    gpio_pull_up(BUTTON_PIN);
    gpio_set_irq_enabled_with_callback(BUTTON_PIN, GPIO_IRQ_EDGE_FALL, true, &gpio_callback);

    // Initialize LED pin
    int rc = pico_led_init();
    hard_assert(rc == PICO_OK);

    // initialize variables to keep track of button presses
    num_presses = 0;

    while (1);
}






// // Extra stuff for interrupt
// static const char *gpio_irq_str[] = {
//     "LEVEL_LOW",  // 0x1
//     "LEVEL_HIGH", // 0x2
//     "EDGE_FALL",  // 0x4
//     "EDGE_RISE"   // 0x8
// };

// void gpio_event_string(char *buf, uint32_t events) {
// for (uint i = 0; i < 4; i++) {
//     uint mask = (1 << i);
//     if (events & mask) {
//         // Copy this event string into the user string
//         const char *event_str = gpio_irq_str[i];
//         while (*event_str != '\0') {
//             *buf++ = *event_str++;
//         }
//         events &= ~mask;

//         // If more events add ", "
//         if (events) {
//             *buf++ = ',';
//             *buf++ = ' ';
//         }
//     }
// }
// *buf++ = '\0';
// }
