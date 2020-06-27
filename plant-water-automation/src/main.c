#include "water_pump.h"
#include "esp_log.h"

#define WATER_PUMP_IO 15

void app_main(void)
{
    struct WaterPump water_pump = init_water_pump(WATER_PUMP_IO, 2500);

    start_water_pump(&water_pump);
    start_water_pump(&water_pump);
    start_water_pump(&water_pump);

    while (1)
    {
        ESP_LOGW("debug", "water_pump");
    }
}
