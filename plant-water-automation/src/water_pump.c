#include <driver/gpio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include "water_pump.h"

struct WaterPump init_water_pump(int io_pin, int activation_time_ms)
{
    gpio_config_t io_conf;
    io_conf.intr_type = GPIO_PIN_INTR_DISABLE;
    io_conf.mode = GPIO_MODE_OUTPUT;
    io_conf.pin_bit_mask = 1ULL << io_pin;
    io_conf.pull_down_en = 0;
    io_conf.pull_up_en = 0;
    gpio_config(&io_conf);

    struct WaterPump water_pump;
    water_pump.activation_io = io_pin;
    water_pump.activation_time_ms = activation_time_ms;
    return water_pump;
}

void start_water_pump(struct WaterPump *pump)
{
    gpio_set_level(pump->activation_io, 1);
    vTaskDelay(pump->activation_time_ms / portTICK_RATE_MS);
    gpio_set_level(pump->activation_io, 0);
}