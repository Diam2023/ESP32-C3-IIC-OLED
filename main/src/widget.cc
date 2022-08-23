//
// Created by monoliths on 8/22/22.
//

#include "widget.h"

void oled::Widget::setPage(oled::Page* page_)
{
    this->m_pPage = page_;
}

oled::Page* oled::Widget::page()
{
    return this->m_pPage;
}

void oled::Widget::bindModel(oled::Object* model_)
{
    this->m_pModel = model_;
}
