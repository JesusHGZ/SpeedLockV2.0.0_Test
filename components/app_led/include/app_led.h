#ifndef _APP_LED_H_
#define _APP_LED_H_

/*
Config pin as output.
@param Digital pin.
@return ESP_OK if successful.Otherwhise has an error.
*/
esp_err_t app_led_init(uint8_t pin_led);

/*
Set high digital pin.
@param Digital pin.
@return ESP_OK if successful.Otherwhise has an error.
*/
esp_err_t app_led_enable(void);

/*
Set low digital pin.
@param Digital pin.
@return ESP_OK if successful.Otherwhise has an error.
*/
esp_err_t app_led_disable(void);

/*
Set toggle led.
@param Digital pin.
@return ESP_OK if successful.Otherwhise has an error.
*/
esp_err_t app_led_toggle(const uint32_t delay_ms_led);

#endif // _APP_LED_H_