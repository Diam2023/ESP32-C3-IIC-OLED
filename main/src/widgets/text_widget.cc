#include "text_widget.h"

#include "page.h"

oled::TextWidget::TextWidget() : Widget(), m_fontSize(OLED_FONT_SIZE_6)
{
    auto *model = new Model<oled::String>();
    model->bindWidget(this);
    this->bindModel(reinterpret_cast<Model<Object> *>(model));

    this->setText(static_cast<const oled::String &>(this->getObjectName()));
}

oled::TextWidget::TextWidget(oled::String &&text, OLED_FONT_SIZE fontSize)
    : Widget(), m_fontSize(fontSize)
{
    auto *model_ = new Model<oled::String>();
    model_->bindWidget(this);
    this->bindModel(reinterpret_cast<Model<Object> *>(model_));

    this->setText(std::move(text));
}

oled::TextWidget::TextWidget(oled::String &&text,
                             oled::Page *page,
                             OLED_FONT_SIZE fontSize)
    : Widget(), m_fontSize(fontSize)
{
    this->setPage(page);
    auto *model_ = new Model<oled::String>();
    model_->bindWidget(this);
    ESP_ERROR_CHECK(reinterpret_cast<Model<Object> *>(model_) == nullptr);
    this->bindModel(reinterpret_cast<Model<Object> *>(model_));
    this->setText(std::move(text));
}

oled::TextWidget::TextWidget(oled::String &&text,
                             oled::Model<oled::String> *model,
                             oled::Page *page,
                             OLED_FONT_SIZE fontSize)
    : Widget(model, page), m_fontSize(fontSize)
{
    ESP_ERROR_CHECK(this->model() == nullptr);
    this->model()->setData(text);
}

void oled::TextWidget::modelUpdated()
{
    ESP_ERROR_CHECK(this->page() == nullptr);
    // only flash this widget
    page()->flash(reinterpret_cast<oled::Widget *>(this));
    //    this->page()->flash(this);
}

void oled::TextWidget::flash(DataMap *data_mapping, const Point &point)
{
    oled::Paint::writeString(data_mapping,
                             point.getX(),
                             point.getY(),
                             std::move(this->text()),
                             m_fontSize);
}

void oled::TextWidget::setModel(oled::Model<oled::String> *model)
{
    this->bindModel(reinterpret_cast<Model<Object> *>(model));
}

oled::Model<oled::String> *oled::TextWidget::model()
{
    ESP_ERROR_CHECK(this->m_pModel == nullptr);

    auto result = reinterpret_cast<oled::Model<oled::String> *>(this->m_pModel);

    ESP_ERROR_CHECK(result == nullptr);

    return result;
}

oled::String &&oled::TextWidget::text()
{
    // keep to lvalue
    return std::move(this->model()->data());
}

void oled::TextWidget::setText(oled::String &&text)
{
    ESP_ERROR_CHECK(this->model() == nullptr);
    this->model()->setData(text);
}

void oled::TextWidget::setText(const oled::String &text)
{
    ESP_ERROR_CHECK(this->model() == nullptr);
    this->model()->setData(text);
}

void oled::TextWidget::updateText(const oled::String &&text)
{
    ESP_ERROR_CHECK(this->model() == nullptr);
    this->model()->updateData(text);
}

void oled::TextWidget::setFontSize(oled::OLED_FONT_SIZE oledFontSize)
{
    m_fontSize = oledFontSize;
}

oled::TextWidget::TextWidget(std::string &&text, oled::OLED_FONT_SIZE fontSize)
{
    auto *model_ = new Model<oled::String>();
    model_->bindWidget(this);
    this->bindModel(reinterpret_cast<Model<Object> *>(model_));

    this->setText(static_cast<oled::String &&>(std::move(text)));
}
