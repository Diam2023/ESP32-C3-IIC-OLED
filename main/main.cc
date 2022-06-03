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
#include <memory>

static const char* TAG = "oled test main";

void oled_test()
{
    auto i2c_oled = std::make_unique<oled::OLED>(5, 6, true);

    esp_err_t err = i2c_oled->init();
    if (err == ESP_OK)
    {
        uint8_t data[32] = {0x00, 0xC0, 0x80, 0x00, 0xC0, 0x30, 0x0C, 0x02,
                            0x04, 0x38, 0x60, 0x80, 0x00, 0x80, 0xC0, 0x00,
                            0x1E, 0x63, 0x80, 0x01, 0x00, 0x40, 0xB8, 0x04,
                            0x04, 0x88, 0x70, 0x00, 0x01, 0x80, 0x71, 0x0F};
        ESP_LOGI(TAG, "oled init succ");
        i2c_oled->clear();
        i2c_oled->show_string(20,
                              0,
                              "2022-06-03",
                              oled::OLED_FONT_SIZE::OLED_FONT_SIZE_16);
        i2c_oled->show_string(45,
                              3,
                              "DEMO",
                              oled::OLED_FONT_SIZE::OLED_FONT_SIZE_16);
        i2c_oled->show_string(23,
                              6,
                              "MONOLITHS",
                              oled::OLED_FONT_SIZE::OLED_FONT_SIZE_16);
        // i2c_oled->show_image(0, 0, data, 16, 32);
        i2c_oled->show_image(105, 3, 2, oled::OLED_IMAGE_SIZE::OLED_IMAGE_SIZE_32);
        i2c_oled->show_image(0, 0, 5, oled::OLED_IMAGE_SIZE::OLED_IMAGE_SIZE_32);

        i2c_oled->show_string(105, 7, "V0.2", oled::OLED_FONT_SIZE::OLED_FONT_SIZE_6);
        i2c_oled->show_image(97, 7, 5);
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
