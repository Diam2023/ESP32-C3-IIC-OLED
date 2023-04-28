//
// Created by monoliths on 12/3/22.
//
#include "list_widget.h"
#include "model.h"

oled::ListWidget::ListWidget(oled::Page *pPage,
                                 oled::Direction direction,
                                 oled::Position position,
                                 oled::Size size)
    : ListLayout(pPage, direction, std::move(position), size)
{
    Widget::setPage(pPage);

    auto *model_ = new oled::Model<ListWidget*>(this);
    model_->bindWidget(this);
    model_->setData(this);
    this->bindModel(reinterpret_cast<Model<Object> *>(model_));
}

uint8_t oled::ListWidget::getWidth()
{
    return ListLayout::m_size.getWidth();
}

uint8_t oled::ListWidget::getHeight()
{
    return ListLayout::m_size.getHeight();
}
