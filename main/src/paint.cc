#include "paint.h"

#include <cstring>
#include "oled_font.h"

void oled::Paint::full(DataMap* data_mapping, const uint8_t data)
{
    // data_mapping->setData(data);
    for (size_t i = 0; i < data_mapping->getPage(); i++)
    {
        this->full_page(data_mapping, i, data);
        // data_mapping->setData(data);

        /* code */
    }
}

void oled::Paint::full_page(DataMap* data_mapping,
                            const uint8_t page,
                            const uint8_t data)
{
    data_mapping->setPageData(page, data);
    data_mapping->setData(page, 0, 0x40);
}

void oled::Paint::clear(DataMap* data_mapping)
{
    this->full(data_mapping, 0x00);
}

void oled::Paint::writeString(DataMap* data_mapping,
                              uint8_t x,
                              uint8_t y,
                              const std::string&& string,
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

            memmove(data_mapping->getDataMapping()[y] + x + 1,
                    oled::font::F8X16 + c * 16,
                    8);
            memmove(data_mapping->getDataMapping()[y + 1] + x + 1,
                    oled::font::F8X16 + c * 16 + 8,
                    8);
            // std::copy(std::begin(font::F8X16) + c * 16,
            //           std::begin(font::F8X16) + c * 16 + 8,
            //           std::begin(data_mapping->getDataMapping()[y]) + x
            //           + 1);
            // std::copy(std::begin(font::F8X16) + c * 16 + 8,
            //           std::begin(font::F8X16) + c * 16 + 16,
            //           std::begin(data_mapping[y + 1]) + x + 1);
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
            memmove(data_mapping->getDataMapping()[y] + x + 1,
                    font::F6x8[c] + 1,
                    5);
            // std::copy(std::begin(font::F6x8[c]) + 1,
            //           std::begin(font::F6x8[c]) + 6,
            //           std::begin(data_mapping[y]) + x + 1);
            x += 6;
            j++;
        }
    }
}

void oled::Paint::writeImage(DataMap* data_mapping,
                             uint8_t x,
                             uint8_t y,
                             const uint8_t* begin,
                             const uint8_t split_size,
                             const uint8_t length)
{
    for (size_t line = 0; line < (length / split_size); line++)
    {
        memmove(data_mapping->getDataMapping()[y + line] + x + 1,
                begin + (line * split_size),
                split_size);
        // std::copy(begin + (line * split_size),
        //           begin + ((line + 1) * split_size),
        //           std::begin(data_mapping[y + line]) + x + 1);
    }
}

void oled::Paint::writeImage(DataMap* data_mapping,
                             uint8_t x,
                             uint8_t y,
                             const uint8_t index,
                             const OLED_IMAGE_SIZE image_size)
{
    if (image_size == OLED_IMAGE_SIZE::OLED_IMAGE_SIZE_32)
    {
        memmove(data_mapping->getDataMapping()[y] + x + 1,
                font::H_Imag[index * 2],
                16);

        memmove(data_mapping->getDataMapping()[y + 1] + x + 1,
                font::H_Imag[index * 2 + 1],
                16);
        // std::copy(std::begin(font::H_Imag[index * 2]),
        //           std::begin(font::H_Imag[index * 2]) + 16,
        //           std::begin(data_mapping[y]) + x + 1);

        // std::copy(std::begin(font::H_Imag[index * 2 + 1]),
        //           std::begin(font::H_Imag[index * 2 + 1]) + 16,
        //           std::begin(data_mapping[y + 1]) + x + 1);
    }
    else if (image_size == OLED_IMAGE_SIZE::OLED_IMAGE_SIZE_8)
    {
        memmove(data_mapping->getDataMapping()[y] + x + 1,
                font::H_Imag_8[index],
                8);
        // std::copy(std::begin(font::H_Imag_8[index]),
        //           std::begin(font::H_Imag_8[index]) + 8,
        //           std::begin(data_mapping[y]) + x + 1);
    }
    else if (image_size == OLED_IMAGE_SIZE::OLED_IMAGE_SIZE_4)
    {
        memmove(data_mapping->getDataMapping()[y] + x + 1,
                font::H_Imag_4[index],
                4);
        // std::copy(std::begin(font::H_Imag_4[index]),
        //           std::begin(font::H_Imag_4[index]) + 4,
        //           std::begin(data_mapping[y]) + x + 1);
    }
}

oled::Paint::Paint()
{
}

oled::Paint::~Paint()
{
}
