#include "window.h"
#include "esp_log.h"
#include "page.h"

oled::Window::Window(oled::OledDevice* pDevice)
{
    this->device.reset(pDevice);
}

// TODO Wait to Complete Event Module
// void oled::Window::eventLoop(oled::Event event)
// {
// }

// void oled::Window::registerEventHandler(EventHandler_t eventHandler,
//                                         oled::Event)
// {
// }

void oled::Window::setPage(const uint8_t index)
{
    this->m_nowPage = index;
}

void oled::Window::addPage(Page* pPage)
{
    if (pPage != nullptr)
    {
        this->pages().push_back(pPage);

        OLED_D("window add page %d", this->pages().size());
    }
    else
    {
        OLED_W("Try To add a nullptr to pages");
    }
}

oled::Page* oled::Window::createPage()
{
    auto* page = new oled::Page(this->getOledDevice());
    page->bindWindow(this);
    this->addPage(page);
    return page;
}

void oled::Window::show()
{
    OLED_D("showTag pages size%d", this->pages().size());

    if (!this->m_pages.empty())
    {
        auto page = this->pages().at(this->m_nowPage);
        page->flash();
        //        this->getOledDevice()->flash(page->dataMap());
    }
    else
    {
        OLED_W("page is empty!");
    }
}

void oled::Window::flash(const Page* pPage)
{
    // TODO BUG Fix should Find pPage in pages.
    auto page = this->pages().at(this->m_nowPage);
    if (page == pPage)
    {
        this->getOledDevice()->flash(page->dataMap());
    }
}

void oled::Window::flash()
{
    OLED_D("flashTag pages size%d", this->pages().size());

    if (!this->m_pages.empty())
    {
        auto page = this->pages().at(this->m_nowPage);
        page->flash();
        //        this->getOledDevice()->flash(page->dataMap());
    }
    else
    {
        OLED_W("page is empty!");
    }
}

void oled::Window::deletePage(const uint8_t index)
{
    auto page = this->pages().at(index);

    if (page != nullptr)
    {
        // remove
        std::remove(this->pages().begin(), this->pages().end(), page);
    }
}

void oled::Window::pushEvent(const Event& event)
{
    m_eventQueue.push(event);
}

void oled::Window::eventDispatch()
{
    if (!m_eventQueue.empty())
    {
        auto event = m_eventQueue.front();
        m_eventQueue.pop();
        auto page = this->pages().at(this->m_nowPage);

        for (auto& layout : page->layouts())
        {
            layout->sendEvent(event);
        }
    }
}
