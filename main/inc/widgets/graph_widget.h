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
public:

    using Func = std::function<void(DataMap*, const Point &)>;

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
