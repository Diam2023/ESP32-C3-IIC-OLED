/**
 * @file main.cc
 *
 * @brief test for OLED class
 *
 * @author monoliths (monoliths-uni@outlook.com)
 * @version 1.0
 * @date 2022-06-03
 *
 * *********************************************************************************
 *
 * @note version: 0.3
 *
 *
 * @description: none
 *
 * *********************************************************************************
 */
#include "esp_log.h"
#include "oled_device.h"

#include "types.h"
#include "page.h"
#include "widget.h"
#include "text_widget.h"
#include "window.h"
#include "layout.h"
#include "image_widget.h"
#include "absolutely_layout.h"
#include "graph_widget.h"

#include "graph_widget.h"
#include "list_widget.h"

static const char *TAG_MAIN = "oled test main";

using namespace oled;

// TODO split debug code

class MyPage : public Page
{
private:
    TextWidget *m_pTestTextWidget{};
    TextWidget *m_pTest2TextWidget{};
    ImageWidget *m_pImageTextWidget{};

    ImageWidget *m_pImage2TextWidget{};

public:
    void updateTestText(std::string &&data);

    void slightFire()
    {
        if (m_pImage2TextWidget->model()->data() == 4)
        {
            m_pImage2TextWidget->updateIndex(3);
        }
        else
        {
            m_pImage2TextWidget->updateIndex(4);
        }
    }

    void init()
    {
        auto ly = new ListWidget(this,
                                 oled::Direction::VERTICAL,
                                 Position(0, 0),
                                 Size(127, 7));

        m_pTestTextWidget =
            new TextWidget(ts("Just For Test"), this, oled::OLED_FONT_SIZE_16);

        m_pTest2TextWidget = new TextWidget(ts("Test Data"), this);
        m_pImageTextWidget = new ImageWidget(4, this);
        m_pImage2TextWidget =
            new ImageWidget(4, this, OLED_IMAGE_SIZE::OLED_IMAGE_SIZE_32);

        m_pTestTextWidget->addEventListener(
            EventListener([](const Event &event) -> void {
                ESP_LOGI("event", "Text1 event Handler %d", event.getEventId());
            }));

        m_pTest2TextWidget->addEventListener(
            EventListener([](const Event &event) -> void {
                ESP_LOGI("event", "Text2 event Handler %d", event.getEventId());
            }));

        //        ly->addWidget(m_pTestTextWidget, Point(0, 0));
        //        ly->addWidget(m_pTest2TextWidget, Point(60, 3));
        //        ly->addWidget(m_pImageTextWidget, Point(30, 5));
        //
        //        ly->addWidget(m_pImage2TextWidget, Point(80, 5));

        ly->addWidget(m_pTestTextWidget);
        ly->addWidget(m_pTest2TextWidget);
        ly->addWidget(m_pImageTextWidget);
        ly->addWidget(m_pImage2TextWidget);

        addLayout(ly);
    };

    MyPage(OledDevice *pDevice) : Page(pDevice){};

    MyPage(const oled::Window *pWindow) : Page(pWindow){};

    ~MyPage()
    {
        delete m_pImageTextWidget;
        delete m_pTest2TextWidget;
        delete m_pTestTextWidget;
    };
};

void testPaint(Page *mpg, OledDevice *i2c_oled)
{
    // Test Hor Line
    Paint::drawLine(
        mpg->dataMap(), Point(0, 0), Point(0, 2), Point(127, 0), Point(0, 0));

    Paint::drawLine(
        mpg->dataMap(), Point(0, 0), Point(0, 6), Point(127, 0), Point(0, 0));

    // Test Vec Line
    Paint::drawLine(
        mpg->dataMap(), Point(40, 2), Point(0, 4), Point(40, 5), Point(0, 0));

    Paint::drawLine(
        mpg->dataMap(), Point(40, 1), Point(0, 7), Point(40, 7), Point(0, 0));

    Paint::drawLine(
        mpg->dataMap(), Point(42, 1), Point(0, 5), Point(42, 7), Point(0, 0));

    //        Paint::offset(mpg->dataMap(),
    //                      0,
    //                      0,
    //                      90,
    //                      2,
    //                      20,
    //                      OLED_OFFSET_DIRECTION::OLED_OFFSET_HORIZONTAL);

    //        Paint::offset(mpg->dataMap(),
    //                      0,
    //                      0,
    //                      90,
    //                      4,
    //                      2,
    //                      OLED_OFFSET_DIRECTION::OLED_OFFSET_VERTICAL);

    //        i2c_oled->flash(mpg->dataMap());
    i2c_oled->flash(mpg->dataMap());

    //            if (l >= 10)
    //            {
    //            Paint::offsetLoop(mpg->dataMap(),
    //                              0,
    //                              0,
    //                              mpg->dataMap()->getLineSeg() - 1,
    //                              mpg->dataMap()->getPage(),
    //                              1,
    //                              OLED_OFFSET_DIRECTION::OLED_OFFSET_VERTICAL);
    //                l = 0;
    //            }
    //            else
    //            {
    //                l++;
    //            }

    //            Paint::offsetLoop(mpg->dataMap(),
    //                              0,
    //                              0,
    //                              mpg->dataMap()->getLineSeg() - 1,
    //                              mpg->dataMap()->getPage(),
    //                              5,    // 增量
    //                              OLED_OFFSET_DIRECTION::OLED_OFFSET_HORIZONTAL);
    //
    //            i2c_oled->flash(mpg->dataMap());

    //            mpg->slightFire();

    //            vTaskDelay(20);

    //            window->setPage(1);
    //            window->flash();
    //            vTaskDelay(200);
    //
    //            window->setPage(0);
    //            window->flash();
    //            //
    //            textWidget->updateText(ts("Test From Oled"));
    //            vTaskDelay(200);
}

void testPage(OledDevice *i2c_oled)
{
    auto mpg = new MyPage(i2c_oled);

    auto window = new oled::Window(i2c_oled);

    mpg->bindWindow(window);
    mpg->clear();
    window->addPage(mpg);
    mpg->init();
}

auto a = [](oled::DataMap *a, const oled::Point &b) -> void {
    // Test Hor Line
    Paint::drawLine(a, b, Point(0, 2), Point(127, 0), b);

    Paint::drawLine(a, b, Point(0, 6), Point(127, 0), b);
};

[[noreturn]] void eventLoopTask(void *arg)
{
    auto window = reinterpret_cast<Window *>(arg);
    for (;;)
    {
        window->eventDispatch();
        vTaskDelay(100);
    }
}

[[noreturn]] void oled_test()
{
    auto i2c_oled = new oled::OledDevice(5, 6, true);

    esp_err_t err = i2c_oled->init(true, false);

    if (err == ESP_OK)
    {
        ESP_LOGD("test", "new window");

        auto window = new oled::Window(i2c_oled);

        //        Page *page = window->createPage();
        //
        //        auto textWidget = new TextWidget(ts("Test Test"), page,
        //        oled::OLED_FONT_SIZE_16);
        //        //        auto text2Widget = new TextWidget(ts("Test Test2"),
        //        page);
        //
        //        auto graphWidget = new GraphWidget(
        //            [](GraphWidget *this_,
        //               oled::DataMap *a,
        //               const oled::Point &start_point) -> void {
        //                ESP_LOGD("graphWidget", "graph callback");
        //
        //                // Test Hor Line
        //                Paint::drawLine(
        //                    a, start_point, Point(0, 2), Point(127,
        //                    start_point.getY()), start_point);
        //
        //                Paint::drawLine(
        //                    a, start_point, Point(0, 6), Point(127,
        //                    start_point.getY()), start_point);
        //
        //                //                ESP_LOGD("graphWidget", "graph
        //                //                        callback");
        //            },
        //            page);
        //
        //        graphWidget->setSize({126, 8});
        //
        //        ESP_LOGD("main",
        //                 "Graph size w: %d, h: %d",
        //                 graphWidget->getWidth(),
        //                 graphWidget->getHeight());
        //
        //        auto *textWidget2 = new TextWidget(ts("Test2"), page);
        //
        //        //        auto *layout = new AbsolutelyLayout(page);
        //        auto *listLayout = new ListLayout(page,
        //        oled::Direction::HORIZON);
        //
        //        //        auto* layout2 = new AbsolutelyLayout(page2);
        //
        //        //        layout2->addWidget(textWidget2, Point(20, 0));
        //        listLayout->addWidget(textWidget);
        //        listLayout->addWidget(textWidget2, 10);
        //        listLayout->addWidget(graphWidget);
        //        //        listLayout->addWidget(text2Widget);
        //        //        ESP_LOGD("layout", );
        //        //        layout->addWidget(graphWidget, Point(0, 0));
        //        //        layout->addWidget(textWidget, Point(20, 0));
        //
        //        //        ESP_LOGD("test", "add widget");
        //
        //        page->addLayout(listLayout);
        //        //        page->addLayout(layout);
        //        //        page2->addLayout(layout2);
        //        //        ESP_LOGD("test", "add layout");
        //        //
        //        page->clear();

        auto myPage = new MyPage(window);
        window->addPage(myPage);

        myPage->clear();

        myPage->init();

        window->show();
        xTaskCreate(eventLoopTask, "eventLoopTask", 4096, window, 4, nullptr);

        window->pushEvent(Event(10));
        window->pushEvent(Event(2));
        window->pushEvent(Event(5));

        while (true)
        {
            //            vTaskDelay(20);
            vTaskDelay(10);

            myPage->slightFire();

            myPage->update();
        }

        // printf("%s buffer get: %d\n", __func__, esp_get_free_heap_size());
        // ESP_ERROR_CHECK(heap_trace_stop());
        // heap_trace_dump();
        // DataMap dataMap(i2c_oled->device_info->max_page,
        //                            i2c_oled->device_info->max_line_seg);

        // auto paint = new Paint(&dataMap);

        // paint->clear();

        // paint->writeString(20,
        //                       0,
        //                       "2022-08-15",
        //                       oled::OLED_FONT_SIZE::OLED_FONT_SIZE_16);

        // i2c_oled->flash(std::move(dataMap));

        // ESP_LOGI(TAG_MAIN, "oled init succ");

        // i2c_oled->show_string(20,
        //                       0,
        //                       "2022-06-03",
        //                       oled::OLED_FONT_SIZE::OLED_FONT_SIZE_16);
        // i2c_oled->show_string(45,
        //                       3,
        //                       "DEMO",
        //                       oled::OLED_FONT_SIZE::OLED_FONT_SIZE_16);
        // i2c_oled->show_string(23,
        //                       6,
        //                       "MONOLITHS",
        //                       oled::OLED_FONT_SIZE::OLED_FONT_SIZE_16);
        // i2c_oled->show_image(0, 0, data, 16, 32);
        // i2c_oled->show_image(105, 3, 2,
        // oled::OLED_IMAGE_SIZE::OLED_IMAGE_SIZE_32); i2c_oled->show_image(0,
        // 0, 5, oled::OLED_IMAGE_SIZE::OLED_IMAGE_SIZE_32);

        // i2c_oled->show_string(105, 7, "V0.2",
        // oled::OLED_FONT_SIZE::OLED_FONT_SIZE_6); i2c_oled->show_image(97, 7,
        // 5);
    }
    else
    {
        ESP_LOGE(TAG_MAIN, "oled init err, err code: %d", err);
    }
}

#ifdef __cplusplus
extern "C"
{
#endif

    void app_main(void)
    {
        oled_test();
    }

#ifdef __cplusplus
}
#endif
