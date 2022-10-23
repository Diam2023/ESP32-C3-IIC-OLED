//
// Created by monoliths on 8/21/22.
//
#include "layout.h"
#include "esp_err.h"
#include <vector>
#include "page.h"
#include <algorithm>

// void oled::Layout::addWidget(oled::Widget *widget_)
//{
//
//     if (widget_ != nullptr)
//     {
//         this->m_widgets.push_back(widget_);
//         this->positions.emplace_back(Point());
//     } else {
//         OLED_D("Try to add a null widget in Layout!");
//     }
// }

void oled::Layout::addWidget(oled::Widget *pWidget, oled::Point &&pPoint)
{
    if (pWidget != nullptr)
    {
        this->m_widgets.emplace_back(pWidget);
        this->m_positions.emplace_back(pPoint);
    }
#ifdef DEBUG

    else
    {
        OLED_D("Try to add a null widget in Layout!");
    }
#endif
}

int oled::Layout::indexOfWidget(const oled::Widget *pWidget)
{
    //    auto result = std::find(this->widgets.begin(), this->widgets.end(),
    //    widget_);
    //
    //    if (result != this->widgets.end())
    //    {
    //        auto widget = *result;
    //    }
    for (int i = 0; i <= this->m_widgets.size(); i++)
    {
        if (this->m_widgets.at(i) == pWidget)
        {
            return i;
        }
    }
    return -1;
}

void oled::Layout::flash()
{
    ESP_ERROR_CHECK(this->m_widgets.size() != this->m_positions.size());

    for (size_t i = 0; i < this->m_widgets.size(); i++)
    {
        // ergodic widget and point to flash
        this->m_widgets.at(i)->flash(this->m_pPage->dataMap(),
                                     this->m_positions.at(i));
    }
}

void oled::Layout::flash(const oled::Widget *pWidget)
{
    ESP_ERROR_CHECK(this->m_widgets.size() != this->m_positions.size());
    for (size_t i = 0; i < this->m_widgets.size(); i++)
    {
        auto widget = this->m_widgets.at(i);
        if (pWidget == widget)
        {
            widget->flash(this->m_pPage->dataMap(), this->m_positions.at(i));
        }
    }
}

void oled::Layout::setPage(oled::Page *pPage)
{
#ifdef DEBUG

    if (pPage == nullptr)
    {
        OLED_D("Try To set a nullptr for page")
    }
#endif
    this->m_pPage = pPage;
    for (auto widget : this->m_widgets)
    {
        // ergodic widget and point to flash
        widget->setPage(pPage);
    }
}

oled::Widget *oled::Layout::getWidget(const uint8_t c_index)
{
    return this->m_widgets.at(c_index);
}

std::vector<oled::Widget *> &&oled::Layout::widgets()
{
    return std::move(this->m_widgets);
}

oled::Layout::Layout(oled::Page *pPage) : m_pPage(pPage)
{
}

void oled::Layout::removeWidget(oled::Widget *pWidget)
{
}

// void oled::Layout::removeWidget(oled::Widget *pWidget)
//{
//     std::remove(m_widgets.begin(), m_widgets.end(), pWidget);
//
//     for (auto i = 0; i < m_widgets.size(); ++i)
//     {
//         if (m_widgets[i] == pWidget)
//         {
//             auto position = m_positions.at(i);
//
//             std::remove(m_positions.begin(), m_positions.end(), position);
//
//         }
//     }
//
//
//
//     // m_positions.at(index);
//
//
//     // std::remove(m_positions.begin(), m_positions.end(),
//     m_positions.at(index));
// }
