#ifndef ESP32_C3_IIC_OLED_INC_WIDGET_H_
#define ESP32_C3_IIC_OLED_INC_WIDGET_H_

#include "object.h"
#include "data_map.h"
#include "paint.h"

// #include "event_listener.h"

namespace oled
{

class Layout;
class Page;
class Animation;

template <typename M>
class Model;

/**
 * Abstract Widget
 */
class Widget : public Object
{
    OLED_OBJECT
protected:
    // Widget Model
    Model<Object>* m_pModel = nullptr;

    Page* m_pPage = nullptr;

    bool m_visible = true;

    // /**
    //  * Event Listener For Widget.
    //  */
    // oled::EventListener m_eventListener;

    /**
     * updateFlag for update
     */
    bool m_upDateFlag = false;

public:
    /**
     * module For Data
     * @tparam T
     * @return
     */
    template <typename T>
    Model<T>* getModel();

    // /**
    //  * Event Listener For Widget
    //  * @param eventListener
    //  */
    // void addEventListener(const EventListener& eventListener);

    // /**
    //  * Send Event To Handler It
    //  * @param event Event For Listener
    //  */
    // void sendEvent(oled::Event event);

    //    template <typename T>
    //    void bindModel(const Model<T>*);

    //    template <typename T>
    //    void bindModel(Model<T>* const);

    void bindAnimation(oled::Animation* animation);

    /**
     * Bind Animaiton To Widget And Add To Page
     * @param animation Animation For Page
     */
    void bindAnimation(oled::Animation&& animation);

    /**
     * bind Animation To Page
     * @param animation Animation Argument
     */
    void bindAnimation(const oled::Animation& animation);

    //    template <typename T>
    //    void bindModel(Model<T>*);
    void bindModel(Model<Object>*);

    void setPage(Page*);

    void setUpdateFlag(bool flag)
    {
        m_upDateFlag = flag;
    };

    void setVisible(bool visible)
    {
        m_visible = visible;
    };

    bool visible() const
    {
        return m_visible;
    };

    bool updateFlag() const
    {
        return m_upDateFlag;
    }

    Page* page();

    /**
     * Call By Model.
     *
     * setUpdate Flag For true , It mean Is Widget Flashed When System Call
     * update() function.
     */
    void modelUpdated()
    {
        setUpdateFlag(true);
    };

    virtual void flash(DataMap*, const Point&){};

    void update(DataMap* pDataMap, const Point& point)
    {
        if (m_upDateFlag)
        {
            flash(pDataMap, point);
            m_upDateFlag = !m_upDateFlag;
        }
    };

    // TODO To Add Widget And Height Calculator For Derived Classes
    virtual uint8_t getWidth()
    {
        return 0;
    };

    virtual uint8_t getHeight()
    {
        return 0;
    };

    virtual Size getSize()
    {
        return {getWidth(), getHeight()};
    };

    virtual Rectangle getArea()
    {
        return {};
    };

    Widget() = default;

    template <typename T>
    explicit Widget(Model<T>* pModel, Page* pPage)
        : m_pModel(reinterpret_cast<Model<Object>*>(pModel)), m_pPage(pPage){};

    ~Widget() override = default;
};

}    // namespace oled

#endif    // ESP32_C3_IIC_OLED_INC_WIDGET_H_
