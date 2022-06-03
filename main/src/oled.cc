#include "oled.h"

oled::OLED::OLED(int scl_pin,
                 int sda_pin,
                 bool inner_pull,
                 const uint8_t oled_addr)
{
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
    this->config.master.clk_speed = oled::OLED::OLED_I2C_FREQ;
    this->i2c_port = I2C_NUM_0;
    this->oled_addr = oled_addr;

    this->data_mapping = new uint8_t[MAX_PAGE][MAX_LINE_SEG];

    for (size_t i = 0; i < MAX_PAGE; i++)
    {
        for (size_t j = 0; j < MAX_LINE_SEG; j++)
        {
            if (j == 0)
            {
                this->data_mapping[i][0] = 0x40;
            }
            else
            {
                this->data_mapping[i][j] = 0x00;
            }
        }
    }
}

esp_err_t oled::OLED::init()
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

    if (i2c_master_write_slave(OLED_INIT_CMD, OLED_INIT_CMD_SIZE) != ESP_OK)
    {
        ESP_LOGE(TAG, "write err");
        return 3;
    }
    return ESP_OK;
}

esp_err_t oled::OLED::clear()
{
    return this->full(0x00);
}

esp_err_t oled::OLED::full(const uint8_t data)
{
    for (size_t i = 0; i < MAX_PAGE; i++)
    {
        for (size_t j = 1; j < MAX_LINE_SEG; j++)
        {
            this->data_mapping[i][j] = data;
        }
    }

    return flash();
}

esp_err_t oled::OLED::full_page(const uint8_t page, const uint8_t data)
{
    for (size_t i = 1; i < MAX_LINE_SEG; i++)
    {
        this->data_mapping[page][i] = data;
    }
    return flash_page(page);
}

esp_err_t oled::OLED::flash()
{
    esp_err_t err = ESP_OK;
    for (size_t i = 0; i < MAX_PAGE; i++)
    {
        err = flash_page(i);
    }
    return err;
}
esp_err_t oled::OLED::flash_page(const uint8_t page)
{
    data_mapping[page][0] = 0x40;
    this->oled_set_start_address(page, 0);
    return this->i2c_master_write_slave(&data_mapping[page][0], MAX_LINE_SEG);
}

esp_err_t oled::OLED::show_string(uint8_t x,
                                  uint8_t y,
                                  const std::string &&string,
                                  const OLED_FONT_SIZE font_size)
{
    uint8_t c = 0, j = 0;
    if (font_size == OLED_FONT_SIZE::OLED_FONT_SIZE_16)
    {
        while (string[j] != '\0')
        {
            c = string[j] - 32;
            if (x > 120)
            {
                x = 0;
                y += 2;
            }
            std::copy(std::begin(font::F8X16) + c * 16,
                      std::begin(font::F8X16) + c * 16 + 8,
                      std::begin(data_mapping[y]) + x + 1);
            std::copy(std::begin(font::F8X16) + c * 16 + 8,
                      std::begin(font::F8X16) + c * 16 + 16,
                      std::begin(data_mapping[y + 1]) + x + 1);
            x += 8;
            j++;
        }
    }
    else
    {
        while (string[j] != '\0')
        {
            c = string[j] - 32;
            if (x > 126)
            {
                x = 0;
                y++;
            }
            std::copy(std::begin(font::F6x8[c]) + 1,
                      std::begin(font::F6x8[c]) + 6,
                      std::begin(data_mapping[y]) + x + 1);
            x += 6;
            j++;
        }
    }
    return ((font_size == OLED_FONT_SIZE::OLED_FONT_SIZE_16)
                ? (flash_page(y) & flash_page(y + 1))
                : flash_page(y));
}

esp_err_t oled::OLED::show_image(uint8_t x,
                                 uint8_t y,
                                 const uint8_t *begin,
                                 const uint8_t split_size,
                                 const uint8_t length)
{
    esp_err_t err = ESP_OK;

    for (size_t line = 0; line < (length / split_size); line++)
    {
        std::copy(begin + (line * split_size),
                  begin + ((line + 1) * split_size),
                  std::begin(data_mapping[y + line]) + x + 1);

        err = flash_page(line);
    }
    return err;
}

esp_err_t oled::OLED::show_image(uint8_t x,
                                 uint8_t y,
                                 const uint8_t index,
                                 const OLED_IMAGE_SIZE image_size)
{
    if (image_size == OLED_IMAGE_SIZE::OLED_IMAGE_SIZE_32)
    {
        std::copy(std::begin(font::H_Imag[index * 2]),
                  std::begin(font::H_Imag[index * 2]) + 16,
                  std::begin(data_mapping[y]) + x + 1);
        std::copy(std::begin(font::H_Imag[index * 2 + 1]),
                  std::begin(font::H_Imag[index * 2 + 1]) + 16,
                  std::begin(data_mapping[y + 1]) + x + 1);
    }
    else if (image_size == OLED_IMAGE_SIZE::OLED_IMAGE_SIZE_8)
    {
        std::copy(std::begin(font::H_Imag_8[index]),
                  std::begin(font::H_Imag_8[index]) + 8,
                  std::begin(data_mapping[y]) + x + 1);
    }
    else if (image_size == OLED_IMAGE_SIZE::OLED_IMAGE_SIZE_4)
    {
        std::copy(std::begin(font::H_Imag_4[index]),
                  std::begin(font::H_Imag_4[index]) + 4,
                  std::begin(data_mapping[y]) + x + 1);
    }

    return ((image_size == OLED_IMAGE_SIZE::OLED_IMAGE_SIZE_32)
                ? (flash_page(y) & flash_page(y + 1))
                : flash_page(y));
}

oled::OLED::~OLED()
{
    delete[] data_mapping;
}