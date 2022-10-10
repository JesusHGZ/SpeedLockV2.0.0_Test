#include <stdio.h>
#include <string.h>

#include "esp_log.h"
#include "esp_err.h"
#include "nvs_flash.h"
#include "app_nvs.h"


static const char TAG[] = "nvs";
const char app_nvs_adc[] = "adc_idle";
const char app_nvs_siganl[] = "signal_idle";

esp_err_t app_nvs_save_adc(uint8_t *const ptr_byte)
{
    nvs_handle handle;
    esp_err_t esp_err;

    ESP_LOGI(TAG, "app_nvs_save_adc");

    // Open NVS
    esp_err = nvs_open(app_nvs_adc, NVS_READWRITE, &handle);

    if (esp_err != ESP_OK)
    {
        ESP_ERROR_CHECK(nvs_flash_erase());
        return esp_err;
    }

    // Saving ADC1
    esp_err = nvs_set_u8(handle, "adc1", ptr_byte[0]);
    if (esp_err != ESP_OK)
    {
        printf("app_nvs_save_adc1: Error (%s) setting adc1 to NVS!\n", esp_err_to_name(esp_err));
        return esp_err;
    }

    // Saving ADC2
    esp_err = nvs_set_u8(handle, "adc2", ptr_byte[1]);
    if (esp_err != ESP_OK)
    {
        printf("app_nvs_save_adc2: Error (%s) setting adc2 to NVS!\n", esp_err_to_name(esp_err));
        return esp_err;
    }
    // Saving ADC3
    // esp_err = nvs_set_u8(handle, "adc3", ptr_byte[2]);
    // if (esp_err != ESP_OK)
    // {
    //     printf("app_nvs_save_adc3: Error (%s) setting adc3 to NVS!\n", esp_err_to_name(esp_err));
    //     return esp_err;
    // }

    // To commit ADC to NVS
    esp_err = nvs_commit(handle);
    if (esp_err != ESP_OK)
    {
        printf("app_nvs_save_adc: Error (%s) comitting adc to NVS!\n", esp_err_to_name(esp_err));
        return esp_err;
    }

    // To close NVS
    nvs_close(handle);
    ESP_LOGI(TAG, "app_nvs_save_ok: adc1:%d, adc2:%d, adc3:%d", ptr_byte[0], ptr_byte[1], ptr_byte[2]);
    return ESP_OK;
}

esp_err_t app_nvs_load_adc(uint8_t *const ptr_byte)
{
    nvs_handle handle;
    esp_err_t esp_err;

    ESP_LOGI(TAG, "app_nvs_load_adc");

    // Open NVS
    esp_err = nvs_open(app_nvs_adc, NVS_READONLY, &handle);

    if (esp_err != ESP_OK)
    {
        printf("app_nvs_load_adc: Error (%s) didnt get to NVS!\n", esp_err_to_name(esp_err));
        return esp_err;
    }

    // Get ADC1
    esp_err = nvs_get_u8(handle, "adc1", &ptr_byte[0]);
    if (esp_err != ESP_OK)
    {
        printf("app_nvs_save_adc1: Error (%s) setting adc1 to NVS!\n", esp_err_to_name(esp_err));
        return esp_err;
    }

    // Get ADC2
    esp_err = nvs_get_u8(handle, "adc2", &ptr_byte[1]);
    if (esp_err != ESP_OK)
    {
        printf("app_nvs_save_adc2: Error (%s) setting adc2 to NVS!\n", esp_err_to_name(esp_err));
        return esp_err;
    }

    // Get ADC3
    // esp_err = nvs_get_u8(handle, "adc3", &ptr_byte[2]);
    // if (esp_err != ESP_OK)
    // {
    //     printf("app_nvs_save_adc3: Error (%s) setting adc3 to NVS!\n", esp_err_to_name(esp_err));
    //     return esp_err;
    // }

    // Close NVS
    nvs_close(handle);
    return ESP_OK;
}

esp_err_t app_nvs_clear_adc(void)
{
    nvs_handle handle;
    esp_err_t esp_err;

    ESP_LOGI(TAG, "app_nvs_clear_adc: Clearing adc values from flash");

    // Open NVS
    esp_err = nvs_open(app_nvs_adc, NVS_READWRITE, &handle);
    if (esp_err != ESP_OK)
    {
        printf("app_nvs_clear_adc: Error (%s) opening NVS handle!\n", esp_err_to_name(esp_err));
        return esp_err;
    }

    // Erase ADC values on namespace
    esp_err = nvs_erase_all(handle);
    if (esp_err != ESP_OK)
    {
        printf("app_nvs_clear_adc: Error (%s) erasing adc values from flash!\n", esp_err_to_name(esp_err));
        return esp_err;
    }

    // Commit ADC values from NVS
    esp_err = nvs_commit(handle);
    if (esp_err != ESP_OK)
    {
        printf("app_nvs_clear_adc: Error (%s) NVS commit!\n", esp_err_to_name(esp_err));
        return esp_err;
    }

    // Close NVS
    nvs_close(handle);

    printf("app_nvs_clear_adc: returned ESP_OK\n");
    return ESP_OK;
}

esp_err_t app_nvs_init(void)
{
    // Init NVS
    esp_err_t err = nvs_flash_init();
    if (err == ESP_ERR_NVS_NO_FREE_PAGES || err == ESP_ERR_NVS_NEW_VERSION_FOUND)
    {
        ESP_ERROR_CHECK(nvs_flash_erase());
        err = nvs_flash_init();
    }
    ESP_ERROR_CHECK(err);
    return err;
}

esp_err_t app_nvs_save_signal(uint8_t *const ptr_signal)
{
    nvs_handle handle;
    esp_err_t esp_err;

    ESP_LOGI(TAG, "app_nvs_save_signal");

    // Open NVS
    esp_err = nvs_open(app_nvs_siganl, NVS_READWRITE, &handle);

    if (esp_err != ESP_OK)
    {
        ESP_ERROR_CHECK(nvs_flash_erase());
        return esp_err;
    }

    // Saving signal
    esp_err = nvs_set_u8(handle, "Signal", ptr_signal[0]);
    if (esp_err != ESP_OK)
    {
        printf("app_nvs_save_signal: Error (%s) setting signal to NVS!\n", esp_err_to_name(esp_err));
        return esp_err;
    }

    // To commit signal to NVS
    esp_err = nvs_commit(handle);
    if (esp_err != ESP_OK)
    {
        printf("app_nvs_save_signal: Error (%s) comitting signal to NVS!\n", esp_err_to_name(esp_err));
        return esp_err;
    }

    // To close NVS
    nvs_close(handle);
    ESP_LOGI(TAG, "app_nvs_save_ok: signal:%d", ptr_signal[0]);
    return ESP_OK;
}

esp_err_t app_nvs_load_signal(uint8_t *const ptr_signal)
{
    nvs_handle handle;
    esp_err_t esp_err;

    ESP_LOGI(TAG, "app_nvs_load_signal");

    // Open NVS
    esp_err = nvs_open(app_nvs_siganl, NVS_READONLY, &handle);

    if (esp_err != ESP_OK)
    {
        printf("app_nvs_load_signal: Error (%s) didnt get to NVS!\n", esp_err_to_name(esp_err));
        return esp_err;
    }

    // Get Signal
    esp_err = nvs_get_u8(handle, "Signal", &ptr_signal[0]);
    if (esp_err != ESP_OK)
    {
        printf("app_nvs_save_signal: Error (%s) setting signal to NVS!\n", esp_err_to_name(esp_err));
        return esp_err;
    }

    // Close NVS
    nvs_close(handle);
    return ESP_OK;
}