#include "PrimitiveObjectType.h"

PrimitiveObjectType::PrimitiveObjectType(Type *type) : type_(type) {}
std::string PrimitiveObjectType::GetTypeName() {
  return type_->GetType();
}
