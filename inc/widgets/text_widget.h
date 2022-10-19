#pragma once

#include "widget.h"
#include "model.h"

namespace oled
{

class TextWidget : public Widget
{
private:

public:
    void setModel(Model<std::string>*);

    Model<std::string>* model();

    void setText(const std::string &&text_);
    void updateText(const std::string&&);

    std::string&& text();

    void flash(DataMap *, const Point &) override;

    void modelUpdated() override;

    explicit TextWidget(std::string &&);
    explicit TextWidget(std::string &&text_, Page*);
    explicit TextWidget(std::string &&text_, Object*, Page*);
    explicit TextWidget(Object* model_, Page* page_) : Widget(model_, page_) {};
    TextWidget();
    ~TextWidget() = default;
};

}    // namespace oled
