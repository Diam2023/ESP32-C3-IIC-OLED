//
// Created by monoliths on 8/28/22.
//

#ifndef ESP32_C3_IIC_OLED_LIST_LAYOUT_H
#define ESP32_C3_IIC_OLED_LIST_LAYOUT_H

#include "layout.h"

namespace oled
{



class ListLayout : public Layout
{
OLED_OBJECT
public:
    void addWidget(Widget*);

    void addWidget(Widget*, const Point&&);

    int indexOfWidget(Widget*);

    oled::Widget* getWidget(uint8_t);

    std::vector<Widget*>&& widgets();
    void flash();
    void flash(Widget*);


};

}

#endif    // ESP32_C3_IIC_OLED_LIST_LAYOUT_H
