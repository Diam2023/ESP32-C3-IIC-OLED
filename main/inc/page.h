#pragma once

#include "object.h"
#include "widget.h"
#include "oled_device.h"
#include "types.h"
#include "data_map.h"
#include "esp_log.h"
#include "layout.h"
#include "animation.h"

#include <queue>
#include <functional>

namespace oled
{

class Window;

class Page : public Object
{
    OLED_OBJECT

private:
    DataMap *m_pDataMap;

    std::vector<Layout *> m_layouts;

    Window *m_pWindow{};

    /**
     * Priority AnimationQueue For Window
     */
    std::deque<oled::Animation *> m_animationQueue{};

public:
    /**
     * Push Animation To Animation Queue
     * @param animation Animation For Push Move Version
     */
    void pushAnimation(oled::Animation *pAnimation);

    /**
     * Push Animation To Animation Queue
     * @param animation Animation For Push Copy Version
     */
//    void pushAnimation(const oled::Animation &animation);

    /**
     * Get AnimationQueue For This Page
     * @return typeOf m_animationQueue Animation Queue Refer
     */
    std::deque<oled::Animation *>& getAnimationQueue()
    {
        return this->m_animationQueue;
    };

    // TODO Resolve Position!
    //    std::pair<Layout *, Position> getPosition(Widget *pWidget);

    void bindWindow(const Window *);

    Window *window();

    DataMap *dataMap();

    std::vector<Layout *> &&layouts();

    void addLayout(Layout *);

    void full(uint8_t);

    void clear();

    void flash();

    void flash(Widget *);

    void update();

    Page() : m_pDataMap(nullptr){};
    explicit Page(const OledDevice *pDevice);
    explicit Page(const Window *pWindow);

    Page(uint8_t page, uint8_t line_seg);

    ~Page() override;
};

}    // namespace oled
