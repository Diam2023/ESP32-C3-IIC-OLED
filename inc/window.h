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
    // TODO Add event Pool Class to handle event
    //    std::vector<oled::EVENT> eventQueue;
    //    std::map<std::string, std::function<void*(void*)>> event;

    // 目前两种方案
    /**
     * 1.传入指针 使用智能指针传入
     * 2.使用移动构造函数
     */
    std::shared_ptr<OledDevice> device;

    // pages
    std::vector<Page*> m_pages;

    uint8_t m_nowPage{0};

public:
    /**
     * 获取page的副本
     * @return
     */
    std::vector<Page*> &pages()
    {
        return this->m_pages;
    }

    /**
     * 隐式内联
     * @return OledDevice Pointer
     */
    OledDevice* getOledDevice() const
    {
        return device.get();
    }

    /**
     * 隐式内联
     * @param pDevice
     */
    void setOledDevice(OledDevice* pDevice)
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
