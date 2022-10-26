//
// Created by monoliths on 8/21/22.
//

#ifndef ESP32_C3_IIC_OLED_LAYOUT_H
#define ESP32_C3_IIC_OLED_LAYOUT_H

#include <vector>
#include "widget.h"
#include "object.h"

namespace oled
{

class Page;

class Layout : public Object
{
    OLED_OBJECT
protected:
    /**
     * widget
     */
    std::vector<Widget*> m_widgets;

    /**
     * Position for widgets
     */
    std::vector<Point> m_positions;

    /**
     * parent page pointer
     */
    Page* m_pPage;

public:
    virtual void addWidget(Widget* pWidget, Point&& pPoint);

    virtual void removeWidget(Widget* pWidget);

    void setPage(Page* pPoint);

    oled::Widget* getWidget(uint8_t index);

    std::vector<Widget*>&& widgets();

    int indexOfWidget(const Widget* pWidget);

    void flash();
    void flash(const Widget* pWidget);

    Layout() : m_widgets(), m_pPage(){};

    explicit Layout(Page* pPage);

    virtual ~Layout() = default;
};

}    // namespace oled

#endif    // ESP32_C3_IIC_OLED_LAYOUT_H
