#pragma once

#include <memory>
#include <queue>
#include <vector>

#include "page.h"
#include "types.h"
#include "oled_device.h"
#include "object.h"
#include "animation.h"

namespace oled
{

class Window : public Object
{
    OLED_OBJECT

protected:
    // 目前两种方案
    /**
     * 1.传入指针 使用智能指针传入
     * 2.使用移动构造函数
     */
    std::shared_ptr<OledDevice> device;

    // pages
    std::vector<Page*> m_pages;

    // /**
    //  * Event QueueFor Data
    //  */
    // std::queue<Event> m_eventQueue;

    /**
     * Page Index
     */
    uint8_t m_nowPage{0};

public:
    /**
     * Push Event To Queue For Widget handler.
     * @param event
     */
    void pushEvent(const Event& event);

    // /**
    //  * New Task For Dispatch Event.
    //  */
    // void eventDispatch();

    /**
     * 获取page的副本
     * @return
     */
    std::vector<Page*>& pages()
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

    // uint8_t indexOfPage(const Page&);

    Page* createPage();

    void show();

    void flash();

    explicit Window(OledDevice*);

    ~Window() override = default;

    void addPage(Page* pPage);
    void flash(const Page* page);
};

}    // namespace oled
