/*
 * main.c
 */

#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/sys/printk.h>
#include <inttypes.h>

#include "BTN.h"
#include "LED.h"

#define SLEEP_TIME_MS 1

uint8_t counter = 0;

void update_LEDs(uint8_t num) {
 
    uint8_t led0_val = (num >> 0) & 1;
    uint8_t led1_val = (num >> 1) & 1;
    uint8_t led2_val = (num >> 2) & 1;
    uint8_t led3_val = (num >> 3) & 1;

    LED_set(LED0, led0_val);
    LED_set(LED1, led1_val);
    LED_set(LED2, led2_val);
    LED_set(LED3, led3_val); 

    return;
}

int main(void) {
    
    if (BTN_init() < 0) {
	return 0;
    }

    if (LED_init() < 0) {
	return 0;
    }

    while(1) {
	if (BTN_check_clear_pressed(BTN0)) {
	    counter += 1;    	
	}
	k_msleep(SLEEP_TIME_MS);
	
	if (counter == 16) {
	    counter = 0;
	}

	update_LEDs(counter);
    }

    return 0;
}
