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
    }
#ifdef DEBUG
    else
    {
        ESP_LOGD("Debug", "debug message");
        ESP_LOGI(getObjectNameCStyle(), "info message");
        OLED_D("Try To add a nullptr to pages");
    }
#endif
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
    if (!this->m_pages.empty())
    {
        auto page = this->pages().at(this->m_nowPage);
        page->flash();
        //        this->getOledDevice()->flash(page->dataMap());
    }
#ifdef DEBUG

    else
    {
        OLED_D("page is empty!");
    }
#endif
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
    if (!this->m_pages.empty())
    {
        auto page = this->pages().at(this->m_nowPage);
        page->flash();
        //        this->getOledDevice()->flash(page->dataMap());
    }
#ifdef DEBUG
    else
    {
        OLED_D("page is empty!");
    }
#endif
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
