#pragma once

struct MoistureSensor
{
    int adc_channel;
    esp_adc_cal_characteristics_t *adc_chars;
};

extern struct MoistureSensor init_moisture_sensor(int gpio_pin);

extern uint32_t get_moisture(struct MoistureSensor *moisture_sensor);