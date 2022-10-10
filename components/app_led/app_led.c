#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "driver/gpio.h"
#include "app_led.h"
#include <stdbool.h>


static uint8_t g_led_interface;
static const char TAG[] = "led";

esp_err_t app_led_init(uint8_t pin_led)
{
    esp_err_t esp_err;
    ESP_LOGI(TAG, "app_led_init");

    esp_err = gpio_set_direction(pin_led, GPIO_MODE_OUTPUT);
    if (esp_err != ESP_OK)
    {
        printf("app_led_init: Error (%s). Pin %d\n", esp_err_to_name(esp_err), pin_led);
        return esp_err;
    }

    g_led_interface = pin_led;
    return ESP_OK;
}

esp_err_t app_led_enable(void)
{
    esp_err_t esp_err;

    esp_err = gpio_set_level(g_led_interface, true);
    if (esp_err != ESP_OK)
    {
        printf("app_led_enable_led_calib_interface: Error (%s). Pin %d\n", esp_err_to_name(esp_err), g_led_interface);
        return esp_err;
    }

    return ESP_OK;
}

esp_err_t app_led_disable(void)
{
    esp_err_t esp_err;

    esp_err = gpio_set_level(g_led_interface, false);
    if (esp_err != ESP_OK)
    {
        printf("app_led_disable_led_calib_interface: Error (%s). Pin %d\n", esp_err_to_name(esp_err), g_led_interface);
        return esp_err;
    }

    return ESP_OK;
}

esp_err_t app_led_toggle(const uint32_t delay_ms_led)
{
    esp_err_t esp_err;

    esp_err = app_led_enable();
    if (esp_err != ESP_OK)
    {
        return esp_err;
    }
    vTaskDelay(delay_ms_led / portTICK_RATE_MS);

    esp_err = app_led_disable();
    if (esp_err != ESP_OK)
    {
        return esp_err;
    }
    vTaskDelay(delay_ms_led / portTICK_RATE_MS);
    return ESP_OK;
}