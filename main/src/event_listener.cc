#include "event_listener.h"

bool oled::EventListener::operator*()
{
    if (m_eventHandler)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void oled::EventListener::handler(oled::Event event)
{
    m_eventHandler(event);
}

oled::EventListener::EventListener() : m_eventHandler()
{
}

oled::EventListener::EventListener(oled::EventHandler&& handler)
{
    m_eventHandler = handler;
}
