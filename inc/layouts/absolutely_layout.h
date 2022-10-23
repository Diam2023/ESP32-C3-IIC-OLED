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

    void addWidget(Widget *pWidget, Point &&pPoint) override;
//    AbsolutelyLayout();
};

}    // namespace oled

#endif    // ESP32_C3_IIC_OLED_ABSOLUTELY_LAYOUT_H
