//
// Created by monoliths on 11/26/22.
//

#ifndef ESP32_C3_IIC_OLED_GRAPH_WIDGET_H
#define ESP32_C3_IIC_OLED_GRAPH_WIDGET_H

#include "widget.h"
#include <functional>

namespace oled
{

class GraphWidget : public Widget
{
private:
    Size m_size;

public:
    uint8_t getWidth() override;
    uint8_t getHeight() override;
    Size getSize() override;

    void setSize(const Size &size);

    using Func = std::function<void(GraphWidget *, DataMap *, const Point &)>;

    void setModel(Model<Func> *);

    void setFunction(Func &&function);

    void modelUpdated() override;

    void flash(DataMap *, const Point &) override;

    explicit GraphWidget(Func &&function, Page *);

    ~GraphWidget() override = default;

    GraphWidget();
};
};    // namespace oled

#endif    // ESP32_C3_IIC_OLED_GRAPH_WIDGET_H
