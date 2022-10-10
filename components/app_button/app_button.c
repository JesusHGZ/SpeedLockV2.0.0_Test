#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "driver/gpio.h"
#include "esp_log.h"
#include "esp_err.h"
#include "app_button.h"


static uint8_t g_btn;
static const char TAG[] = "led";

esp_err_t app_button_init(const uint8_t pin_btn)
{
    ESP_LOGI(TAG, "app_btn_init");
    esp_err_t esp_err;
    gpio_config_t config_btn = 
    {
        .pin_bit_mask = (1ULL << pin_btn),
        .mode = GPIO_MODE_INPUT,
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_ENABLE,
        .intr_type = GPIO_INTR_DISABLE,
    };

    esp_err = gpio_config(&config_btn);

    if (esp_err != ESP_OK)
    {
        printf("app_btn_init: Error (%s). Pin %d\n", esp_err_to_name(esp_err), pin_btn);
        return esp_err;
    }
    g_btn = pin_btn;
    return ESP_OK;
}


bool app_button_read(void)
{
    return gpio_get_level(g_btn);
}