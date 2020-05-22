#include <stdexcept>
#include <method-mechanisms/ClassStorage.h>
#include "PrimitiveSimpleType.h"

std::string PrimitiveSimpleType::GetTypeName() {
  return type_->GetSimpleTypeIdentifier();
}
bool PrimitiveSimpleType::IsClass() {
  return is_class_;
}
PrimitiveSimpleType::PrimitiveSimpleType(SimpleType *type) :type_(type){
  auto id = type_->GetSimpleTypeIdentifier();
  is_class_ = !(id == "int" || id == "boolean");
}
bool PrimitiveSimpleType::IsArray() {
  return false;
}
size_t PrimitiveSimpleType::GetSize() {
  if (!is_class_) {
    return 4;
  } else {
    auto id = type_->GetSimpleTypeIdentifier();
    auto fields = ClassStorage::GetInstance().GetFields(Symbol(id));
    size_t size = 0;
    for (const auto& field: fields) {
      size += field.second->GetSize();
    }
    return size;
  }
}
