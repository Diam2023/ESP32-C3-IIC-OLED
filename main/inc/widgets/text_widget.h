#pragma once

#include "widget.h"
#include "model.h"

#include "string_object.h"

namespace oled
{

class TextWidget : public Widget
{
private:
    OLED_FONT_SIZE m_fontSize;

public:
    uint8_t getWidth() override;
    uint8_t getHeight() override;
    Size getSize() override;

    void setFontSize(OLED_FONT_SIZE fontSize);

    void setModel(Model<oled::String> *);

    Model<oled::String> *model();

    void setText(std::string &&text);

    void setText(const std::string &text);

    void setText(oled::String &&text);

    void setText(const oled::String &text);

    /**
     * It will set update Flag true
     */
    void updateText(const oled::String &&);

    /**
     * It will set update Flag true
     * @param text
     */
    void updateText(const std::string &text);

    /**
     * It will set update Flag true
     * @param text
     */
    void updateText(std::string &&text);

    oled::String &&text();

    void flash(DataMap *, const Point &) override;

    //    void modelUpdated() override;

    explicit TextWidget(oled::String &&text,
                        OLED_FONT_SIZE fontSize = OLED_FONT_SIZE_6);

    explicit TextWidget(std::string &&text,
                        OLED_FONT_SIZE fontSize = OLED_FONT_SIZE_6);

    explicit TextWidget(oled::String &&text,
                        Page *,
                        OLED_FONT_SIZE fontSize = OLED_FONT_SIZE_6);

    explicit TextWidget(oled::String &&text,
                        oled::Model<oled::String> *,
                        Page *,
                        OLED_FONT_SIZE fontSize = OLED_FONT_SIZE_6);

    TextWidget();

    ~TextWidget() override = default;
};

}    // namespace oled
