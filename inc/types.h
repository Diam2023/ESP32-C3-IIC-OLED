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
    uint8_t x;
    uint8_t y;

public:
    uint8_t getX() const
    {
        return this->x;
    }
    uint8_t getY() const
    {
        return this->y;
    }

    Point() : x(0), y(0){};


    Point(const uint8_t x, const uint8_t y) : x(x), y(y) {};

    Point(const Point& point) : Point(point.x, point.y) {};

    ~Point() = default;
};

class Rectangle
{
private:
    oled::Point start;
    oled::Point end;

public:
    Rectangle()
    {
    }

    Rectangle(const Point&&, const Point&&);

    ~Rectangle()
    {
    }
};

inline Rectangle::Rectangle(const Point&& start_, const Point&& end_)
    : start(start_), end(end_)
{
}

class Size
{
private:
    uint8_t width;
    uint8_t height;

public:
    Size() : width(0), height(0)
    {
    }

    Size(const uint8_t& width, const uint8_t& height)
        : width(width), height(height)
    {
    }

    ~Size()
    {
    }
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
