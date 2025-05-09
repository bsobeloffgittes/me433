#include <stdio.h>
#include "pico/stdlib.h"
#include "ssd1306.h"
#include "hardware/i2c.h"
#include "font.h"
#include "hardware/adc.h"

// I2C defines
// This example will use I2C0 on GPIO8 (SDA) and GPIO9 (SCL) running at 400KHz.
// Pins can be changed, see the GPIO function select table in the datasheet for information on GPIO assignments
#define I2C_PORT i2c0
#define I2C_SDA 4
#define I2C_SCL 5

#define ONBOARD_LED 25

void heartbeat(void);
void draw_letter(char c, uint8_t x, uint8_t y);
void draw_message(char* c, uint8_t x, uint8_t y);


int main()
{
    stdio_init_all();

    // I2C Initialisation. Using it at 400Khz.
    i2c_init(I2C_PORT, 400*1000);
    
    gpio_set_function(I2C_SDA, GPIO_FUNC_I2C);
    gpio_set_function(I2C_SCL, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_SDA);
    gpio_pull_up(I2C_SCL);
    // For more examples of I2C use see https://github.com/raspberrypi/pico-examples/tree/master/i2c

    ssd1306_setup();
    sleep_ms(100);
    // ssd1306_clear();

    // Initialize ADC
    adc_init();
    adc_gpio_init(26); // ADC0 pin is used as ADC
    adc_select_input(0); // select to read from ADC0



    gpio_init(ONBOARD_LED);
    gpio_set_dir(ONBOARD_LED, GPIO_OUT);

    unsigned int past_t = 0;
    unsigned int t;

    char fps_msg[10];
    char message[50];


    while (true) {
        heartbeat();
        // sleep_ms(5);
        // ssd1306_drawPixel(0,0,1);
        // draw_letter('A', 10, 5);

        t = to_us_since_boot(get_absolute_time());

        sprintf(fps_msg, "fps: %d", 1000000 / (t - past_t));

        past_t = t;

        draw_message(fps_msg, 17*5, 25);

        uint16_t adc_val = adc_read();
        sprintf(message, "ADC: %d", adc_val);
        draw_message(message, 10, 10);

        ssd1306_update();

    }
}







void heartbeat() {
    static uint16_t i = 0;
    i = (i+1)%100;
    if(i==0) {
        gpio_put(ONBOARD_LED, 0);
    }
    else if(i==50) {
        // ssd1306_drawPixel(0,0,0);
        // ssd1306_clear();
        gpio_put(ONBOARD_LED, 1);
    }
}





void draw_letter(char c, uint8_t x, uint8_t y) {

    for(int i = 0; i < 5; i++) {
        for(int j = 0; j < 8; j++) {
            ssd1306_drawPixel(x + i,y + j,((ASCII[c-0x20][i]) >> j) & 0x01);
        }
    }
}

void draw_message(char* c, uint8_t x, uint8_t y) {
    for(int i = 0; i < 100; i++) {

        char next_char = c[i];

        if(!next_char) break; // end if null terminator

        draw_letter(next_char, x + 6*i, y);
    }
}
