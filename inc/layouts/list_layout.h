//
// Created by monoliths on 8/28/22.
//

#ifndef ESP32_C3_IIC_OLED_LIST_LAYOUT_H
#define ESP32_C3_IIC_OLED_LIST_LAYOUT_H

#include "layout.h"

#include <utility>

namespace oled
{

enum Direction
{
    HORIZON,
    VERTICAL
};

class ListLayout : public Layout
{
    OLED_OBJECT

private:
    Direction m_direction;

    /**
     * index -> <Position, Widget*>
     */
    std::vector<std::pair<Point, Widget*>> m_objects;

public:
    void addWidget(Widget* pWidget, uint16_t space = 0);

    std::pair<Position, Widget*> getWidget(uint16_t);

    void flash() override;
    void flash(const Widget*) override;

    void setDirection(Direction direction)
    {
        m_direction = direction;
    };

    Direction getDirection()
    {
        return m_direction;
    };

    ListLayout() : Layout(), m_direction(Direction::VERTICAL), m_objects(){};

    explicit ListLayout(Page* pPage)
        : Layout(pPage), m_direction(Direction::VERTICAL), m_objects(){};

    explicit ListLayout(Direction direction)
        : Layout(), m_direction(direction), m_objects(){};

    explicit ListLayout(Page* pPage, Direction direction)
        : Layout(pPage), m_direction(direction), m_objects(){};

    explicit ListLayout(Page* pPage,
                        Direction direction,
                        Position position,
                        Size size)
        : Layout(pPage, std::move(position), size),
          m_direction(direction),
          m_objects(){};
};

}    // namespace oled

#endif    // ESP32_C3_IIC_OLED_LIST_LAYOUT_H
