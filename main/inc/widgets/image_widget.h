//
// Created by monoliths on 10/24/22.
//

#ifndef ESP32_C3_IIC_OLED_IMAGE_WIDGET_H
#define ESP32_C3_IIC_OLED_IMAGE_WIDGET_H

#include "widget.h"
#include "model.h"

namespace oled {

    /**
     * Image Widget To Show Image
     */
    class ImageWidget : public Widget {
    private:
        OLED_IMAGE_SIZE m_imageSize;

    public:
        void setImageSize(OLED_IMAGE_SIZE imageSize);

        void setModel(Model<uint32_t> *);

        Model<uint32_t> *model();

        void setIndex(uint32_t index);

        void updateIndex(uint32_t index);

        uint32_t index();

        void flash(DataMap *, const Point &) override;

        void modelUpdated() override;

        explicit ImageWidget(uint32_t index, OLED_IMAGE_SIZE imageSize = OLED_IMAGE_SIZE_8);

        explicit ImageWidget(uint32_t index, Page *, OLED_IMAGE_SIZE imageSize = OLED_IMAGE_SIZE_8);

        explicit ImageWidget(uint32_t index, Object *, Page *, OLED_IMAGE_SIZE imageSize = OLED_IMAGE_SIZE_8);

        explicit ImageWidget(Object *model, Page *page) : Widget(model, page), m_imageSize(OLED_IMAGE_SIZE_8) {};

        ImageWidget();

        ~ImageWidget() = default;
    };

};
#endif //ESP32_C3_IIC_OLED_IMAGE_WIDGET_H
