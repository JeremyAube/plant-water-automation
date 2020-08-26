#include "driver/gpio.h"
#include "driver/adc.h"
#include "esp_log.h"
#include "esp_adc_cal.h"
#include "esp_sleep.h"
#include "moisture_sensor.h"
#include "water_pump.h"

// This value is found by trial and error
int MIN_MOISTURE = 50;
RTC_DATA_ATTR bool first_boot = false;
RTC_DATA_ATTR struct MoistureSensor moisture_sensor;
RTC_DATA_ATTR struct WaterPump water_pump;

void check_moisture_level()
{
	int moisture = get_moisture(&moisture_sensor);
	ESP_LOGW("DEBUG", "Moisture: %d", moisture);

	if (moisture > MIN_MOISTURE)
	{
		start_water_pump(&water_pump);
	}
}

void app_main(void)
{
	if (!first_boot)
	{
		moisture_sensor = init_moisture_sensor(ADC1_GPIO34_CHANNEL);
		water_pump = init_water_pump(15, 500);
		gpio_set_level(water_pump.io, 0);
		first_boot = true;
		ESP_LOGW("DEBUG", "Initialized");
	}

	ESP_LOGW("OUTPUT", "Water pump is on: %d", water_pump.activated);
	if (water_pump.activated)
	{
		stop_water_pump(&water_pump);
	}
	else
	{
		check_moisture_level();
	}

	esp_sleep_enable_timer_wakeup(3000000);
	esp_deep_sleep_start();
}
