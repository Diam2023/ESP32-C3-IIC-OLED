#include "text_widget.h"

#include "page.h"

oled::TextWidget::TextWidget() : Widget(), m_fontSize(OLED_FONT_SIZE_6) {
    auto *model = new Model<std::string>();
    model->bindWidget(this);
    this->bindModel(dynamic_cast<Object *>(model));

    this->setText(this->getObjectName());
}

oled::TextWidget::TextWidget(std::string &&text, OLED_FONT_SIZE fontSize) : Widget(), m_fontSize(fontSize) {
    auto *model_ = new Model<std::string>();
    model_->bindWidget(this);
    this->bindModel(dynamic_cast<Object *>(model_));

    this->setText(std::move(text));
}

oled::TextWidget::TextWidget(std::string &&text, oled::Page *page, OLED_FONT_SIZE fontSize)
        : Widget(), m_fontSize(fontSize) {
    this->setPage(page);
    auto *model_ = new Model<std::string>();
    model_->bindWidget(this);
    this->bindModel(dynamic_cast<Object *>(model_));
    this->setText(std::move(text));
}

oled::TextWidget::TextWidget(std::string &&text,
                             oled::Object *model,
                             oled::Page *page, OLED_FONT_SIZE fontSize)
        : Widget(model, page), m_fontSize(fontSize) {
    ESP_ERROR_CHECK(this->model() == nullptr);
    this->model()->setData(text);
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

void oled::TextWidget::setModel(oled::Model<std::string> *model) {
    this->bindModel(model);
}

oled::Model<std::string> *oled::TextWidget::model() {
    return dynamic_cast<oled::Model<std::string> *>(this->m_pModel);
}

std::string &&oled::TextWidget::text() {
    // keep to lvalue
    return std::move(this->model()->data());
}

void oled::TextWidget::setText(const std::string &&text) {
    ESP_ERROR_CHECK(this->model() == nullptr);
    this->model()->setData(text);
}

void oled::TextWidget::updateText(const std::string &&text) {
    ESP_ERROR_CHECK(this->model() == nullptr);
    this->model()->updateData(text);
}

void oled::TextWidget::setFontSize(oled::OLED_FONT_SIZE oledFontSize) {
    m_fontSize = oledFontSize;
}
