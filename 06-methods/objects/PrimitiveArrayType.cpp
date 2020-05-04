#include "PrimitiveArrayType.h"
PrimitiveArrayType::PrimitiveArrayType(ArrayType *type)
  : simple_type_(new PrimitiveSimpleType(type->GetSimpleType())) {
}

std::string PrimitiveArrayType::GetTypeName() {
  return "Array of" + simple_type_->GetTypeName();
}
PrimitiveSimpleType* PrimitiveArrayType::GetSimpleType() {
  return simple_type_;
}
bool PrimitiveArrayType::IsArray() {
  return true;
}
PrimitiveArrayType::PrimitiveArrayType(PrimitiveSimpleType *primitive_type): simple_type_(primitive_type) {

}
