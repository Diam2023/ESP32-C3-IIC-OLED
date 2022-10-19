#include "window.h"
#include "esp_log.h"
#include "page.h"

oled::Window::Window(oled::OledDevice* device_)
{
    this->device.reset(device_);
}

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

void oled::Window::addPage(Page* page_)
{
    if (page_ != nullptr)
    {
        this->pages().push_back(page_);
    } else {
        ESP_LOGD("Debug", "debug message");
        ESP_LOGI(getObjectNameCStyle(), "info message");
        OLED_D("Try To add a nullptr to pages");
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
    if (!this->m_pages.empty())
    {
        auto page = this->pages().at(this->m_nowPage);
        this->getOledDevice()->flash(page->dataMap());
    } else {
        OLED_D("page is empty!");
    }
}

void oled::Window::flash(Page* page)
{
    if (this->pages().at(this->m_nowPage) == page)
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
        this->getOledDevice()->flash(page->dataMap());
    } else {
        OLED_D("page is empty!");
    }
}

// oled::Page* oled::Window::newPage()
// {
//     OledDevice* device = this->getOledDevice();

//     if (device == nullptr)
//     {
//         ESP_LOGI("Page", "oled_device error");
//     }
//     else
//     {
//         ESP_LOGI("Page", "oled_device pased");
//     }

//     Page* page = new Page(device);

//     if (device == nullptr)
//     {
//         ESP_LOGI("Page", "page error");
//     }
//     else
//     {
//         ESP_LOGI("Page", "page pased");
//     }
//     this->addPage(page);

//     return page;
// }

// void deletePage(const uint8_t)
// {

// }
