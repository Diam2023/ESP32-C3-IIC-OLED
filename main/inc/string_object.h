//
// Created by monoliths on 11/25/22.
//

#ifndef ESP32_C3_IIC_OLED_STRING_OBJECT_H
#define ESP32_C3_IIC_OLED_STRING_OBJECT_H

#include <string>
#include "object.h"

#define ts oled::String

namespace oled
{

class String : public std::string, public Object
{
public:
    String() = default;

    explicit String(const char* string_) : std::string(string_){};
    explicit String(const std::string& string_) : std::string(string_){};
    explicit String(std::string& string_) : std::string(string_){};
    explicit String(std::string&& string_) : std::string(string_){};
};

};    // namespace oled

#endif    // ESP32_C3_IIC_OLED_STRING_OBJECT_H
