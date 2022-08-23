#pragma once

#include <cstdint>
#include <cstring>

namespace oled
{

/**
 * @brief data container
 */
class DataMap
{
private:
    uint8_t** data_mapping;
    const uint8_t page;
    const uint8_t line_seg;

public:
    inline uint8_t getPage() const { return page; }
    inline uint8_t getLineSeg() const { return line_seg; }

    inline uint8_t** getDataMapping()
    {
        return data_mapping;
    }

    inline void setPageData(const uint8_t page_, const uint8_t data) const
    {
        for (size_t i = 0; i < this->line_seg; i++)
        {
            this->data_mapping[page_][i] = data;
        }
    }

    inline void setData(const uint8_t page_,
                        const uint8_t line_seg_,
                        const uint8_t data) const
    {
        this->data_mapping[page_][line_seg_] = data;
    }

    inline void setData(const uint8_t data) const
    {
        for (size_t i = 0; i < this->page; i++)
        {
            for (size_t j = 0; j < this->line_seg; j++)
            {
                this->data_mapping[i][j] = data;
            }
        }
    }

    DataMap(const uint8_t page, const uint8_t line_seg);
    ~DataMap();
};

inline DataMap::DataMap(const uint8_t page, const uint8_t line_seg)
    : page(page), line_seg(line_seg)
{
    this->data_mapping = new uint8_t*[page];
    for (size_t i = 0; i < page; i++)
    {
        this->data_mapping[i] = new uint8_t[line_seg];
    }
}

inline DataMap::~DataMap()
{
    for (size_t i = 0; i < page; i++)
    {
        delete data_mapping[i];
    }
}

}
