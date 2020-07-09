#include "wifi.h"
#include "esp_wifi.h"
#include "wifi_config.h"

void init_wifi()
{
    wifi_init_config_t wifi_init_config = WIFI_INIT_CONFIG_DEFAULT();
    esp_wifi_init(&wifi_init_config);
    wifi_config_t wifi_config = {
        .sta = {
            .ssid = WIFI_CONFIG_SSID,
            .password = WIFI_CONFIG_PASSWORD,
            .threshold.authmode = WIFI_AUTH_WPA2_PSK,
            .pmf_cfg = {
                .capable = true,
                .required = false,
            },
        },
    };
    esp_wifi_set_config(ESP_IF_WIFI_STA, &wifi_config);
    esp_wifi_set_mode(WIFI_MODE_STA);
    esp_wifi_start();
}