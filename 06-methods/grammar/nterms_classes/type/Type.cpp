
#include "Type.h"

Type::Type(SimpleType *simple_type) : simple_type_(simple_type), is_simple_type_(true) {}
Type::Type(ArrayType *array_type) : array_type_(array_type), is_simple_type_(false) {}
void Type::Accept(Visitor *visitor) { visitor->Visit(this); }
SimpleType *Type::GetSimpleType() const { return simple_type_; }
void Type::SetSimpleType(SimpleType *simple_type) {
  simple_type_ = simple_type;
}
ArrayType *Type::GetArrayType() const { return array_type_; }
void Type::SetArrayType(ArrayType *array_type) { array_type_ = array_type; }
bool Type::IsSimpleType() const { return is_simple_type_; }
void Type::SetIsSimpleType(bool is_simple_type) {
  Type::is_simple_type_ = is_simple_type;
}
