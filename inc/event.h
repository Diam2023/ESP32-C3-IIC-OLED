//
// Created by monoliths on 11/22/22.
//

#ifndef ESP32_C3_IIC_OLED_EVENT_H
#define ESP32_C3_IIC_OLED_EVENT_H

template <typename T>
class Event
{


protected:
    T m_EventType;

    static int m_typeId;

    /**
     * Get EventType For Event
     * @return
     */
    T getEventType()
    {
        return m_EventType;
    }

    /**
     * Get Event Unique Id
     * @return unique id
     */
    int getEventId();

public:
    Event();
    ~Event();
};

#endif    // ESP32_C3_IIC_OLED_EVENT_H
