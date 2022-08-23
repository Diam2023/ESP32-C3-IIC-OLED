#include "page.h"

#include "window.h"

oled::Page::Page(const OledDevice *device)
{
    this->m_pDataMap = new DataMap(device->device_info->max_page,
                                device->device_info->max_line_seg);
}

oled::Page::Page(uint8_t page, uint8_t line_seg)
{
    this->m_pDataMap = new DataMap(page, line_seg);
}

std::vector<oled::Layout *> &&oled::Page::layouts()
{
    return std::move(this->m_layouts);
}

oled::Page::~Page()
{
    delete this->m_pDataMap;
}

void oled::Page::addLayout(Layout *layout_)
{
    layout_->setPage(this);
    this->m_layouts.emplace_back(layout_);
}

oled::DataMap *oled::Page::dataMap()
{
    if (this->m_pDataMap == nullptr)
    {
        OLED_D("Return a null DataMap pointer!");
    }
    return this->m_pDataMap;
}

void oled::Page::full(uint8_t data)
{
    paint.full(dataMap(), data);
}

void oled::Page::clear()
{
    paint.clear(dataMap());
}

void oled::Page::flash()
{
    for (auto layout : this->m_layouts)
    {
        layout->flash();
    }

    this->window()->flash(this);
}

void oled::Page::flash(oled::Widget *widget_)
{
    for (auto layout : this->m_layouts)
    {
        layout->flash(widget_);
    }

    this->window()->flash(this);
}

void oled::Page::bindWindow(oled::Window *window_)
{
    this->m_pWindow = window_;
}

oled::Window *oled::Page::window()
{
    return this->m_pWindow;
}

