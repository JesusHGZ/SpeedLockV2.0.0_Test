#include <stdio.h>
#include "esp_system.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "app_nvs.h"
#include "app_adc_dac.h"
#include "app_button.h"
#include "app_led.h"

#define MAXIMO 2
#define MUESTRAS 12

bool btn_level = 0;
bool btn_level2 = 0;

void app_main(void)
{
    static esp_err_t main_err;

    static const uint8_t g_btn = GPIO_NUM_23, g_led = GPIO_NUM_32;
    static uint8_t g_adc_pines[MAXIMO] = {ADC1_CHANNEL_6, ADC1_CHANNEL_7}, g_dac_val[MAXIMO], bits_adc[MAXIMO], R_Signal[1];
    static uint32_t g_adc_val[MAXIMO], adc1_array[MUESTRAS], adc2_array[MUESTRAS];
    static int sum1 = 0, sum2 = 0, prom_ADC1, prom_ADC2;

    gpio_reset_pin(GPIO_NUM_14);
    gpio_reset_pin(GPIO_NUM_12);

    gpio_set_direction(GPIO_NUM_2, GPIO_MODE_OUTPUT);
    gpio_set_direction(GPIO_NUM_14, GPIO_MODE_OUTPUT);
    gpio_set_direction(GPIO_NUM_18, GPIO_MODE_INPUT);
    gpio_set_direction(GPIO_NUM_12, GPIO_MODE_OUTPUT);
    gpio_set_pull_mode(GPIO_NUM_18, GPIO_PULLDOWN_ONLY);
    gpio_set_pull_mode(GPIO_NUM_4, GPIO_PULLDOWN_ONLY);

    printf("Setup\n");

    main_err = app_nvs_init();
    if (main_err != ESP_OK)
    {
        /* Que acciones tomar si existe un problema?*/;
        // esp_restart();
    }

    main_err = app_button_init(g_btn);
    if (main_err != ESP_OK)
    {
        /* Que acciones tomar si existe un problema? */
    }

    main_err = app_led_init(g_led);
    if (main_err != ESP_OK)
    {
        /* Que acciones tomar si existe un problema?*/
    }

    main_err = app_adc_init(g_adc_pines);
    if (main_err != ESP_OK)
    {
        /* Que acciones tomar si existe un problema?*/
    }

    main_err = app_dac_init();
    if (main_err != ESP_OK)
    {
        /* Que acciones tomar si existe un problema?*/
    }

    main_err = app_nvs_load_signal(R_Signal);
    if (main_err != ESP_OK)
    {
        /* Que acciones tomar si existe un problema?*/
    }

    main_err = app_nvs_load_adc(g_dac_val);
    printf("%d\n", main_err);
    if (main_err != ESP_OK)
    {
        /* Que acciones tomar si existe un problema?*/
    }

    main_err = app_adc_calib();
    if (main_err != ESP_OK)
    {
        /* Que acciones tomar si existe un problema?*/
    }

    while (1)
    {

        btn_level = gpio_get_level(GPIO_NUM_4);
        printf("Button State: %i \n", btn_level);

        if (btn_level == 1)
        {
            vTaskDelay(2000 / portTICK_PERIOD_MS);
            gpio_set_level(GPIO_NUM_2, 1);
            sum1 = 0;
            sum2 = 0;
            prom_ADC1 = 0;
            prom_ADC2 = 0;

            main_err = app_adc_calib();
            if (main_err != ESP_OK)
            {
                /* Que acciones tomar si existe un problema?*/
            }

            main_err = app_adc_read_milli_voltage(g_adc_val);
            if (main_err != ESP_OK)
            {
                /* Que acciones tomar si existe un problema?*/
            }

            if (g_adc_val[0] && g_adc_val[1] < 180)
            {
                gpio_set_level(GPIO_NUM_12, 1);
            }
            else if (g_adc_val[0] && g_adc_val[1] > 180)
            {
                gpio_set_level(GPIO_NUM_12, 0);
            }

            g_adc_val[0] = 0;
            g_adc_val[1] = 0;

            for (int i = 0; i < 12; i++)
            {
                main_err = app_adc_read_milli_voltage(g_adc_val);
                if (main_err != ESP_OK)
                {
                    /* Que acciones tomar si existe un problema?*/
                }
                adc1_array[i] = g_adc_val[0];
                adc2_array[i] = g_adc_val[1];
                sum1 += adc1_array[i];
                sum2 += adc2_array[i];

                printf("ADC1: %i \t ADC2: %i \n", adc1_array[i], adc2_array[i]);
                vTaskDelay(500 / portTICK_PERIOD_MS);
            }
            prom_ADC1 = sum1 / MUESTRAS;
            prom_ADC2 = sum2 / MUESTRAS;
            gpio_set_level(GPIO_NUM_2, 0);
            gpio_set_level(GPIO_NUM_12, 0);

            printf("\n P_ADC1: %i \t P_ADC2: %i \n", prom_ADC1, prom_ADC2);

            bits_adc[0] = (prom_ADC1 * 256) / 3100;
            bits_adc[1] = (prom_ADC2 * 256) / 3100;

            if (g_adc_val[0] && g_adc_val[1] < 1200) // El rango de error es mayor entre 0 y 2.5 V, por eso la compensación es mayor.
            {
                // Compensación negativa para mejorar resoución:
                g_dac_val[0] = bits_adc[0] - 3;
                g_dac_val[1] = bits_adc[1] - 3;
            }

            else if (g_adc_val[0] && g_adc_val[1] > 1200)
            {
                // Compensación negativa para mejorar resoución:
                g_dac_val[0] = bits_adc[0] - 4;
                g_dac_val[1] = bits_adc[1] - 7;
            }

            btn_level2 = gpio_get_level(GPIO_NUM_18);
            if (btn_level2 == 1)
            {
                R_Signal[0] = 0;
                main_err = app_nvs_save_signal(R_Signal);
                if (main_err != ESP_OK)
                {
                    printf("Valor: nulo");
                    /* Que acciones tomar si existe un problema?*/
                }
            }
            else
            {
                R_Signal[0] = 1;
                main_err = app_nvs_save_signal(R_Signal);
                if (main_err != ESP_OK)
                {
                    printf("Valor: nulo");
                    /* Que acciones tomar si existe un problema?*/
                }
            }

            printf("Valor: %d\n", R_Signal[0]);

            if (((bits_adc[0] - 4) < 70 && (bits_adc[0] - 8) < 66) && R_Signal[0] == 1)
            {

                main_err = app_nvs_save_adc(g_dac_val);
                if (main_err != ESP_OK)
                {
                    /* Que acciones tomar si existe un problema?*/
                }

                main_err = app_dac_write(g_dac_val[0], g_dac_val[1]);
                if (main_err != ESP_OK)
                {
                    /* Que acciones tomar si existe un problema?*/
                }
            }

            else if (((bits_adc[0] - 4) > 0 && (bits_adc[0] - 8) > 0) && R_Signal[0] == 0)
            {
                main_err = app_nvs_save_adc(g_dac_val);
                if (main_err != ESP_OK)
                {
                    /* Que acciones tomar si existe un problema?*/
                }

                main_err = app_dac_write(g_dac_val[0], g_dac_val[1]);
                if (main_err != ESP_OK)
                {
                    /* Que acciones tomar si existe un problema?*/
                }
            }
        }
        else
        {
            switch (R_Signal[0])
            {
            // declarations
            // . . .
            case 1:
                // statements executed if the expression equals the
                // value of this constant_expression
                gpio_set_level(GPIO_NUM_14, 0);
                break;
            default:
                // statements executed if expression does not equal
                // any case constant_expression
                gpio_set_level(GPIO_NUM_14, 1);
            }
            
            main_err = app_dac_write(g_dac_val[0], g_dac_val[1]);
            if (main_err != ESP_OK)
            {
                /* Que acciones tomar si existe un problema?*/
            }
        }

        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}