#include <method-mechanisms/ClassStorage.h>
#include "VariableObject.h"
#include "ArrayObject.h"
VariableObject::VariableObject(PrimitiveSimpleType *type) : type_(type) {
  if (type_->IsClass()) {
    auto fields = ClassStorage::GetInstance().GetFields(Symbol(type_->type_->GetSimpleTypeIdentifier()));
    for (const auto& field: fields) {
      if (field.second->IsArray()) {
        fields_[field.first] = new ArrayObject((PrimitiveArrayType*)field.second.get());
      } else {
        fields_[field.first] = new VariableObject((PrimitiveSimpleType*)field.second.get());
      }
    }
  } else {
    value_ = 0;
  }
}
VariableObject::VariableObject(PrimitiveSimpleType *type, int value) : type_(type) {
  if (type_->IsClass()) {
    throw std::runtime_error("Trying to set 'int' value to Class object");
  } else {
    value_ = value;
  }
}
void VariableObject::SetValue(int value) {
  if (type_->IsClass()) {
    throw std::runtime_error("Trying to set 'int' value to Class object");
  } else {
    value_ = value;
  }
}
void VariableObject::SetValue(Object *object) {
  if ((PrimitiveSimpleType*)object->GetType() == this->GetType()) {
    type_ = (PrimitiveSimpleType *) object->GetType();
  } else {
    throw std::runtime_error("Different types");
  }
  value_ = object->GetValue();
  fields_ = std::move(object->GetFields());
}
int VariableObject::GetValue() {
  if (type_->IsClass()) {
    throw std::runtime_error("Trying to get 'int' value from Class object");
  }
  return value_;
}
std::unordered_map<Symbol, Object *> VariableObject::GetFields() {
  return fields_;
}
PrimitiveSimpleType *VariableObject::GetType() {
  return type_;
}
