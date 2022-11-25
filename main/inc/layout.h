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
     * widget EveryThing
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
    //    virtual void addWidget(Widget<Object>* pWidget, Point&& pPoint);

    /**
     * Remove
     * @param pWidget
     */
    void addWidget(Widget* pWidget);
    void addPosition(Point&& pPoint);

    void removeWidget(Widget* pWidget);
    void removePosition(Point&& pPoint);

    void setPage(Page* pPoint);

    oled::Widget* getWidget(uint8_t index);

    std::vector<Widget*>&& widgets();

    int indexOfWidget(const Widget* pWidget);

    void flash();
    void flash(const Widget* pWidget);

    Layout();;

    explicit Layout(Page* pPage);

    ~Layout() override = default;
};

}    // namespace oled

#endif    // ESP32_C3_IIC_OLED_LAYOUT_H
