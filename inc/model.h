#ifndef ESP32_C3_IIC_OLED_INC_MODEL_H_
#define ESP32_C3_IIC_OLED_INC_MODEL_H_

#include "object.h"
#include <vector>
#include "widget.h"

namespace oled
{

/**
 * Abstract Model
 */
template <typename T>
class Model : public Object
{
    MODEL_MEMBERS

protected:
    oled::Widget* m_pWidget = nullptr;

    T m_data{};

public:
    void bindWidget(oled::Widget* widget_)
    {
        this->m_pWidget = widget_;
    };

    oled::Widget* widget()
    {
        return this->widget();
    };

    virtual T&& data()
    {
        return std::move(m_data);
    }

    virtual void setData(const T& data_)
    {
        this->m_data = data_;
    };

    /**
     * It will call page modelUpdated
     * @param data_
     */
    virtual void updateData(const T& data_)
    {
        this->m_data = data_;
        if (this->m_pWidget != nullptr)
        {
            this->m_pWidget->modelUpdated();
        }
        else
        {
            OLED_I("widget null");
        }
    };

    explicit Model(oled::Widget* widget_) : m_pWidget(widget_){};
    Model() : m_pWidget(nullptr){};
    ~Model() = default;
};

}    // namespace oled

#endif    // ESP32_C3_IIC_OLED_INC_MODEL_H_
