#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "driver/adc.h"
#include "esp_log.h"
#include "esp_adc_cal.h"
#include "moisture_sensor.h"
#include "water_pump.h"

void app_main(void)
{
    struct MoistureSensor moisture_sensor = init_moisture_sensor(ADC1_GPIO34_CHANNEL);
    struct WaterPump water_pump = init_water_pump(15, 500);

    while (1)
    {
        int voltage = get_moisture(&moisture_sensor);

        if (voltage < 1500)
        {
            start_water_pump(&water_pump);
            printf("start water");
        }

        ESP_LOGW("adc1", "value %d", voltage);
        vTaskDelay(1000 / portTICK_RATE_MS);
    }
}
