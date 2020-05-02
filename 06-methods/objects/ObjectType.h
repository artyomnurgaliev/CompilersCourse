#pragma once
#include <string>

class ObjectType {
 public:
    virtual ~ObjectType() = default;
    virtual std::string GetTypeName() = 0;
};