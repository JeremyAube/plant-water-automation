#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "driver/adc.h"
#include "esp_log.h"
#include "esp_adc_cal.h"
#include "water_pump.h"

void app_main(void)
{
    adc1_config_width(ADC_WIDTH_12Bit);
    adc1_config_channel_atten(ADC1_GPIO34_CHANNEL, ADC_ATTEN_11db);

    esp_adc_cal_characteristics_t *adc_chars = calloc(1, sizeof(esp_adc_cal_characteristics_t));
    esp_adc_cal_characterize(ADC_UNIT_1, ADC_ATTEN_11db, ADC_WIDTH_12Bit, ESP_ADC_CAL_VAL_DEFAULT_VREF, adc_chars);

    struct WaterPump water_pump = init_water_pump(15, 500);

    while (1)
    {
        int value = adc1_get_raw(ADC1_GPIO34_CHANNEL);
        int voltage = esp_adc_cal_raw_to_voltage(value, adc_chars);

        if (voltage < 1500)
        {
            start_water_pump(&water_pump);
            printf("start water");
        }

        ESP_LOGW("adc1", "value %d", voltage);
        vTaskDelay(1000 / portTICK_RATE_MS);
    }
}
