#pragma once

#include "object.h"
#include "widget.h"
#include "oled_device.h"
#include "types.h"
#include "data_map.h"
#include "esp_log.h"
#include "layout.h"

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

public:

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
