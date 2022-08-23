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
    std::vector<Widget*> m_widgets;
    /**
     * Position for widgets
     */
    std::vector<Point> positions;

    /**
     * parent page pointer
     */
    Page* m_pPage{};

public:
    void setPage(Page*);

    void addWidget(Widget*);
    void addWidget(Widget*, const Point&&);

    int indexOfWidget(Widget*);

    oled::Widget* getWidget(uint8_t);

    std::vector<Widget*>&& widgets();
    void flash();
    void flash(Widget*);

    Layout() = default;

    ~Layout() = default;

};

}

#endif    // ESP32_C3_IIC_OLED_LAYOUT_H
