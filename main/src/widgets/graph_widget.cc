//
// Created by monoliths on 11/27/22.
//
#include "graph_widget.h"
#include "model.h"
#include "page.h"

oled::GraphWidget::GraphWidget(Func &&function, Page *pPage)
{
    this->setPage(pPage);
    auto *model_ = new Model<Func>();
    model_->bindWidget(this);
    model_->setData(function);
    this->bindModel(reinterpret_cast<Model<Object> *>(model_));
}

oled::GraphWidget::GraphWidget() : Widget()
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
    auto callBack = reinterpret_cast<oled::Model<Func> *>(this->m_pModel);
    if (callBack != nullptr)
    {
        callBack->data()(pDataMapping, point);
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
