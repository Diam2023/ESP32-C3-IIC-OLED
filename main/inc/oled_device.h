/**
 * @file oled_device.h
 *
 * @brief  OledDevice Class
 *
 * @author monoliths (monoliths-uni@outlook.com)
 * @version 0.3
 * @date 2022-06-03
 *
 * *********************************************************************************
 *
 * @note version: 0.1
 *
 * @description: added base font operation
 *
 *
 * @note version: 0.2
 *
 * @description: added image operation
 *
 *
 * @note version: 0.3
 *
 * @description: customize initialize screen
 *
 * *********************************************************************************
 */

#pragma once

#include "driver/i2c.h"
#include <string>
#include "esp_log.h"
#include "oled_font.h"
#include "types.h"
#include "data_map.h"

namespace oled
{

constexpr DeviceInfo DefautlDeviceInfo{
    .max_page = 8,
    .max_line_seg = 129,
    .init_size = 56,
    .init_cmd = {
        0x80,
        0xAE,    //--turn off oled panel
        0x80,
        0x00,    //---set low column address
        0x80,
        0x10,    //---set high column address
        0x80,
        0x40,    //--set start line address  Set Mapping RAM Display
                 // Start Line
        0x80,
        0x81,    //--set contrast control register
        0x80,
        0xCF,    // Set SEG Output Current Brightness
        0x80,
        0xA1,    //--Set SEG/Column Mapping
        0x80,
        0xC8,    // Set COM/Row Scan Direction
        0x80,
        0xA6,    //--set normal display
        0x80,
        0xA8,    //--set multiplex ratio(1 to 64)
        0x80,
        0x3F,    //--1/64 duty
        0x80,
        0xD3,    //-set display offset	Shift Mapping RAM Counter
                 //(0x00~0x3F)
        0x80,
        0x00,    //-not offset
        0x80,
        0xD5,    //--set display clock divide ratio/oscillator frequency
        0x80,
        0x80,    //--set divide ratio, Set Clock as 100 Frames/Sec
        0x80,
        0xD9,    //--set pre-charge period
        0x80,
        0xF1,    // Set Pre-Charge as 15 Clocks & Discharge as 1 Clock
        0x80,
        0xDA,    //--set com pins hardware configuration
        0x80,
        0x12,    //
        0x80,
        0xDB,    //--set vcomh
        0x80,
        0x40,    // Set VCOM Deselect Level
        0x80,
        0x20,    //-Set Page Addressing Mode (0x00/0x01/0x02)
        0x80,
        0x02,    //
        0x80,
        0x8D,    //--set Charge Pump enable/disable
        0x80,
        0x14,    //--set(0x10) disable
        0x80,
        0xA4,    // Disable Entire Display On (0xa4/0xa5)
        0x80,
        0xA6,    // Disable Inverse Display On (0xa6/a7)
        0x00,
        0xAF    //
    }};

constexpr auto getDefaultDeviceInfo()
{
    return &DefautlDeviceInfo;
};

/**
 * @brief  operation i2c oled.
 */
class OledDevice
{
private:
    /**
     * @brief  i2c configuration.
     */
    i2c_config_t m_config{};

    /**
     * @brief oled communication i2c port number.
     */
    i2c_port_t m_I2C_Port;

    /**
     * @brief oled device address.
     */
    uint8_t m_oledAddr;

    static const uint8_t sc_I2C_ASK_CHECK_ENABLE = 0x01;
    static const uint32_t sc_I2C_FREQUENCY = 400000;

    /**
     * @brief  send data for oled.
     * @param  data_wr: datas
     * @param  size: sizeof data_wr
     * @return esp_err_t: error if occurred, return code type esp_err_t, else
     * ESP_OK.
     */
    inline esp_err_t i2c_master_write_slave(const uint8_t *data_wr,
                                            const size_t size)
    {
        i2c_cmd_handle_t cmd = i2c_cmd_link_create();
        i2c_master_start(cmd);
        i2c_master_write_byte(cmd,
                              (this->m_oledAddr << 1),
                              sc_I2C_ASK_CHECK_ENABLE);
        i2c_master_write(cmd, data_wr, size, sc_I2C_ASK_CHECK_ENABLE);
        i2c_master_stop(cmd);
        esp_err_t ret = i2c_master_cmd_begin(this->m_I2C_Port,
                                             cmd,
                                             1000 / portTICK_PERIOD_MS);
        i2c_cmd_link_delete(cmd);
        return ret;
    }

    /**
     * @brief  set start address
     * @param  page_addr: page address
     * @param  ram_addr: ram_addr
     * @return esp_err_t: error type
     */
    inline esp_err_t oled_set_start_address(const uint8_t page_addr,
                                            const uint16_t ram_addr)
    {
        esp_err_t esp_err;
        uint8_t set_addr_cmd[6] = {
            0x80,
            0xb0,    // Set Page Start Address
            0x80,
            0x00,    // Set Lower Column Start Address
            0x00,
            0x10    // Set Higher Column Start Address
        };
        set_addr_cmd[1] = 0xb0 | page_addr;
        set_addr_cmd[3] = 0x00 | (ram_addr & 0x00ff);
        set_addr_cmd[5] = 0x10 | (ram_addr >> 8);
        esp_err = i2c_master_write_slave(set_addr_cmd, 6);
        return esp_err;
    }

public:
    const DeviceInfo *cm_pDeviceInfo;

    /**
     * @brief  Construct a new OledDevice object.
     * @param  int: oled iic scl pin.
     * @param  int: oled iic sda pin.
     * @param  innerPull: mcu sda、scl inner pull up.
     * @param  oledAddress: oled iic address.
     */
    OledDevice(int scl_pin,
               int sda_pin,
               bool innerPull = false,
               uint8_t oledAddress = 0x3c,
               const DeviceInfo *device_info = getDefaultDeviceInfo());

    /**
     * @brief  Move Construct.
     * @param  oled: rvalue.
     */
    OledDevice(OledDevice &&oled,
               const DeviceInfo *deviceInfo = getDefaultDeviceInfo()) noexcept
        : m_config(oled.m_config),
          m_I2C_Port(oled.m_I2C_Port),
          m_oledAddr(oled.m_oledAddr),
          cm_pDeviceInfo(deviceInfo){};

    /**
     * @brief  init driver and install it.
     * @param  forward: forward display, It means signal line on top of screen.
     * @param  inverse: if inverse on, It will inverse display color.
     * @return esp_err_t: error code.
     *
     * @note forward and inverse option added in version 0.3
     */
    esp_err_t init(bool forward = true, bool inverse = false);

    /**
     * @brief  customize initialize use cmd.
     * @param  cmd: customize data.
     * @param  sizeofCmd: customize data size.
     * @return esp_err_t: error code.
     *
     * @since 0.3
     */
    esp_err_t init(const uint8_t *cmd, uint8_t sizeofCmd);

    // /**
    //  * @brief  set screen to 0x00
    //  * @return esp_err_t: erorr code.
    //  */
    // esp_err_t clear();

    // /**
    //  * @brief  full screen of data.
    //  * @param  data:
    //  * @return esp_err_t:
    //  */
    // esp_err_t full( const uint8_t data);

    // /**
    //  * @brief  use data to full page.
    //  * @param  page: page of oled.
    //  * @param  data: data for oled page.
    //  * @return esp_err_t: error code.
    //  */
    // esp_err_t full_page(const uint8_t page, const uint8_t data);

    /**
     * @brief  flash screen for page use data_mapping.
     * @param  page: page of oled.
     * @return esp_err_t: error code.
     */
    esp_err_t flashPage(DataMap *, uint8_t page);

    /**
     * @brief  flash data for oled use data_mapping.
     * @return esp_err_t: error code.
     */
    esp_err_t flash(DataMap *);

    // /**
    //  * @brief  show string data on x,y.
    //  * @param  x: seg
    //  * @param  y: page line
    //  * @param  string: string data
    //  * @param  font_size: font_size
    //  * @return esp_err_t: error code.
    //  */
    // esp_err_t show_string(
    //     const uint8_t x,
    //     const uint8_t y,
    //     const std::string &&string,
    //     const OLED_FONT_SIZE font_size = OLED_FONT_SIZE::OLED_FONT_SIZE_16);

    // /**
    //  * @brief  show image use begin data
    //  * @param  x: seg.
    //  * @param  y: page line.
    //  * @param  begin: begin data.
    //  * @param  split_size: data on one page.
    //  * @param  length: if (length / split_size) > 1 it will show (begin +
    //  * split_size * around) on (around + page).
    //  * @return esp_err_t: error code.
    //  */
    // esp_err_t show_image(const uint8_t x,
    //                      const uint8_t y,
    //                      const uint8_t *begin,
    //                      const uint8_t split_size = 16,
    //                      const uint8_t length = 32);

    // /**
    //  * @brief  show H_Imag index image on x, y
    //  * @param  x: seg
    //  * @param  y: page line.
    //  * @param  index: index of H_Image.
    //  * @param  image_size: size of image
    //  * @return esp_err_t: error code.
    //  */
    // esp_err_t show_image(
    //     const uint8_t x,
    //     const uint8_t y,
    //     const uint8_t index,
    //     const OLED_IMAGE_SIZE image_size =
    //     OLED_IMAGE_SIZE::OLED_IMAGE_SIZE_8);

    /**
     * @brief  Destroy the OledDevice object.
     */
    ~OledDevice();
};

}    // namespace oled
