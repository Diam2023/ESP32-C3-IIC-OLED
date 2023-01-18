//
// Created by monoliths on 8/22/22.
//

#include "widget.h"

using namespace oled;

void oled::Widget::setPage(oled::Page* pPage)
{
    m_pPage = pPage;
}

oled::Page* oled::Widget::page()
{
    return m_pPage;
}

// template <typename T>
// void Widget::bindModel(const Model<T>* pModel)
//{
//     this->m_pModel =
//         reinterpret_cast<Model<Object>*>(const_cast<Model<Object>*>(pModel));
// }

template <typename T>
Model<T>* Widget::getModel()
{
    return reinterpret_cast<Model<T>*>(m_pModel);
}

// template <typename T>
// void Widget::bindModel(const Model<T>* const pModel)
//{
//     this->m_pModel =
//         reinterpret_cast<Model<Object>*>(const_cast<Model<Object>*>(pModel));
// }

// template <typename T>
// void Widget::bindModel(Model<T>* pModel)
//{
//     this->m_pModel = reinterpret_cast<Model<Object>*>(pModel);
//     //    this->m_pModel = pModel;
// }

void Widget::bindModel(Model<Object>* pModel)
{
    this->m_pModel = reinterpret_cast<Model<Object>*>(pModel);
}

void Widget::addEventListener(const EventListener& eventListener)
{
    m_eventListener = eventListener;
}

void Widget::sendEvent(oled::Event event)
{
    if (*m_eventListener)
    {
        m_eventListener.handler(event);
    }
}
