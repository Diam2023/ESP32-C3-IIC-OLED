//
// Created by monoliths on 8/21/22.
//

#include "absolutely_layout.h"

void oled::AbsolutelyLayout::addWidget(oled::Widget *pWidget,
                                       oled::Point &&pPoint)
{
    Layout::addWidget(reinterpret_cast<oled::Widget *>(pWidget));
    Layout::addPosition(std::move(pPoint));
}

void oled::AbsolutelyLayout::removeWidget(oled::Widget *pWidget,
                                          oled::Point &&pPoint)
{
    Layout::removeWidget(pWidget);
    Layout::removePosition(std::move(pPoint));
}

oled::AbsolutelyLayout::AbsolutelyLayout()
{
    m_pPage = nullptr;
}