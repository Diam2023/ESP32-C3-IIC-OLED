#pragma once

#include <memory>
#include <vector>
#include "page.h"
#include "types.h"
#include "oled_device.h"
#include "object.h"

namespace oled
{

class Window : public Object
{
    OLED_OBJECT

private:
    // TODO Add event handler
    //    std::vector<oled::EVENT> eventQueue;

    std::shared_ptr<OledDevice> device;

    // pages
    std::vector<Page*> m_pages;

    uint8_t m_nowPage{0};

public:
    std::vector<Page*>&& pages()
    {
        return std::move(this->m_pages);
    }

    inline OledDevice* getOledDevice() const
    {
        return device.get();
    }

    inline void setOledDevice(OledDevice* pDevice)
    {
        this->device.reset(pDevice);
    }

    Page* getPage(const uint8_t index)
    {
        return this->pages().at(index);
    }

    void setPage(uint8_t);

    void deletePage(uint8_t index);

    // uint8_t indexOfPage(const Page&&);

    Page* createPage();

    void show();

    void flash();

    explicit Window(OledDevice*);

    ~Window() = default;

    void addPage(Page* pPage);
    void flash(const Page* page);
};

}    // namespace oled
