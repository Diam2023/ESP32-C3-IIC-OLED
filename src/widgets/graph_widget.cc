//
// Created by monoliths on 11/27/22.
//
#include "graph_widget.h"
#include "model.h"
#include "page.h"

oled::GraphWidget::GraphWidget(Func &&function, Page *pPage) : m_size({0, 0})
{
    this->setPage(pPage);
    auto *model_ = new Model<Func>();
    model_->bindWidget(this);
    model_->setData(function);
    this->bindModel(reinterpret_cast<Model<Object> *>(model_));
}

oled::GraphWidget::GraphWidget() : Widget(), m_size({0, 0})
{
}

void oled::GraphWidget::setModel(oled::Model<Func> *pModel)
{
    pModel->bindWidget(this);
    this->bindModel(reinterpret_cast<Model<Object> *>(pModel));
}

void oled::GraphWidget::flash(oled::DataMap *pDataMapping,
                              const oled::Point &point)
{
    if (!visible())
    {
        return;
    }
    auto callBack = reinterpret_cast<oled::Model<Func> *>(this->m_pModel);
    if (callBack != nullptr)
    {
        callBack->data()(this, pDataMapping, point);
    }
    else
    {
        OLED_D("callBack is null!");
    }
}

void oled::GraphWidget::modelUpdated()
{
    // only flash this widget
    if (this->page() != nullptr)
    {
        this->page()->flash(reinterpret_cast<oled::Widget *>(this));
    }
    else
    {
        OLED_D("Page is null!");
    }
}

void oled::GraphWidget::setFunction(oled::GraphWidget::Func &&function)
{
    reinterpret_cast<oled::Model<Func> *>(this->m_pModel)->setData(function);
}

uint8_t oled::GraphWidget::getWidth()
{
    return m_size.getWidth();
}

uint8_t oled::GraphWidget::getHeight()
{
    return m_size.getHeight();
}

oled::Size oled::GraphWidget::getSize()
{
    return m_size;
}

void oled::GraphWidget::setSize(const oled::Size &size)
{
    m_size = size;
}
