#ifndef ESP32_C3_IIC_OLED_INC_WIDGET_H_
#define ESP32_C3_IIC_OLED_INC_WIDGET_H_

#include "object.h"
#include "data_map.h"
#include "paint.h"
#include <memory>

namespace oled
{

class Layout;
class Page;

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

public:
    template <typename T>
    Model<T>* getModel();

    //    template <typename T>
    //    void bindModel(const Model<T>*);

    //    template <typename T>
    //    void bindModel(Model<T>* const);

    //    template <typename T>
    //    void bindModel(Model<T>*);
    void bindModel(Model<Object>*);

    void setPage(Page*);

    Page* page();

    /**
     * Call By Model.
     */
    virtual void modelUpdated(){};

    virtual void flash(DataMap*, const Point&){};

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
