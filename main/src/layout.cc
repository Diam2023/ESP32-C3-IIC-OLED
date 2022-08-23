//
// Created by monoliths on 8/21/22.
//
#include "layout.h"
#include "esp_err.h"
#include <vector>
#include "page.h"
#include<algorithm>

void oled::Layout::addWidget(oled::Widget *widget_)
{

    if (widget_ != nullptr)
    {
        this->m_widgets.push_back(widget_);
        this->positions.emplace_back(Point());
    } else {
        OLED_D("Try to add a null widget in Layout!");
    }
}

void oled::Layout::addWidget(oled::Widget *widget_, const oled::Point &&point_)
{
    if (widget_ != nullptr)
    {
        this->m_widgets.emplace_back(widget_);
        this->positions.emplace_back(point_);
    } else {
        OLED_D("Try to add a null widget in Layout!");
    }
}

int oled::Layout::indexOfWidget(oled::Widget *widget_)
{
//    auto result = std::find(this->widgets.begin(), this->widgets.end(), widget_);
//
//    if (result != this->widgets.end())
//    {
//        auto widget = *result;
//    }
    for (int i = 0; i <= this->m_widgets.size(); i++)
    {
        if (this->m_widgets.at(i) == widget_)
        {
            return i;
        }
    }
    return -1;
}

void oled::Layout::flash()
{
    ESP_ERROR_CHECK(this->m_widgets.size() != this->positions.size());
    for (size_t i = 0; i < this->m_widgets.size(); i++)
    {
        // ergodic widget and point to flash
        this->m_widgets.at(i)->flash(
            this->m_pPage->dataMap(),
            this->positions.at(i));
    }
}


void oled::Layout::flash(oled::Widget *widget_)
{
    ESP_ERROR_CHECK(this->m_widgets.size() != this->positions.size());
    for (size_t i = 0; i < this->m_widgets.size(); i++)
    {
        if (widget_ == this->m_widgets.at(i))
        {
            widget_->flash(
                this->m_pPage->dataMap(),
                this->positions.at(i));
        }
    }
}


void oled::Layout::setPage(oled::Page *page_)
{
    if (page_ == nullptr)
    {
        OLED_D("Try To set a nullptr for page")
    }
    this->m_pPage = page_;
    OLED_I("start widget set page");
    for (auto widget : this->m_widgets)
    {
        // ergodic widget and point to flash
        OLED_I("page set");
        widget->setPage(page_);
    }
}

oled::Widget* oled::Layout::getWidget(const uint8_t index_)
{
    return this->m_widgets.at(index_);
}

std::vector<oled::Widget *> &&oled::Layout::widgets()
{
    return std::move(this->m_widgets);
}