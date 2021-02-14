/**
 * Temperature sensor test for Raspberry Pi Pico
 *   by Pa@ART   Feb.14, 2021
 */

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/adc.h"

#define VREF        3.25f   // Voltage of Vref
#define CONV_FACTOR (VREF / (1 << 12)) // conversion factor
#define TEMP_ADC    4   // ADC number of temperature sensor

int main() {

    uint16_t temp_dat;
    float temp, voltage;
    const uint LED_PIN = 25;
    bool state = true;

    // initialize stdio
    stdio_init_all();
    // initialize ADC
    adc_init();
    // set temperature sensor enabled
    adc_set_temp_sensor_enabled(true);
    // select ADC input
    adc_select_input(TEMP_ADC);    // temperature sensor selected
    // set LED pin as output mode
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    while (1) {
        // read raw data from ADC
        temp_dat = adc_read();
        // convert raw to voltage
        voltage = temp_dat * CONV_FACTOR;
        // convert voltage to temperature
        temp = 27 - (voltage - 0.706) / 0.001721;
        printf("Voltage:%2.3f[V], Temperature:%2.2f[C]\n", voltage, temp);
        // toggle LED
        gpio_put(LED_PIN, state);
        sleep_ms(500);
        state = !state;
    }

    return 0;
}
