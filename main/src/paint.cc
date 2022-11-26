#include "paint.h"

#include <cstring>
#include "oled_font.h"
#include "esp_log.h"

void oled::Paint::full(DataMap* pDataMapping, const uint8_t data)
{
    for (size_t i = 0; i < pDataMapping->getPage(); i++)
    {
        oled::Paint::full_page(pDataMapping, i, data);
    }
}

void oled::Paint::full_page(DataMap* pDataMapping,
                            const uint8_t page,
                            const uint8_t data)
{
    pDataMapping->setPageData(page, data);
    pDataMapping->setData(page, 0, 0x40);
}

void oled::Paint::clear(DataMap* pDataMapping)
{
    this->full(pDataMapping, 0x00);
}

void oled::Paint::writeString(DataMap* pDataMapping,
                              uint8_t x,
                              uint8_t y,
                              const std::string&& string,
                              const OLED_FONT_SIZE fontSize)
{
    uint8_t c;
    uint8_t j = 0;
    if (fontSize == OLED_FONT_SIZE::OLED_FONT_SIZE_16)
    {
        while (string[j] != '\0')
        {
            c = string[j] - 32;
            if (x > 120)
            {
                x = 0;
                y += 2;
            }

            memmove(pDataMapping->getDataMapping()[y] + x + 1,
                    oled::font::F8X16 + c * 16,
                    8);
            memmove(pDataMapping->getDataMapping()[y + 1] + x + 1,
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
            memmove(pDataMapping->getDataMapping()[y] + x + 1,
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

void oled::Paint::writeImage(DataMap* pDataMapping,
                             uint8_t x,
                             uint8_t y,
                             const uint8_t* begin,
                             const uint8_t splitSize,
                             const uint8_t length)
{
    for (size_t line = 0; line < (length / splitSize); line++)
    {
        memmove(pDataMapping->getDataMapping()[y + line] + x + 1,
                begin + (line * splitSize),
                splitSize);
        // std::copy(begin + (line * split_size),
        //           begin + ((line + 1) * split_size),
        //           std::begin(data_mapping[y + line]) + x + 1);
    }
}

void oled::Paint::writeImage(DataMap* pDataMapping,
                             uint8_t x,
                             uint8_t y,
                             const uint32_t index,
                             const OLED_IMAGE_SIZE imageSize)
{
    if (imageSize == OLED_IMAGE_SIZE::OLED_IMAGE_SIZE_32)
    {
        memmove(pDataMapping->getDataMapping()[y] + x + 1,
                font::H_Imag[index * 2],
                16);

        memmove(pDataMapping->getDataMapping()[y + 1] + x + 1,
                font::H_Imag[index * 2 + 1],
                16);
        // std::copy(std::begin(font::H_Imag[index * 2]),
        //           std::begin(font::H_Imag[index * 2]) + 16,
        //           std::begin(data_mapping[y]) + x + 1);

        // std::copy(std::begin(font::H_Imag[index * 2 + 1]),
        //           std::begin(font::H_Imag[index * 2 + 1]) + 16,
        //           std::begin(data_mapping[y + 1]) + x + 1);
    }
    else if (imageSize == OLED_IMAGE_SIZE::OLED_IMAGE_SIZE_8)
    {
        memmove(pDataMapping->getDataMapping()[y] + x + 1,
                font::H_Imag_8[index],
                8);
        // std::copy(std::begin(font::H_Imag_8[index]),
        //           std::begin(font::H_Imag_8[index]) + 8,
        //           std::begin(data_mapping[y]) + x + 1);
    }
    else if (imageSize == OLED_IMAGE_SIZE::OLED_IMAGE_SIZE_4)
    {
        memmove(pDataMapping->getDataMapping()[y] + x + 1,
                font::H_Imag_4[index],
                4);
        // std::copy(std::begin(font::H_Imag_4[index]),
        //           std::begin(font::H_Imag_4[index]) + 4,
        //           std::begin(data_mapping[y]) + x + 1);
    }
}

void oled::Paint::offset(oled::DataMap* pDataMapping,
                         uint8_t x,
                         uint8_t y,
                         uint8_t width,
                         uint8_t height,
                         int16_t offset,
                         oled::OLED_OFFSET_DIRECTION direction)
{
    //    pDataMapping
    if (direction == oled::OLED_OFFSET_HORIZONTAL)
    {
        // height Must bigger than zero
        for (int16_t y_ = y; y_ <= (y + height); y_++)
        {
            memmove(pDataMapping->getDataMapping()[y_] + x + 1 + offset,
                    pDataMapping->getDataMapping()[y_] + x + 1,
                    width - offset);

            memset(pDataMapping->getDataMapping()[y_] + x + 1, 0, offset);
        }
    }
    else
    {
        uint8_t tempData[height][width];
        for (int i = 0; i < height; i++)
        {
            memmove(tempData[i] + 0,
                    pDataMapping->getDataMapping()[y + i] + x,
                    width);
        }

        for (int i = 0; i < height; i++)
        {
            memmove(pDataMapping->getDataMapping()[y + offset + i] + x,
                    tempData[i] + 0,
                    width);
        }

        for (int y_ = y; y_ < y + offset; y_++)
        {
            memset(pDataMapping->getDataMapping()[y_] + x, 0, width);
        }
    }
}

oled::Paint::Paint() = default;

oled::Paint::~Paint() = default;
