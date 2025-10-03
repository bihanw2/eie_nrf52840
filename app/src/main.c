/*
 * main.c
 */

#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>

#define LED0_NODE DT_ALIAS(led0)
#define LED1_NODE DT_ALIAS(led1)
#define LED2_NODE DT_ALIAS(led2)
#define LED3_NODE DT_ALIAS(led3)

static const struct gpio_dt_spec led0 = GPIO_DT_SPEC_GET(LED0_NODE, gpios);
static const struct gpio_dt_spec led1 = GPIO_DT_SPEC_GET(LED1_NODE, gpios);
static const struct gpio_dt_spec led2 = GPIO_DT_SPEC_GET(LED2_NODE, gpios);
static const struct gpio_dt_spec led3 = GPIO_DT_SPEC_GET(LED3_NODE, gpios);

void drive_num_pattern(uint8_t num) {
	
	uint8_t led0_val = (num >> 0) & 1;
	uint8_t led1_val = (num >> 1) & 1;
	uint8_t led2_val = (num >> 2) & 1;
	uint8_t led3_val = (num >> 3) & 1;

	gpio_pin_set_dt(&led0, led0_val);
	gpio_pin_set_dt(&led1, led1_val);
	gpio_pin_set_dt(&led2, led2_val);
	gpio_pin_set_dt(&led3, led3_val);

	return;
}

int main(void) {
	int ret0;
	int ret1;
	int ret2;
	int ret3;

	if (!gpio_is_ready_dt(&led0) || !gpio_is_ready_dt(&led1) || !gpio_is_ready_dt(&led2) || !gpio_is_ready_dt(&led3)) {
		return -1;
	}

	ret0 = gpio_pin_configure_dt(&led0, GPIO_OUTPUT_ACTIVE);
	ret1 = gpio_pin_configure_dt(&led1, GPIO_OUTPUT_ACTIVE);
	ret2 = gpio_pin_configure_dt(&led2, GPIO_OUTPUT_ACTIVE);
	ret3 = gpio_pin_configure_dt(&led3, GPIO_OUTPUT_ACTIVE);

	if (ret0 < 0 || ret1 < 0 || ret2 < 0 || ret3 < 0) {
		return -1;
	}

	while (1) {
		for (uint8_t i = 0; i < 16; i++) {
			drive_num_pattern(i);
			k_msleep(1000);
		}
	}
	
	return 0;
}
