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
    uint8_t** m_pDataMapping;
    const uint8_t cm_page;
    const uint8_t cm_lineSeg;

public:
    inline uint8_t getPage() const
    {
        return cm_page;
    }
    inline uint8_t getLineSeg() const
    {
        return cm_lineSeg;
    }

    inline uint8_t** getDataMapping()
    {
        return m_pDataMapping;
    }

    inline void setPageData(const uint8_t page_, const uint8_t data) const
    {
        for (size_t i = 0; i < this->cm_lineSeg; i++)
        {
            this->m_pDataMapping[page_][i] = data;
        }
    }

    inline void setData(const uint8_t page_,
                        const uint8_t line_seg_,
                        const uint8_t data) const
    {
        this->m_pDataMapping[page_][line_seg_] = data;
    }

    inline void setData(const uint8_t data) const
    {
        for (size_t i = 0; i < this->cm_page; i++)
        {
            for (size_t j = 0; j < this->cm_lineSeg; j++)
            {
                this->m_pDataMapping[i][j] = data;
            }
        }
    }

    DataMap(uint8_t page, uint8_t lineSeg);
    ~DataMap();
};

inline DataMap::DataMap(const uint8_t page, const uint8_t lineSeg)
    : cm_page(page), cm_lineSeg(lineSeg)
{
    this->m_pDataMapping = new uint8_t*[page];
    for (size_t i = 0; i < page; i++)
    {
        this->m_pDataMapping[i] = new uint8_t[cm_lineSeg];
    }
}

inline DataMap::~DataMap()
{
    for (size_t i = 0; i < cm_page; i++)
    {
        delete m_pDataMapping[i];
    }
}

}    // namespace oled
