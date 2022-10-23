#ifndef ESP32_C3_IIC_OLED_INC_WIDGET_H_
#define ESP32_C3_IIC_OLED_INC_WIDGET_H_

#include "object.h"
#include "data_map.h"
#include "paint.h"
#include <memory>
// #include "model.h"

namespace oled
{

class Layout;
class Page;

/**
 * Abstract Widget
 */
class Widget : public Object
{
    OLED_OBJECT
protected:
    // Widget Model
    Object* m_pModel = nullptr;

    Page* m_pPage = nullptr;

public:
    void bindModel(const Object* pModel);

    void setPage(Page*);

    Page* page();

    /**
     * Call By Model.
     */
    virtual void modelUpdated(){};

    virtual void flash(DataMap*, const Point&){};

    Widget() = default;
    explicit Widget(Object* pModel, Page* pPage)
        : m_pModel(pModel), m_pPage(pPage){};

    ~Widget() = default;
};

}    // namespace oled

#endif    // ESP32_C3_IIC_OLED_INC_WIDGET_H_
