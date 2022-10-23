//
// Created by monoliths on 8/21/22.
//

#include "absolutely_layout.h"


void oled::AbsolutelyLayout::addWidget(oled::Widget *pWidget,
                                       oled::Point &&pPoint)
{
    Layout::addWidget(pWidget, std::move(pPoint));
}
