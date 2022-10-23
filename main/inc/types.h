#pragma once

#include <cstdint>

#include <functional>

#define MODEL_MEMBERS private:

namespace oled
{
class Point;

class Point
{
private:
    uint8_t m_x;
    uint8_t m_y;

public:
    uint8_t getX() const
    {
        return this->m_x;
    }
    uint8_t getY() const
    {
        return this->m_y;
    }

    Point() : m_x(0), m_y(0){};

    Point(const uint8_t x, const uint8_t y) : m_x(x), m_y(y){};

    Point(const Point& point) : Point(point.m_x, point.m_y){};

    ~Point() = default;
};

class Rectangle
{
private:
    oled::Point m_start;
    oled::Point m_end;

public:
    Rectangle(Point&&, Point&&);
    Rectangle(const Point&, const Point&);

    Rectangle() : m_start({0, 0}), m_end({0, 0}){};
    ~Rectangle() = default;
};

inline Rectangle::Rectangle(Point&& start, Point&& end)
    : m_start(start), m_end(end)
{
}

inline Rectangle::Rectangle(const Point& start, const Point& end)
    : m_start(start), m_end(end)
{
}

class Size
{
private:
    uint8_t m_width;
    uint8_t m_height;

public:
    Size() : m_width(0), m_height(0)
    {
    }

    Size(const uint8_t& width, const uint8_t& height)
        : m_width(width), m_height(height)
    {
    }

    ~Size() = default;

    inline uint8_t getWidth() const
    {
        return m_width;
    };
    inline uint8_t getHeight() const
    {
        return m_height;
    };
};

enum OLED_FONT_SIZE
{
    OLED_FONT_SIZE_6,
    OLED_FONT_SIZE_16,
};

/**
 * @brief show on oled image.
 */
enum OLED_IMAGE_SIZE
{
    OLED_IMAGE_SIZE_4,
    OLED_IMAGE_SIZE_8,
    OLED_IMAGE_SIZE_32
};

struct DeviceInfo
{
    uint8_t max_page;
    uint8_t max_line_seg;

    size_t init_size;
    uint8_t init_cmd[];
};

struct Event
{
};

struct InputEvent : public Event
{
};

using EventHandler_t = std::function<void*(struct EVENT)>;

}    // namespace oled
