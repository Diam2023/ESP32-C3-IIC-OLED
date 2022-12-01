//
// Created by monoliths on 8/28/22.
//

#include "list_layout.h"
#include "page.h"

// void oled::ListLayout::setPage(oled::Page *)
// {
//     Layout::setPage(<unnamed>);
// }

// void oled::ListLayout::addWidget(oled::Widget *pWidget)
//{
//
////    for (auto &position : this->m_positions)
////    {
////
////    }
//
//}
void oled::ListLayout::addWidget(oled::Widget *pWidget, uint16_t space)
{
    if (m_objects.empty())
    {
        OLED_D("First");

        OLED_D("x: %d, y: %d", m_position.getX(), m_position.getY());
        m_objects.emplace_back(
            std::make_pair(oled::Position(m_position.getX(), m_position.getY()),
                           pWidget));
    }
    else
    {
        if (m_direction == oled::Direction::HORIZON)
        {
            // Horizon
            OLED_D("Horizon");
            auto last = m_objects[m_objects.size() - 1];
            auto start_x = last.first.getX() + last.second->getWidth() + space;
            if ((start_x + pWidget->getWidth()) <=          // added space
                (m_position.getX() + m_size.getWidth()))    // widget space
            {
                Position position(start_x, last.first.getY());
                m_objects.emplace_back(std::make_pair(position, pWidget));
            }
            else
            {    // next page
                auto max_height =
                    std::max_element(m_objects.begin(),
                                     m_objects.end(),
                                     [](const std::pair<Point, Widget *> &a,
                                        const std::pair<Point, Widget *> &b)
                                         -> bool {
                                         return (a.second->getHeight() <
                                                 b.second->getHeight());
                                     })
                        ->second->getHeight();
                Position position(m_position.getX(),
                                  last.first.getY() + (max_height / 8));
                m_objects.emplace_back(std::make_pair(position, pWidget));
            }
        }
        else
        {
            auto last = m_objects[m_objects.size() - 1];

            OLED_D("VERTICAL");

            OLED_D("x: %d, y: %d",
                   last.first.getX(),
                   last.first.getY() + (last.second->getHeight() / 8));

            // VERTICAL
            m_objects.emplace_back(std::make_pair(
                Position(last.first.getX(),
                         last.first.getY() + (last.second->getHeight() / 8)),
                pWidget));
        }
    }
}
std::pair<oled::Position, oled::Widget *> oled::ListLayout::getWidget(
    uint16_t index)
{
    return m_objects[index];
}

void oled::ListLayout::flash()
{
    for (auto object : this->m_objects)
    {
        // check position
        OLED_D("layout position x: %d, y: %d",
               m_position.getX(),
               m_position.getY());
        OLED_D("layout size w: %d, h: %d",
               m_size.getWidth(),
               m_size.getHeight());

        OLED_D("x: %d, y: %d", object.first.getX(), object.first.getY());

        if (checkInArea(object.first, object.second))
        {
            OLED_D("Passed!");

            object.second->flash(this->m_pPage->dataMap(), object.first);
        }
    }
}

void oled::ListLayout::flash(const oled::Widget *pWidget)
{
    for (auto object : this->m_objects)
    {
        if (pWidget == object.second)
        {
            object.second->flash(this->m_pPage->dataMap(), object.first);
        }
    }
}
