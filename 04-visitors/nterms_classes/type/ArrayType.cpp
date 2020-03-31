

#include "ArrayType.h"
ArrayType::ArrayType(SimpleType *simple_type) : simple_type_(simple_type) {}
void ArrayType::Accept(Visitor *visitor) { visitor->Visit(this); }
SimpleType *ArrayType::GetSimpleType() const { return simple_type_; }
void ArrayType::SetSimpleType(SimpleType *simple_type) {
  simple_type_ = simple_type;
}
