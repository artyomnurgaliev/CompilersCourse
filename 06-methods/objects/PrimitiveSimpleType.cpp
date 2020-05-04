#include <stdexcept>
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
