//
// Created by monoliths on 8/21/22.
//

#include "absolutely_layout.h"
#include "page.h"

std::pair<oled::Widget *, oled::Position> oled::AbsolutelyLayout::addWidget(
    oled::Widget *pWidget,
    oled::Position &&point)
{
    if (checkInArea(point, pWidget))
    {
        m_objects.emplace(std::make_pair(point, pWidget));
    }
    return std::make_pair(pWidget, point);
}

void oled::AbsolutelyLayout::removeWidget(oled::Widget *pWidget)
{
    for (auto c = m_objects.begin(); c != m_objects.end(); c++)
    {
        if (c->second == pWidget)
        {
            m_objects.erase(c);
            break;
        }
    }
}

oled::AbsolutelyLayout::AbsolutelyLayout() : m_objects()
{
    m_pPage = nullptr;
}

void oled::AbsolutelyLayout::setPage(oled::Page *pPage)
{
    Layout::setPage(pPage);

    for (auto object : this->m_objects)
    {
        // ergodic widget and point to flash
        object.second->setPage(pPage);
    }
}

std::vector<std::pair<oled::Point, oled::Widget *>>
    oled::AbsolutelyLayout::getCheckedAreaWidget()
{
    std::vector<std::pair<oled::Point, oled::Widget *>> result;

    for (auto &object : this->m_objects)
    {
        if (checkInArea(object.first, object.second))
        {
            result.push_back(object);
        }
    }

    // expiring value
    return result;
};
void oled::AbsolutelyLayout::flash()
{
    for (auto object : this->m_objects)
    {
        // check position
        if (checkInArea(object.first, object.second))
        {
            object.second->flash(this->m_pPage->dataMap(), object.first);
        }
    }
}

void oled::AbsolutelyLayout::flash(const oled::Widget *pWidget)
{
    for (auto object : this->m_objects)
    {
        if (pWidget == object.second)
        {
            object.second->flash(this->m_pPage->dataMap(), object.first);
        }
    }
}

void oled::AbsolutelyLayout::update()
{
    for (auto object : this->m_objects)
    {
        // check position
        if (checkInArea(object.first, object.second))
        {
            object.second->update(this->m_pPage->dataMap(), object.first);
        }
    }
}

// void oled::AbsolutelyLayout::sendEvent(oled::Event event)
// {
//     for (auto object : this->m_objects)
//     {
//         object.second->sendEvent(event);
//     }
// }

oled::Position oled::AbsolutelyLayout::getPosition(const oled::Widget *pWidget)
{
    if (pWidget == m_objects.end()->second)
    {
        return m_objects.end()->first;
    }
    else
    {
        return std::find_if(m_objects.begin(),
                            m_objects.end(),
                            [&](const std::pair<const Position, Widget *> &data)
                                -> bool { return (data.second == pWidget); })
            ->first;
    }
}

// void oled::Layout::flash()
//{
//     for (auto compose : this->m_compose)
//     {
//         compose.first->flash(this->m_pPage->dataMap(), compose.second);
//     }
// }
//
// void oled::Layout::flash(const oled::Widget *pWidget)
//{
//     //    ESP_ERROR_CHECK(this->m_compose.size() !=
//     this->m_positions.size()); for (auto compose : this->m_compose)
//     {
//         if (pWidget == compose.first)
//         {
//             compose.first->flash(this->m_pPage->dataMap(), compose.second);
//         }
//     }
// }