#include "oled_device.h"

#include <cstring>


static const char *TAG = "OledDevice";

oled::OledDevice::OledDevice(int scl_pin,
                             int sda_pin,
                             bool inner_pull,
                             const uint8_t oled_addr,
                             const DeviceInfo *device_info)
{
    this->device_info = device_info;
    this->config.mode = I2C_MODE_MASTER;
    this->config.sda_io_num = sda_pin;
    this->config.scl_io_num = scl_pin;
    if (inner_pull)
    {
        this->config.sda_pullup_en = GPIO_PULLUP_ENABLE;
        this->config.scl_pullup_en = GPIO_PULLUP_ENABLE;
    }
    else
    {
        this->config.sda_pullup_en = GPIO_PULLUP_DISABLE;
        this->config.scl_pullup_en = GPIO_PULLUP_DISABLE;
    }
    this->config.clk_flags = I2C_SCLK_SRC_FLAG_FOR_NOMAL;

    this->config.master.clk_speed = this->iic_freq;
    this->i2c_port = I2C_NUM_0;
    this->oled_addr = oled_addr;

}

esp_err_t oled::OledDevice::init(bool forward, bool inverse)
{
    // ESP_ERROR_CHECK(this->data_mapping == NULL);

    if (i2c_param_config(this->i2c_port, &this->config) != ESP_OK)
    {
        ESP_LOGE(TAG, "config err");
        return 1;
    }
    if (i2c_driver_install(this->i2c_port, this->config.mode, 0, 0, 0) !=
        ESP_OK)
    {
        ESP_LOGE(TAG, "install err");
        return 2;
    }

    uint8_t cmd[56];

    memmove(cmd, this->device_info->init_cmd, sizeof(cmd));

    if (!forward)
    {
        cmd[13] = 0xA0;
        cmd[15] = 0xC0;
    }

    if (inverse)
    {
        cmd[53] = 0xA7;
    }

    if (i2c_master_write_slave(cmd, this->device_info->init_size) != ESP_OK)
    {
        ESP_LOGE(TAG, "write err");
        return 3;
    }
    return ESP_OK;
}

esp_err_t oled::OledDevice::init(const uint8_t *cmd, const uint8_t sizeof_cmd)
{
    if (i2c_param_config(this->i2c_port, &this->config) != ESP_OK)
    {
        ESP_LOGE(TAG, "config err");
        return 1;
    }
    if (i2c_driver_install(this->i2c_port, this->config.mode, 0, 0, 0) !=
        ESP_OK)
    {
        ESP_LOGE(TAG, "install err");
        return 2;
    }

    if (i2c_master_write_slave(cmd, sizeof_cmd) != ESP_OK)
    {
        ESP_LOGE(TAG, "write err");
        return 3;
    }
    return ESP_OK;
}

// esp_err_t oled::OledDevice::clear()
// {
//     return this->full(0x00);
// }

// esp_err_t oled::OledDevice::full(const uint8_t data)
// {
//     this->data_mapping->setData(data);
//     return flash();
// }

// esp_err_t oled::OledDevice::full_page(const uint8_t page, const uint8_t data)
// {
//     this->data_mapping->setPageData(page, data);
//     return flash_page(page);
// }

esp_err_t oled::OledDevice::flash(DataMap *data_mapping)
{
    esp_err_t err = ESP_OK;
    for (size_t i = 0; i < this->device_info->max_page; i++)
    {
        err = flash_page(data_mapping, i);
    }
    return err;
}

esp_err_t oled::OledDevice::flash_page(DataMap *data_mapping,
                                       const uint8_t page)
{
    data_mapping->setData(page, 0, 0x40);
    this->oled_set_start_address(page, 0);


    return this->i2c_master_write_slave(data_mapping->getDataMapping()[page],
                                        this->device_info->max_line_seg);
}

// esp_err_t oled::OledDevice::show_string(uint8_t x,
//                                         uint8_t y,
//                                         const std::string &&string,
//                                         const OLED_FONT_SIZE font_size)
// {
//     uint8_t c = 0, j = 0;
//     if (font_size == OLED_FONT_SIZE::OLED_FONT_SIZE_16)
//     {
//         while (string[j] != '\0')
//         {
//             c = string[j] - 32;
//             if (x > 120)
//             {
//                 x = 0;
//                 y += 2;
//             }

//             memmove(this->data_mapping->getDataMapping()[y] + x + 1,
//                     font::F8X16 + c * 16,
//                     8);
//             memmove(this->data_mapping->getDataMapping()[y + 1] + x + 1,
//                     font::F8X16 + c * 16 + 8,
//                     8);

//             // std::copy(std::begin(font::F8X16) + c * 16,
//             //           std::begin(font::F8X16) + c * 16 + 8,
//             //           std::begin(this->data_mapping->getDataMapping()[y]) + x
//             //           + 1);
//             // std::copy(std::begin(font::F8X16) + c * 16 + 8,
//             //           std::begin(font::F8X16) + c * 16 + 16,
//             //           std::begin(data_mapping[y + 1]) + x + 1);
//             x += 8;
//             j++;
//         }
//     }
//     else
//     {
//         while (string[j] != '\0')
//         {
//             c = string[j] - 32;
//             if (x > 126)
//             {
//                 x = 0;
//                 y++;
//             }
//             memmove(this->data_mapping->getDataMapping()[y] + x + 1,
//                     font::F6x8[c] + 1,
//                     5);
//             // std::copy(std::begin(font::F6x8[c]) + 1,
//             //           std::begin(font::F6x8[c]) + 6,
//             //           std::begin(data_mapping[y]) + x + 1);
//             x += 6;
//             j++;
//         }
//     }
//     return ((font_size == OLED_FONT_SIZE::OLED_FONT_SIZE_16)
//                 ? (flash_page(y) & flash_page(y + 1))
//                 : flash_page(y));
// }

// esp_err_t oled::OledDevice::show_image(uint8_t x,
//                                        uint8_t y,
//                                        const uint8_t *begin,
//                                        const uint8_t split_size,
//                                        const uint8_t length)
// {
//     esp_err_t err = ESP_OK;

//     for (size_t line = 0; line < (length / split_size); line++)
//     {
//         memmove(this->data_mapping->getDataMapping()[y + line] + x + 1,
//                 begin + (line * split_size),
//                 split_size);
//         // std::copy(begin + (line * split_size),
//         //           begin + ((line + 1) * split_size),
//         //           std::begin(data_mapping[y + line]) + x + 1);

//         err = flash_page(line);
//     }
//     return err;
// }

// esp_err_t oled::OledDevice::show_image(uint8_t x,
//                                        uint8_t y,
//                                        const uint8_t index,
//                                        const OLED_IMAGE_SIZE image_size)
// {
//     if (image_size == OLED_IMAGE_SIZE::OLED_IMAGE_SIZE_32)
//     {
//         memmove(this->data_mapping->getDataMapping()[y] + x + 1,
//                 font::H_Imag[index * 2],
//                 16);

//         memmove(this->data_mapping->getDataMapping()[y + 1] + x + 1,
//                 font::H_Imag[index * 2 + 1],
//                 16);
//         // std::copy(std::begin(font::H_Imag[index * 2]),
//         //           std::begin(font::H_Imag[index * 2]) + 16,
//         //           std::begin(data_mapping[y]) + x + 1);

//         // std::copy(std::begin(font::H_Imag[index * 2 + 1]),
//         //           std::begin(font::H_Imag[index * 2 + 1]) + 16,
//         //           std::begin(data_mapping[y + 1]) + x + 1);
//     }
//     else if (image_size == OLED_IMAGE_SIZE::OLED_IMAGE_SIZE_8)
//     {
//         memmove(this->data_mapping->getDataMapping()[y] + x + 1,
//                 font::H_Imag_8[index],
//                 8);
//         // std::copy(std::begin(font::H_Imag_8[index]),
//         //           std::begin(font::H_Imag_8[index]) + 8,
//         //           std::begin(data_mapping[y]) + x + 1);
//     }
//     else if (image_size == OLED_IMAGE_SIZE::OLED_IMAGE_SIZE_4)
//     {
//         memmove(this->data_mapping->getDataMapping()[y] + x + 1,
//                 font::H_Imag_4[index],
//                 4);
//         // std::copy(std::begin(font::H_Imag_4[index]),
//         //           std::begin(font::H_Imag_4[index]) + 4,
//         //           std::begin(data_mapping[y]) + x + 1);
//     }

//     return ((image_size == OLED_IMAGE_SIZE::OLED_IMAGE_SIZE_32)
//                 ? (flash_page(y) & flash_page(y + 1))
//                 : flash_page(y));
// }

oled::OledDevice::~OledDevice()
{
    // delete[] data_mapping;
}