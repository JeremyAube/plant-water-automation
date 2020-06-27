#pragma once

struct WaterPump
{
    int activation_io;
    int activation_time_ms;
};

extern struct WaterPump init_water_pump(int io_pin, int activation_time_ms);
extern void start_water_pump(struct WaterPump *pump);
