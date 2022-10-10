#ifndef _APP_BUTTON_H_
#define _APP_BUTTON_H_
/*
Config pin as input.
@param Digital pin.
@return ESP_OK if successful.Otherwhise has an error.
@note pullup and pulldown are disable.
*/
esp_err_t app_button_init(const uint8_t pin_btn);

/*
Read pin configurated as input.
@return Status of pin.
*/
bool app_button_read(void);

#endif // _APP_BUTTON_H_