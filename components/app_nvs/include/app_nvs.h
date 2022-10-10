#ifndef _APP_NVS_H_
#define _APP_NVS_H_

/*
Save adc values from int8_t ptr_byte[3] into flash memory.
@param varible type uint8_t.
@return ESP_OK if successful.Otherwhise has an error.
@note Use adc_idle space.
*/
esp_err_t app_nvs_save_adc(uint8_t* const ptr_byte);
esp_err_t app_nvs_save_signal(uint8_t *const ptr_signal);

/*
Load adc values from flash to varible.
@param Get value from flash to varible type uint8_t ptr_byte[3].
@return ESP_OK if successful.Otherwhise has an error.
@note Use adc_idle space.
*/
esp_err_t app_nvs_load_adc(uint8_t *const ptr_byte);
esp_err_t app_nvs_load_signal(uint8_t *const ptr_byte);


/*
Initialize space adc_idle for starage adc values in flash memory.
@return ESP_OK if successful.Otherwhise has an error.
@note Use adc_idle space.
*/
esp_err_t app_nvs_init(void);

/*
Clear adc_idle space in flash memory.
@return ESP_OK if successful.Otherwhise has an error.
*/
esp_err_t app_nvs_clear_adc(void);



#endif // _APP_NVS1_H_