#ifndef __APP_ADC_DAC_H__
#define __APP_ADC_DAC_H__

#include <stdio.h>
#include <string.h>
#include "esp_log.h"
#include "esp_err.h"
#include "driver/adc.h"
#include "esp_adc_cal.h"
#include "driver/dac.h"


/*
Config 3 pines as 3 analog pines.
@param array whith 3 uint8_t pines.
@return ESP_OK if successful.Otherwhise has an error.
@note ADC_UNIT_1, ADC_ATTEN_DB_11, ADC_WIDTH_BIT_DEFAULT
*/
esp_err_t app_adc_init(uint8_t* const ptr_pines);

/*
Get the voltage for the 3 analog pines.
@param variable type uint32_t.
@return ESP_OK if successful.Otherwhise has an error. 
*/
esp_err_t app_adc_read_milli_voltage(uint32_t* const ptr_voltage);

/*
Calibrate adc channel 1.
@return ESP_OK if successful.Otherwhise has an error.
*/
esp_err_t app_adc_calib(void);

//############# Add DAC Header ############

/*
Initialize internal dac from esp32.
@return ESP_OK if successful.Otherwhise has an error.
*/
esp_err_t app_dac_init(void);


/*
Write any value form internal dac to esp32.
@param Get value from flash to varible type uint8_t ptr_byte[3].
@return ESP_OK if successful.Otherwhise has an error.
@note the function to set external adc value dosent exist .
*/
esp_err_t app_dac_write(uint8_t dac_value1, uint8_t dac_value2);

#endif // __APP_ADC_DAC_H__