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
    void addWidget(Widget *);

    void removeWidget(Widget *);
public:
    AbsolutelyLayout();
};

}

#endif    // ESP32_C3_IIC_OLED_ABSOLUTELY_LAYOUT_H
