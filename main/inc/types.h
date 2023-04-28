#pragma once

#include <cstdint>
#include <cstddef>
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

    bool operator==(const Point& point) const
    {
        return ((point.getX() == m_x) && (point.getX() == m_y));
    };

    // If Use map It Have To reload < symbol
    bool operator<(const Point& point) const
    {
        return ((point.getX() < m_x) && (point.getX() < m_y));
    };

    bool operator!=(const Point& point) const
    {
        return !((point.getX() == m_x) && (point.getX() == m_y));
    };

    Point& operator=(const Point& point)
    {
        m_x = point.getX();
        m_y = point.getY();
        return *this;
    };

    Point() : m_x(0), m_y(0){};

    Point(const uint8_t x, const uint8_t y) : m_x(x), m_y(y){};

    Point(Point&& point) noexcept : Point(point.m_x, point.m_y){};

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

    Size(const uint8_t width, const uint8_t height)
        : m_width(width), m_height(height)
    {
    }

    ~Size() = default;

    uint8_t getWidth() const
    {
        return m_width;
    };
    uint8_t getHeight() const
    {
        return m_height;
    };

    Size& operator=(const oled::Size& size)
    {
        this->m_height = size.getHeight();
        this->m_width = size.getWidth();
        return *this;
    };
};

struct DeviceInfo
{
    uint8_t max_page;
    uint8_t max_line_seg;

    unsigned int init_size;
    uint8_t init_cmd[];
};

// /**
//  * Event For something happen.
//  */
// class Event
// {
// protected:
//     /**
//      * Event Id for Event Class to find Event Type.
//      */
//     uint16_t m_eventId;

// public:
//     /**
//      * Get Event Unique Id
//      * @return unique id
//      */
//     uint16_t getEventId() const
//     {
//         return m_eventId;
//     }

//     /**
//      * set EventID
//      * @param eventId
//      */
//     void setEventId(uint16_t eventId)
//     {
//         m_eventId = eventId;
//     };

//     /**
//      * Use Event Id to compare
//      * @param event event data
//      * @return true for eventId Equ
//      */
//     bool operator==(const Event& event) const
//     {
//         return (event.m_eventId == m_eventId);
//     };

//     Event& operator=(const Event& event)
//     {
//         m_eventId = event.getEventId();
//         return *this;
//     };

    /**
     * use 0 to initialize event id.
     */
    Event()
    {
        m_eventId = 0;
    };

//     /**
//      * add Event id for construction class
//      * @param eventId
//      */
//     explicit Event(uint16_t eventId)
//     {
//         m_eventId = eventId;
//     };

//     ~Event() = default;
// };

// using EventHandler = std::function<void(Event)>;

// Define Position And MicroPoint
using Position = Point;
using MicroPoint = Point;

}    // namespace oled

template <>
struct std::hash<oled::Point>
{
    std::size_t operator()(oled::Point const& point) const noexcept
    {
        std::size_t h1 = std::hash<uint8_t>{}(point.getX());
        std::size_t h2 = std::hash<uint8_t>{}(point.getY());
        return h1 ^ (h2 << 1);    // or use boost::hash_combine
    }
};