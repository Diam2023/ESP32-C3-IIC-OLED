//
// Created by monoliths on 8/21/22.
//

#ifndef ESP32_C3_IIC_OLED_LAYOUT_H
#define ESP32_C3_IIC_OLED_LAYOUT_H

#include <utility>
#include <vector>
#include "widget.h"
#include "object.h"

#include <map>

namespace oled
{

class Page;

class Layout : public Object
{
    OLED_OBJECT
protected:
    // TODO Wait Change Structure For Save Widget Or Position
    //    /**
    //     * widget EveryThing
    //     */
    //    std::vector<Widget*> m_widgets;
    //
    //    /**
    //     * Position for widgets
    //     */
    //    std::vector<Position> m_positions;

    // std::map<Widget*, Position> m_compose;

    /**
     * parent page pointer
     */
    Page* m_pPage;

    /**
     * Position For Layout
     */
    Position m_position;

    /**
     * Save Layout Size
     */
    Size m_size;

public:
    bool checkInArea(const Position& point, Widget* pWidget)
    {
        return ((point.getX() >= this->m_position.getX()) &&    // X in rang
                ((pWidget->getWidth() + point.getX()) <=        // left in rang
                 (this->m_position.getX() + this->m_size.getWidth())) &&
                ((point.getY() >= this->m_position.getY()) &&    // Exec
                 (((pWidget->getHeight() / 8) + point.getY()) <=
                  (this->m_position.getY() + this->m_size.getHeight()))));
    };

    //    virtual void addWidget(Widget*) {};
    //    virtual void addWidget(Widget*, const Point&) {};

    //    void addCompose(const std::pair<Widget*, Position>&);

    //    void removeCompose(const std::pair<Widget*, Position>&);

    //    void removeCompose(Widget* pWidget);
    //    void removeCompose(Point&& pPoint);

    virtual void setPage(Page* pPage);

    /**
     * Set Position
     * @param position Position For Layout
     */
    void setPosition(const Position& position)
    {
        m_position = position;
    };

    void setSize(const Size&);

    //    int indexOfWidget(const Widget* pWidget);

    virtual void flash(){};

    virtual void flash(const Widget* pWidget){};

    Layout() : m_pPage(), m_position(), m_size(){};

    explicit Layout(Page* pPage);

    explicit Layout(Page* pPage, Position position, Size size)
        : m_pPage(pPage), m_position(std::move(position)), m_size(size){};

    ~Layout() override = default;
};

}    // namespace oled

#endif    // ESP32_C3_IIC_OLED_LAYOUT_H
