/**
 * @file main.cc
 *
 * @brief test for OLED class
 *
 * @author monoliths (monoliths-uni@outlook.com)
 * @version 1.0
 * @date 2022-06-03
 *
 * *********************************************************************************
 *
 * @note version: 0.1
 *
 *
 * @description: none
 *
 * *********************************************************************************
 */
#include "esp_log.h"
#include "oled.h"

static const char* TAG = "oled test main";

void oled_test()
{
    auto i2c_oled = new oled::OLED(5, 6, true);

    esp_err_t err = i2c_oled->init();
    if (err == ESP_OK)
    {
        ESP_LOGI(TAG, "oled init succ");
        i2c_oled->clear();

        i2c_oled->show_string(20,
                              0,
                              "2022-03-06",
                              oled::OLED_FONT_SIZE::OLED_FONT_SIZE_16);
        i2c_oled->show_string(25,
                              5,
                              "MONOLITHS",
                              oled::OLED_FONT_SIZE::OLED_FONT_SIZE_16);
    }
    else
    {
        ESP_LOGE(TAG, "oled init err, err code: %d", err);
    }
}

#ifdef __cplusplus
extern "C"
{
#endif

    void app_main(void)
    {
        oled_test();
    }

#ifdef __cplusplus
}
#endif
