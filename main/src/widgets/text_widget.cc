#include "text_widget.h"

#include "page.h"

oled::TextWidget::TextWidget() : Widget(), m_fontSize(OLED_FONT_SIZE_6) {
    auto *model_ = new Model<std::string>();
    model_->bindWidget(this);
    this->bindModel(dynamic_cast<Object *>(model_));

    this->setText(this->getObjectName());
}

oled::TextWidget::TextWidget(std::string &&text_, OLED_FONT_SIZE oledFontSize) : Widget(), m_fontSize(oledFontSize) {
    auto *model_ = new Model<std::string>();
    model_->bindWidget(this);
    this->bindModel(dynamic_cast<Object *>(model_));

    this->setText(std::move(text_));
}

oled::TextWidget::TextWidget(std::string &&text_, oled::Page *page_, OLED_FONT_SIZE oledFontSize)
        : Widget(), m_fontSize(oledFontSize) {
    this->setPage(page_);
    auto *model_ = new Model<std::string>();
    model_->bindWidget(this);
    this->bindModel(dynamic_cast<Object *>(model_));
    this->setText(std::move(text_));
}

oled::TextWidget::TextWidget(std::string &&text_,
                             oled::Object *model_,
                             oled::Page *page_, OLED_FONT_SIZE oledFontSize)
        : Widget(model_, page_), m_fontSize(oledFontSize) {
    ESP_ERROR_CHECK(this->model() == nullptr);
    this->model()->setData(text_);
}

void oled::TextWidget::modelUpdated() {
    ESP_ERROR_CHECK(this->page() == nullptr);

    // only flash this widget
    this->page()->flash(this);
}

void oled::TextWidget::flash(DataMap *data_mapping, const Point &point) {
    oled::Paint::writeString(data_mapping,
                             point.getX(),
                             point.getY(),
                             std::move(this->text()),
                             m_fontSize);
}

void oled::TextWidget::setModel(oled::Model<std::string> *model_) {
    this->bindModel(model_);
}

oled::Model<std::string> *oled::TextWidget::model() {
    return dynamic_cast<oled::Model<std::string> *>(this->m_pModel);
}

std::string &&oled::TextWidget::text() {
    // keep to lvalue
    return std::move(this->model()->data());
}

void oled::TextWidget::setText(const std::string &&text_) {
    ESP_ERROR_CHECK(this->model() == nullptr);
    this->model()->setData(text_);
}

void oled::TextWidget::updateText(const std::string &&text_) {
    ESP_ERROR_CHECK(this->model() == nullptr);
    this->model()->updateData(text_);
}

void oled::TextWidget::setFontSize(oled::OLED_FONT_SIZE oledFontSize) {
    m_fontSize = oledFontSize;
}
