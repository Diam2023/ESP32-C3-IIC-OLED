#include "page.h"

#include "window.h"

oled::Page::Page(const OledDevice *pDevice)
{
    this->m_pDataMap = new DataMap(pDevice->cm_pDeviceInfo->max_page,
                                   pDevice->cm_pDeviceInfo->max_line_seg);
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

void oled::Page::addLayout(Layout *pLayout)
{
    pLayout->setPage(this);
    this->m_layouts.emplace_back(pLayout);
}

oled::DataMap *oled::Page::dataMap()
{
    if (this->m_pDataMap == nullptr)
    {
        OLED_W("Return a null DataMap pointer!");
    }
    return this->m_pDataMap;
}

void oled::Page::full(uint8_t data)
{
    oled::Paint::full(dataMap(), data);
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

void oled::Page::flash(oled::Widget *pWidget)
{
    for (auto layout : this->m_layouts)
    {
        layout->flash(pWidget);
    }

    this->window()->flash(this);
}

void oled::Page::bindWindow(const oled::Window *pWindow)
{
    this->m_pWindow = const_cast<Window *>(pWindow);

    // Fix Forget Bind DataMap.
    if (this->m_pDataMap == nullptr)
    {
        this->m_pDataMap =
            new DataMap(pWindow->getOledDevice()->cm_pDeviceInfo->max_page,
                        pWindow->getOledDevice()->cm_pDeviceInfo->max_line_seg);
    }
}

oled::Window *oled::Page::window()
{
    return this->m_pWindow;
}

oled::Page::Page(const oled::Window *pWindow)
{
    this->m_pWindow = const_cast<Window *>(pWindow);
    this->m_pDataMap =
        new DataMap(pWindow->getOledDevice()->cm_pDeviceInfo->max_page,
                    pWindow->getOledDevice()->cm_pDeviceInfo->max_line_seg);
}

void oled::Page::update()
{
    for (auto layout : this->m_layouts)
    {
        layout->update();
    }

    this->window()->flash(this);
}

//std::pair<oled::Layout *, oled::Position> oled::Page::getPosition(oled::Widget *pWidget)
//{
////    std::find_if(m_layouts.begin(), m_layouts.end(), [&](Layout *layout) -> bool{
////        return (pWidget == layout->getPosition())
////    });
////    return std::make_pair()
//}
