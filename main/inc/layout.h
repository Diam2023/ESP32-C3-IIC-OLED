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
    void addWidget(Widget*, const Point&&);

    void setPage(Page*);

    oled::Widget* getWidget(uint8_t);

    std::vector<Widget*>&& widgets();

    int indexOfWidget(Widget*);

    Layout() = default;

    ~Layout() = default;

    void flash();
    void flash(Widget*);
};

}    // namespace oled

#endif    // ESP32_C3_IIC_OLED_LAYOUT_H
