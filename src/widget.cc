//
// Created by monoliths on 8/22/22.
//

#include "widget.h"

using namespace oled;

void oled::Widget::setPage(oled::Page* pPage)
{
    this->m_pPage = pPage;
}

oled::Page* oled::Widget::page()
{
    return this->m_pPage;
}

void oled::Widget::bindModel(const oled::Object* pModel)
{
    this->m_pModel = const_cast<oled::Object*>(pModel);
}
