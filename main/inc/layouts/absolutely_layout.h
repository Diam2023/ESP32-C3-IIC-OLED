//
// Created by monoliths on 8/21/22.
//

#ifndef ESP32_C3_IIC_OLED_ABSOLUTELY_LAYOUT_H
#define ESP32_C3_IIC_OLED_ABSOLUTELY_LAYOUT_H

#include "layout.h"

namespace oled
{

class AbsolutelyLayout : public Layout
{
private:
public:
    /**
     * Add The Widget In Position pPoint
     * @param pWidget widget
     * @param pPoint position
     */
    void addWidget(Widget* pWidget, Point&& pPoint);

    /**
     * Remove Widget From Layout Container.
     * @param pWidget widget
     * @param pPoint position
     */
    void removeWidget(Widget* pWidget, Point&& pPoint);

    AbsolutelyLayout();
    explicit AbsolutelyLayout(Page* page) : Layout(page){};

    ~AbsolutelyLayout() override = default;
    ;
};

}    // namespace oled

#endif    // ESP32_C3_IIC_OLED_ABSOLUTELY_LAYOUT_H
