#include "freertos/FreeRTOS.h"
#include "freertos/event_groups.h"
#include "wifi.h"
#include "esp_wifi.h"
#include "esp_log.h"
#include "wifi_config.h"

#define WIFI_CONNECTED_BIT BIT0
#define WIFI_FAIL_BIT BIT1
static const char *TAG = "wifi station";
static EventGroupHandle_t s_wifi_event_group;

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

    /* Waiting until either the connection is established (WIFI_CONNECTED_BIT) or connection failed for the maximum
     * number of re-tries (WIFI_FAIL_BIT). The bits are set by event_handler() (see above) */
    EventBits_t bits = xEventGroupWaitBits(s_wifi_event_group,
                                           WIFI_CONNECTED_BIT | WIFI_FAIL_BIT,
                                           pdFALSE,
                                           pdFALSE,
                                           portMAX_DELAY);

    if (bits & WIFI_CONNECTED_BIT)
    {
        ESP_LOGI(TAG, "connected to wifi!");
    }
    else if (bits & WIFI_FAIL_BIT)
    {
        ESP_LOGI(TAG, "Failed to connect to wifi!");
    }
    else
    {
        ESP_LOGI(TAG, "UNEXPECTED EVENT");
    }
}