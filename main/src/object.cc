//
// Created by monoliths on 8/21/22.
//

#include "object.h"

const std::string&& oled::Object::getObjectName() const
{
    return std::move(this->m_ObjectName);
}

const char* oled::Object::getObjectNameCStyle() const
{
    return this->m_ObjectName.c_str();
}

void oled::Object::setObjectName(const std::string&& objectName_)
{
    this->m_ObjectName = objectName_;
}

oled::Object::Object()
{
    m_ObjectName = __className();
}
