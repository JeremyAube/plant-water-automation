#include "driver/gpio.h"
#include "driver/adc.h"
#include "esp_log.h"
#include "esp_adc_cal.h"
#include "esp_sleep.h"
#include "moisture_sensor.h"
#include "water_pump.h"

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

// This value is found by trial and error
int MIN_MOISTURE = 2300;		 // TODO: This is just a rough estimate. Need to find better value
int SLEEP_TIME = 3600000000; // This is in microseconds

void app_main(void)
{
	struct MoistureSensor moisture_sensor = init_moisture_sensor(ADC1_GPIO34_CHANNEL);
	struct WaterPump water_pump = init_water_pump(15, 3000);

	int moisture = get_moisture(&moisture_sensor);
	printf("moisture: %d", moisture);
	if (moisture > MIN_MOISTURE)
	{
		start_water_pump(&water_pump);
	}

	esp_sleep_enable_timer_wakeup(SLEEP_TIME);
	esp_deep_sleep_start();
}
