//
// Created by monoliths on 10/24/22.
//
#include "image_widget.h"

#include "page.h"

oled::ImageWidget::ImageWidget() : Widget(), m_imageSize(OLED_IMAGE_SIZE_8) {
    auto *model = new Model<uint32_t>();
    model->bindWidget(this);
    this->bindModel(dynamic_cast<Object *>(model));

    this->setIndex(0);
}

oled::ImageWidget::ImageWidget(uint32_t index, oled::OLED_IMAGE_SIZE imageSize) : Widget(), m_imageSize(imageSize) {
    auto *model_ = new Model<uint32_t>();
    model_->bindWidget(this);
    this->bindModel(dynamic_cast<Object *>(model_));

    this->setIndex(index);
}

oled::ImageWidget::ImageWidget(uint32_t index, oled::Page *page, oled::OLED_IMAGE_SIZE imageSize)
        : Widget(), m_imageSize(imageSize) {
    this->setPage(page);
    auto *model_ = new Model<uint32_t>();
    model_->bindWidget(this);
    this->bindModel(dynamic_cast<Object *>(model_));
    this->setIndex(index);
}

oled::ImageWidget::ImageWidget(uint32_t index,
                               oled::Object *model,
                               oled::Page *page, oled::OLED_IMAGE_SIZE imageSize)
        : Widget(model, page), m_imageSize(imageSize) {
    ESP_ERROR_CHECK(this->model() == nullptr);
    this->model()->setData(index);
}

void oled::ImageWidget::modelUpdated() {
    ESP_ERROR_CHECK(this->page() == nullptr);

    // only flash this widget
    this->page()->flash(this);
}

void oled::ImageWidget::flash(DataMap *dataMapping, const Point &point) {
    oled::Paint::writeImage(dataMapping,
                            point.getX(),
                            point.getY(),
                            this->index(),
                            m_imageSize);
}

void oled::ImageWidget::setModel(oled::Model<uint32_t> *model) {
    this->bindModel(model);
}

oled::Model<uint32_t> *oled::ImageWidget::model() {
    return dynamic_cast<oled::Model<uint32_t> *>(this->m_pModel);
}

uint32_t oled::ImageWidget::index() {
    return this->model()->data();
}

void oled::ImageWidget::setIndex(uint32_t index) {
    ESP_ERROR_CHECK(this->model() == nullptr);
    this->model()->setData(index);
}

void oled::ImageWidget::updateIndex(uint32_t index) {
    ESP_ERROR_CHECK(this->model() == nullptr);
    this->model()->updateData(index);
}

void oled::ImageWidget::setImageSize(oled::OLED_IMAGE_SIZE imageSize) {
    m_imageSize = imageSize;
}


