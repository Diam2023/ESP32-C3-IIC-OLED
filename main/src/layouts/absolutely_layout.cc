//
// Created by monoliths on 8/21/22.
//

#include "absolutely_layout.h"
#include "page.h"

void oled::AbsolutelyLayout::addWidget(oled::Widget *pWidget,
                                       oled::Position &&point)
{
    if (point.getX() >= this->m_position.getX() &&    // X in rang
        ((pWidget->getWidth() + point.getX()) <=      // left in rang
         (this->m_position.getX() + this->m_size.getWidth())) &&
        (point.getY() >= this->m_position.getY() &&    // Exec
         ((pWidget->getHeight() + point.getY()) <=
          (this->m_position.getY() + this->m_size.getHeight()))))
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

oled::AbsolutelyLayout::AbsolutelyLayout(oled::Page *page)
    : Layout(page), m_objects()
{
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
        object.second->flash(this->m_pPage->dataMap(), object.first);
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