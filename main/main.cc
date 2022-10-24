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

static const char *TAG_MAIN = "oled test main";

using namespace oled;

// TODO split debug code

class MyPage : public Page
{
private:
    TextWidget *m_pTestTextWidget{};
    TextWidget *m_pTest2TextWidget{};
    ImageWidget *m_pImageTextWidget{};

public:
    void updateTestText(std::string &&data);

    inline void init()
    {
        auto ly = new Layout();

        m_pTestTextWidget = new TextWidget("1", this, oled::OLED_FONT_SIZE_16);

        m_pTest2TextWidget = new TextWidget("2", this);
        m_pImageTextWidget = new ImageWidget(1, this);

        m_pTest2TextWidget->setPage(this);
        m_pTestTextWidget->setPage(this);
        m_pImageTextWidget->setPage(this);

        ly->addWidget(m_pTestTextWidget, Point(0, 1));
        ly->addWidget(m_pTest2TextWidget, Point(0, 3));
        ly->addWidget(m_pImageTextWidget, Point(30, 5));

        ly->setPage(this);

        addLayout(ly);
    };

    MyPage(OledDevice *pDevice) : Page(pDevice)
    {
        init();
    };

    MyPage(const oled::Window *pWindow) : Page(pWindow)
    {
        init();
    };

    ~MyPage(){};
};

void oled_test()
{
    auto i2c_oled = new oled::OledDevice(5, 6, true);

    esp_err_t err = i2c_oled->init(false, false);

    if (err == ESP_OK)
    {
        auto window = new oled::Window(i2c_oled);

        //        Page* page = window->createPage();
        //        Page* page2 = window->createPage();
        //        auto* textWidget = new TextWidget("Test Test", page);
        //
        //        auto* textWidget2 = new TextWidget("Test2", page2);
        //
        //        // textWidget->setPage(page);
        //
        //        auto* layout = new Layout();
        //        auto* layout2 = new Layout();
        //        layout2->addWidget(textWidget2, Point(20, 0));
        //        layout->addWidget(textWidget, Point(20, 0));
        //
        //        page->addLayout(layout);
        //        page2->addLayout(layout2);
        //
        //        page->clear();
        //        page2->clear();
        auto page = new MyPage(window);
        //        auto myPage = (MyPage*)page;
        //        page->init();

        // page->bindWindow(window);

        window->addPage(page);

        page->clear();
        window->show();
        window->flash();

        while (1)
        {
            vTaskDelay(200);

            // textWidget->updateText("Hello Monoliths");

            //            window->setPage(1);
            //            window->flash();
            //            vTaskDelay(200);
            //
            //            window->setPage(0);
            //            window->flash();
            //
            //            textWidget->updateText("Test From Oled");
            // vTaskDelay(200);
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
