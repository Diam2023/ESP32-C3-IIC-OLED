//
// Created by monoliths on 8/21/22.
//

#ifndef ESP32_C3_IIC_OLED_OBJECT_H
#define ESP32_C3_IIC_OLED_OBJECT_H

#include <string>
#include <regex>
#include "esp_log.h"
#include "types.h"

namespace oled
{

#define OLED_D(format, ...)                          \
    ESP_LOG_LEVEL_LOCAL(ESP_LOG_DEBUG,               \
                        this->getObjectNameCStyle(), \
                        format,                      \
                        ##__VA_ARGS__);
#define OLED_I(format, ...)                          \
    ESP_LOG_LEVEL_LOCAL(ESP_LOG_INFO,                \
                        this->getObjectNameCStyle(), \
                        format,                      \
                        ##__VA_ARGS__)

#define CLASS_INFO                                      \
    virtual std::string __className()                   \
    {                                                   \
        std::string nameBuffer(__PRETTY_FUNCTION__);    \
        std::smatch result;                             \
        std::regex pattern("(\\w+)::");                 \
        std::regex_search(nameBuffer, result, pattern); \
        return result[1];                               \
    }

#define OLED_OBJECT CLASS_INFO

class Object
{
    OLED_OBJECT;

private:
    std::string m_ObjectName;

public:
    Object();

    ~Object() = default;

    const std::string&& getObjectName() const;
    const char* getObjectNameCStyle() const;

    // call move construction
    void setObjectName(const std::string&&);
};

}    // namespace oled

#endif    // ESP32_C3_IIC_OLED_OBJECT_H
