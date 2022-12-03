//
// Created by monoliths on 11/22/22.
//

#ifndef ESP32_C3_IIC_OLED_EVENT_LISTENER_H
#define ESP32_C3_IIC_OLED_EVENT_LISTENER_H

#include "types.h"

namespace oled
{

class EventListener
{
protected:
    EventHandler m_eventHandler;

public:
    void handler(Event event);

    bool operator*();

    EventListener();

    explicit EventListener(oled::EventHandler&& handler);

    ~EventListener() = default;
};

};    // namespace oled

#endif    // ESP32_C3_IIC_OLED_EVENT_LISTENER_H
