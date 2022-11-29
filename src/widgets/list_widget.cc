//
// Created by monoliths on 8/28/22.
//

#include "list_widget.h"
#include "esp_err.h"

oled::Model<std::vector<std::string>>* oled::ListWidget::model()
{
    return dynamic_cast<oled::Model<std::vector<std::string>>*>(this->m_pModel);
}

void oled::ListWidget::addText(std::string&& text_)
{
    ESP_ERROR_CHECK(model() == nullptr);
    model()->data().push_back(std::move(text_));
}

void oled::ListWidget::eraseText(std::string&& text_)
{
    auto dataList = model()->data();
    auto findResult = std::find(dataList.begin(), dataList.end(), text_);
    if (findResult != dataList.end())
    {
        dataList.erase(findResult);
    }
}

void oled::ListWidget::clear()
{
    model()->data().clear();
}

// void oled::ListWidget::modelUpdated()
//{
//     Widget::modelUpdated();
// }
