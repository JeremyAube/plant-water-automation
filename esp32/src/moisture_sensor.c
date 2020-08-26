#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "driver/adc.h"
#include "esp_log.h"
#include "esp_adc_cal.h"
#include "moisture_sensor.h"

const float MaxValue = 3500;
const float MinValue = 1200;

struct MoistureSensor init_moisture_sensor(int adc_channel)
{
	adc1_config_width(ADC_WIDTH_12Bit);
	adc1_config_channel_atten(adc_channel, ADC_ATTEN_11db);

	esp_adc_cal_characteristics_t *adc_chars = calloc(1, sizeof(esp_adc_cal_characteristics_t));
	esp_adc_cal_characterize(ADC_UNIT_1, ADC_ATTEN_11db, ADC_WIDTH_12Bit, ESP_ADC_CAL_VAL_DEFAULT_VREF, adc_chars);

	struct MoistureSensor moisture_sensor;
	moisture_sensor.adc_chars = adc_chars;
	moisture_sensor.adc_channel = adc_channel;
	return moisture_sensor;
}

// This returns a humidity percentage based on adc raw value
int get_percent(int raw_value)
{
	return (raw_value - MinValue) / MaxValue * 100;
}

uint32_t get_moisture(struct MoistureSensor *moisture_sensor)
{
	int value = adc1_get_raw(ADC1_GPIO34_CHANNEL);

	return get_percent(value);
}
