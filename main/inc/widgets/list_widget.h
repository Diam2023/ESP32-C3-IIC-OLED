//
// Created by monoliths on 12/3/22.
//

#ifndef ESP32_C3_IIC_OLED_LIST_WIDGET_H
#define ESP32_C3_IIC_OLED_LIST_WIDGET_H

#include "widget.h"
#include "list_layout.h"

namespace oled
{

/**
 * Use ListLayout Set Widget Position.
 */
class ListWidget : public Widget, public ListLayout
{
    OLED_OBJECT
protected:
public:
    uint8_t getWidth() override;
    uint8_t getHeight() override;
//    Rectangle getArea() override;

    explicit ListWidget(Page* pPage,
                        Direction direction,
                        Position position,
                        Size size);

    ListWidget() = delete;
    ~ListWidget() override = default;
};

};    // namespace oled

#endif    // ESP32_C3_IIC_OLED_LIST_WIDGET_H
