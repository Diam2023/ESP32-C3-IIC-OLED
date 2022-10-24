#pragma once

#include "widget.h"
#include "model.h"

namespace oled {

    class TextWidget : public Widget {
    private:
        OLED_FONT_SIZE m_fontSize;

    public:
        void setFontSize(OLED_FONT_SIZE fontSize);

        void setModel(Model<std::string> *);

        Model<std::string> *model();

        void setText(const std::string &&text);

        void updateText(const std::string &&);

        std::string &&text();

        void flash(DataMap *, const Point &) override;

        void modelUpdated() override;

        explicit TextWidget(std::string &&text, OLED_FONT_SIZE fontSize = OLED_FONT_SIZE_6);

        explicit TextWidget(std::string &&text, Page *, OLED_FONT_SIZE fontSize = OLED_FONT_SIZE_6);

        explicit TextWidget(std::string &&text, Object *, Page *, OLED_FONT_SIZE fontSize = OLED_FONT_SIZE_6);

        explicit TextWidget(Object *model, Page *page) : Widget(model, page), m_fontSize(OLED_FONT_SIZE_6) {};

        TextWidget();

        ~TextWidget() = default;
    };

}    // namespace oled
