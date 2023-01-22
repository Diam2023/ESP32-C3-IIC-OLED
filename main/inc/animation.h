//
// Created by monoliths on 11/27/22.
//
// Feature: use global player Queue, new A Task to complete

#ifndef ESP32_C3_IIC_OLED_ANIMATION_H
#define ESP32_C3_IIC_OLED_ANIMATION_H

#include <utility>
#include "object.h"

namespace oled
{

class Widget;

// AnimationPool --Entry--> AnimationExecutor --Exe--> Animation

/**
 * Animation Status For Running
 */
enum AnimationStatus
{
    READY,        // ready status
    RUNNING,      // running status
    TERMINATED    // die status
};

/**
 * Animation Class, This Class For Widget It Will Running With Flash Thread.
 * Animation Created With Flag Ready status,
 *  when Call Animation::go() Function then change to Running Status.
 * In The Running Status It can Running Once Animation CallBack With Rate.
 * When Animation::end() Called By CallBack Method Or Any Function/Instance
 * Method, The Animation Will Going To Die, And This Instance Will Removed From
 * Window Animation Queue By The System When Next AGC Time;
 */
class Animation : public Object
{
protected:
    /**
     * Status Flag For Animation
     */
    AnimationStatus m_animationStatus;

    /**
     * Run One Timer Based On Flash Task
     */
    uint16_t m_runTimeRate{};

    /**
     * Counter For Timer Running
     */
    uint16_t m_counter{0};

    /**
     * Bind Widget
     */
    Widget *m_pWidget{nullptr};

    /**
     * Animation Callback
     */
    std::function<void(Animation *)> m_callback;

public:
    Animation()
    = default;

    /**
     * Copy Construction
     * @param Another animation
     */
    Animation(const Animation &animation)
     : Object(animation) {
        m_animationStatus = animation.m_animationStatus;
        m_runTimeRate = animation.m_runTimeRate;
        m_counter = animation.m_counter;
        m_pWidget = animation.m_pWidget;
    };

    /**
     * Construct A Animaiton
     * @param pWidget Bind widget
     * @param callback Move construct for lambda expression
     * @param runTimeRate Run every flash()
     */
    Animation(Widget *pWidget,
              std::function<void(Animation *)> &&callback,
              int16_t runTimeRate = 1)
        : m_runTimeRate(runTimeRate), m_pWidget(pWidget), m_callback(callback)
    {
        m_animationStatus = AnimationStatus::READY;
    };

    /**
     * For Fast Initialize Animation For function
     * @param callback
     * @param runTimeRate
     */
    explicit Animation(std::function<void(Animation *)> &&
                           callback,    // move construct for lambda expression
                       int16_t runTimeRate = 1    // run every flash()
                       )
        : m_runTimeRate(runTimeRate), m_callback(callback)
    {
        m_animationStatus = AnimationStatus::READY;
    };

    friend bool operator<(const oled::Animation& a, const oled::Animation& b)
    {
        return a.m_animationStatus >= b.m_animationStatus;
    }

    /**
     * Set Widget For Animation
     * @param pWidget Widget pointer
     */
    void setWidget(Widget *pWidget)
    {
        m_pWidget = pWidget;
    };

    /**
     * get Bound Widget
     * @return Widget Pointer
     */
    Widget *widget()
    {
        return this->m_pWidget;
    };

    /**
     * return Run Time Rate
     * @return uint16_t type of rate
     */
    uint16_t runTimeRate() const
    {
        return m_runTimeRate;
    };

    /**
     * Get The Status Of Animation
     * @return Status
     */
    AnimationStatus status()
    {
        return m_animationStatus;
    };

    /**
     * Change Status To Running
     */
    void go()
    {
        m_animationStatus = AnimationStatus::RUNNING;
    };

    /**
     * Change Status To TERMINATED
     */
    void end()
    {
        m_animationStatus = AnimationStatus::TERMINATED;
    };

    /**
     * Run once Animation Frame
     */
    void run()
    {
        OLED_D("Timer Running!");
        m_counter++;

        /**
         * If Timer
         */
        if (m_counter >= m_runTimeRate)
        {
            // Run CallBack
            m_callback(this);

            OLED_D("Run Animation!");
        }
        else
        {
            // Clear Timer
            m_counter = 0;
        }
    };
};

};    // namespace oled

#endif    // ESP32_C3_IIC_OLED_ANIMATION_H
