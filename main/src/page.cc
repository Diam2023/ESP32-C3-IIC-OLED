#include "page.h"

#include "window.h"

oled::Page::Page(const OledDevice *pDevice)
{
    this->m_pDataMap = new DataMap(pDevice->cm_pDeviceInfo->max_page,
                                   pDevice->cm_pDeviceInfo->max_line_seg);
}

oled::Page::Page(uint8_t page, uint8_t line_seg)
{
    this->m_pDataMap = new DataMap(page, line_seg);
}

std::vector<oled::Layout *> &&oled::Page::layouts()
{
    return std::move(this->m_layouts);
}

oled::Page::~Page()
{
    delete this->m_pDataMap;
}

void oled::Page::addLayout(Layout *pLayout)
{
    pLayout->setPage(this);
    this->m_layouts.emplace_back(pLayout);
}

oled::DataMap *oled::Page::dataMap()
{
    if (this->m_pDataMap == nullptr)
    {
        OLED_W("Return a null DataMap pointer!");
    }
    return this->m_pDataMap;
}

void oled::Page::full(uint8_t data)
{
    oled::Paint::full(dataMap(), data);
}

void oled::Page::clear()
{
    paint.clear(dataMap());
}

void oled::Page::flash()
{
    // TODO Version Fix, 2.0
    // To Separate Layout From Page Flash, As a Independence Feature
    for (auto layout : this->m_layouts)
    {
        auto widgets = layout->getCheckedAreaWidget();
        auto &animationQueue = this->getAnimationQueue();
        std::queue<Animation *> tempQueue;

        for (auto &widget : widgets)
        {
            while (!animationQueue.empty())
            {
                auto animation = animationQueue.front();
                animationQueue.pop_front();

                if (animation->widget() == widget.second)
                {
                    if (animation->status() == AnimationStatus::RUNNING)
                    {
                        // run Animation
                        animation->run();
                    }
                }
                else
                {
                    // Run Next Time Flash
                    if (animation->status() == AnimationStatus::READY)
                    {
                        animation->go();
                    }
                }

                if (animation->status() != AnimationStatus::TERMINATED)
                {
                    tempQueue.push(animation);
                }
                else
                {
                    // GC
                    if (animation->status() == AnimationStatus::TERMINATED)
                    {
                        delete animation;
                    }
                }
            }
            //     Add None Running Animation To Last
            while (!tempQueue.empty())
            {
                auto animation = tempQueue.front();

                tempQueue.pop();
                animationQueue.push_front(animation);
            }
        }

        for (auto &widget : widgets)
        {
            // Deep Flash
            widget.second->flash(this->dataMap(), widget.first);
        }
        //        layout->flash();
    }

    this->window()->flash(this);
}

void oled::Page::flash(oled::Widget *pWidget)
{
    // TODO Add flash logic To Hear
    for (auto layout : this->m_layouts)
    {
        layout->flash(pWidget);
    }

    this->window()->flash(this);
}

void oled::Page::bindWindow(const oled::Window *pWindow)
{
    this->m_pWindow = const_cast<Window *>(pWindow);

    // Fix Forget Bind DataMap.
    if (this->m_pDataMap == nullptr)
    {
        this->m_pDataMap =
            new DataMap(pWindow->getOledDevice()->cm_pDeviceInfo->max_page,
                        pWindow->getOledDevice()->cm_pDeviceInfo->max_line_seg);
    }
}

oled::Window *oled::Page::window()
{
    return this->m_pWindow;
}

oled::Page::Page(const oled::Window *pWindow)
{
    this->m_pWindow = const_cast<Window *>(pWindow);
    this->m_pDataMap =
        new DataMap(pWindow->getOledDevice()->cm_pDeviceInfo->max_page,
                    pWindow->getOledDevice()->cm_pDeviceInfo->max_line_seg);
}

void oled::Page::update()
{
    for (auto layout : this->m_layouts)
    {
        layout->update();
    }

    this->window()->flash(this);
}

// std::pair<oled::Layout *, oled::Position>
// oled::Page::getPosition(oled::Widget *pWidget)
//{
////    std::find_if(m_layouts.begin(), m_layouts.end(), [&](Layout *layout) ->
/// bool{ /        return (pWidget == layout->getPosition()) /    }); / return
/// std::make_pair()
//}

void oled::Page::pushAnimation(oled::Animation *pAnimation)
{
    this->m_animationQueue.push_front(pAnimation);
}

// void oled::Page::pushAnimation(const oled::Animation &animation)
//{
//     this->m_animationQueue.emplace_front(animation);
// }
