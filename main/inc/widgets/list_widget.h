//
// Created by monoliths on 8/28/22.
//

#ifndef ESP32_C3_IIC_OLED_LIST_WIDGET_H
#define ESP32_C3_IIC_OLED_LIST_WIDGET_H

#include "object.h"

#include "widget.h"
#include "model.h"
#include <vector>

namespace oled
{

class ListWidget : public Widget
{
private:

public:
//        void setModel(Model<std::string>*);

        Model<std::vector<std::string>>* model();
        void addText(std::string&& text_);

//        void setText(const std::string &&text_);
        void updateText(const std::string&&);

        std::string&& text();

        void flash(DataMap *, const Point &) override;

        void modelUpdated() override;

        void eraseText(std::string&& text_);
        void clear();
};

}

#endif //ESP32_C3_IIC_OLED_LIST_WIDGET_H
