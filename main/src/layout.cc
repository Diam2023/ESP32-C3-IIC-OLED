//
// Created by monoliths on 8/21/22.
//
#include "layout.h"
#include "esp_err.h"
#include <vector>
#include "page.h"

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

void oled::Layout::setPage(oled::Page *pPage)
{
    if (pPage == nullptr)
    {
        OLED_W("Try To set a nullptr for page")
    }
    this->m_pPage = pPage;
}

oled::Layout::Layout(oled::Page *pPage)
    : m_pPage(pPage),
      m_position({0, 0}),
      m_size({pPage->dataMap()->getLineSeg(), pPage->dataMap()->getPage()})
{
}

void oled::Layout::setSize(const oled::Size &size)
{
    m_size = size;
}

// void oled::Layout::addCompose(const std::pair<Widget *, Position> &compose)
//{
//     m_compose.emplace(compose);
// }
//  void oled::Layout::removeCompose(const std::pair<Widget *, Position>
//  &compose)
//{
//     for (auto c = m_compose.begin(); c != m_compose.end(); c++)
//     {
//         if ((c->first == compose.first) && (c->second == compose.second))
//         {
//             m_compose.erase(c);
//             break;
//         }
//     }
// }
//  std::map<oled::Widget *, oled::Position> *oled::Layout::widgets()
//{
//     return &m_compose;
// }
//
//  void oled::Layout::removeCompose(oled::Widget *pWidget)
//{
//     for (auto c = m_compose.begin(); c != m_compose.end(); c++)
//     {
//         if (c->first == pWidget)
//         {
//             m_compose.erase(c);
//             break;
//         }
//     }
// }
//
//  void oled::Layout::removeCompose(oled::Point &&pPoint)
//{
//     for (auto c = m_compose.begin(); c != m_compose.end(); c++)
//     {
//         if (c->second == pPoint)
//         {
//             m_compose.erase(c);
//             break;
//         }
//     }
// }
