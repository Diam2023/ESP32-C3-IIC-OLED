//
// Created by monoliths on 8/21/22.
//

#ifndef ESP32_C3_IIC_OLED_ABSOLUTELY_LAYOUT_H
#define ESP32_C3_IIC_OLED_ABSOLUTELY_LAYOUT_H

#include "layout.h"
#include <unordered_map>

namespace oled
{

class AbsolutelyLayout : public Layout
{
private:
    /**
     * Use Unordered Multi Map For Save Point And Widget
     */
    std::unordered_multimap<Position, Widget*> m_objects;

public:
    /**
     * Save Page For Widget And Self.
     * @param pPage Page For Data.
     */
    void setPage(Page* pPage) override;

    /**
     * Flash Widgets Data For Page
     */
    void flash() override;

    /**
     * Only Flash Widget
     * @param pWidget
     */
    void flash(const Widget* pWidget) override;

    void update() override;

    void sendEvent(oled::Event event) override;

    Position getPosition(const Widget *pWidget) override;

    /**
     * Add The Widget In Position pPoint
     * @param pWidget widget
     * @param pPoint position
     */
    std::pair<Widget*, Position> addWidget(Widget* pWidget, Position&& position);

    /**
     * Remove Widget From Layout Container.
     * @param pWidget widget
     */
    void removeWidget(Widget* pWidget);

    AbsolutelyLayout();
    explicit AbsolutelyLayout(Page* pPage) : Layout(pPage), m_objects(){};

    explicit AbsolutelyLayout(Page* pPage, Position position, Size size)
        : Layout(pPage, std::move(position), size) {};

    ~AbsolutelyLayout() override = default;
    ;
};

}    // namespace oled

#endif    // ESP32_C3_IIC_OLED_ABSOLUTELY_LAYOUT_H
