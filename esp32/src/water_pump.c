#include <driver/gpio.h>
#include "esp_sleep.h"
#include "esp_log.h"
#include "water_pump.h"

struct WaterPump init_water_pump(int io_pin, int activation_time)
{
	gpio_config_t io_conf;
	io_conf.intr_type = GPIO_PIN_INTR_DISABLE;
	io_conf.mode = GPIO_MODE_OUTPUT;
	io_conf.pin_bit_mask = 1ULL << io_pin;
	io_conf.pull_down_en = 0;
	io_conf.pull_up_en = 0;
	gpio_config(&io_conf);

	struct WaterPump water_pump;
	water_pump.io = io_pin;
	water_pump.time = activation_time;
	water_pump.activated = false;
	return water_pump;
}

void start_water_pump(struct WaterPump *pump)
{
	ESP_LOGW("DEBUG", "Starting water pump");
	pump->activated = true;
	gpio_set_level(pump->io, 1);
	esp_sleep_enable_timer_wakeup(pump->time);
	esp_deep_sleep_start();
}

void stop_water_pump(struct WaterPump *pump)
{
	ESP_LOGW("DEBUG", "Stopping water pump");
	pump->activated = false;
	gpio_set_level(pump->io, 0);
}