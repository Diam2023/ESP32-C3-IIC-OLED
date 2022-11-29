//
// Created by monoliths on 8/21/22.
//

#include "absolutely_layout.h"
#include "page.h"

void oled::AbsolutelyLayout::addWidget(oled::Widget *pWidget,
                                       oled::Position &&point)
{
    if (checkInArea(point, pWidget))
    {
        m_objects.emplace(std::make_pair(point, pWidget));
    }
}

void oled::AbsolutelyLayout::removeWidget(oled::Widget *pWidget)
{
    for (auto c = m_objects.begin(); c != m_objects.end(); c++)
    {
        if (c->second == pWidget)
        {
            m_objects.erase(c);
            break;
        }
    }
}

oled::AbsolutelyLayout::AbsolutelyLayout() : m_objects()
{
    m_pPage = nullptr;
}

void oled::AbsolutelyLayout::setPage(oled::Page *pPage)
{
    Layout::setPage(pPage);

    for (auto object : this->m_objects)
    {
        // ergodic widget and point to flash
        object.second->setPage(pPage);
    }
}

void oled::AbsolutelyLayout::flash()
{
    for (auto object : this->m_objects)
    {
        // check position
        if (checkInArea(object.first, object.second))
        {
            object.second->flash(this->m_pPage->dataMap(), object.first);
        }
    }
}

void oled::AbsolutelyLayout::flash(const oled::Widget *pWidget)
{
    for (auto object : this->m_objects)
    {
        if (pWidget == object.second)
        {
            object.second->flash(this->m_pPage->dataMap(), object.first);
        }
    }
}

// void oled::Layout::flash()
//{
//     for (auto compose : this->m_compose)
//     {
//         compose.first->flash(this->m_pPage->dataMap(), compose.second);
//     }
// }
//
// void oled::Layout::flash(const oled::Widget *pWidget)
//{
//     //    ESP_ERROR_CHECK(this->m_compose.size() !=
//     this->m_positions.size()); for (auto compose : this->m_compose)
//     {
//         if (pWidget == compose.first)
//         {
//             compose.first->flash(this->m_pPage->dataMap(), compose.second);
//         }
//     }
// }