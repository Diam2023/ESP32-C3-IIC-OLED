#pragma once

#include "data_map.h"
#include "types.h"

#include <string>

namespace oled
{

class Paint
{
private:
    // /**
    //  * @brief target map
    //  */
    // DataMap* data_mapping;

    // /**
    //  * @brief poiniter position
    //  */
    // Point pointer;

public:
    // inline void setDataMap(DataMap* target_data_map)
    // {
    //     data_mapping = target_data_map;
    // }

    // inline DataMap* dataMap()
    // {
    //     return data_mapping;
    // }

    // inline Point& nowPosition()
    // {
    //     return pointer;
    // }

    /**
     * @brief  full screen of data.
     * @param  data:
     */
    void full(DataMap*, const uint8_t data);

    /**
     * @brief  use data to full page.
     * @param  page: page of oled.
     * @param  data: data for oled page.
     */
    void full_page(DataMap*, const uint8_t page, const uint8_t data);

    /**
     * @brief  set screen to 0x00
     */
    void clear(DataMap*);

    // /**
    //  * @brief move pointer to position
    //  * @param position:
    //  */
    // void moveTo(const Point& position);

    // /**
    //  * @brief draw line from pointer to position.
    //  * @param position:
    //  */
    // void lineTo(const Point& position);

    // /**
    //  * @brief wait to next version.
    //  * @param r:
    //  * @param angle:
    //  */
    // void arcTo(const uint8_t r, const double angle);

    /**
     * @brief  show string data on x,y.
     * @param  x: seg
     * @param  y: page line
     * @param  string: string data
     * @param  font_size: font_size
     */
    void writeString(
        DataMap*,
        const uint8_t x,
        const uint8_t y,
        const std::string&& string,
        const OLED_FONT_SIZE font_size = OLED_FONT_SIZE::OLED_FONT_SIZE_16);

    /**
     * @brief  show image use begin data
     * @param  x: seg.
     * @param  y: page line.
     * @param  begin: begin data.
     * @param  split_size: data on one page.
     * @param  length: if (length / split_size) > 1 it will show (begin +
     * split_size * around) on (around + page).
     */
    void writeImage(DataMap*,
                    const uint8_t x,
                    const uint8_t y,
                    const uint8_t* begin,
                    const uint8_t split_size = 16,
                    const uint8_t length = 32);

    /**
     * @brief  show H_Imag index image on x, y
     * @param  x: seg
     * @param  y: page line.
     * @param  index: index of H_Image.
     * @param  image_size: size of image
     */
    void writeImage(
        DataMap*,
        const uint8_t x,
        const uint8_t y,
        const uint8_t index,
        const OLED_IMAGE_SIZE image_size = OLED_IMAGE_SIZE::OLED_IMAGE_SIZE_8);

    Paint();
    ~Paint();
};


static Paint paint;

}    // namespace oled
