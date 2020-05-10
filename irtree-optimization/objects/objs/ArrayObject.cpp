

#include "ArrayObject.h"
#include "VariableObject.h"
void ArrayObject::SetValue(int value) {
  throw std::runtime_error("Can't set value to Array object");
}
int ArrayObject::GetValue() {
  throw std::runtime_error("Can't get 'int' value from Array object");
}
std::unordered_map<Symbol, Object *> ArrayObject::GetFields() {
  throw std::runtime_error("Can't get fields from Array Object");
}

void ArrayObject::SetValue(Object *object) {
  auto array = dynamic_cast<ArrayObject *>(object);
  this->Resize(array->GetSize());
  for (size_t i = 0; i < buffer_.size(); ++i) {
    buffer_[i]->SetValue(array->buffer_[i]);
  }
}

PrimitiveSimpleType *ArrayObject::GetElementType() {
  return element_type_;
}

Object *ArrayObject::AtIndex(size_t index) {
  if (index >= buffer_.size()) {
    throw std::runtime_error("Index out of bounds");
  } else {
    return buffer_[index];
  }
}
void ArrayObject::SetAtIndex(Object *value, size_t index) {
  if (value->GetType()->GetTypeName() != this->GetElementType()->GetTypeName()) {
    throw std::runtime_error("Trying to set value of another type");
  } else if (index >= buffer_.size()) {
    throw std::runtime_error("Index out of bounds");
  } else {
    buffer_[index] = value;
  }
}
ArrayObject::ArrayObject(PrimitiveArrayType *array_type) : type_(array_type), element_type_(array_type->GetSimpleType()) {
}
PrimitiveArrayType *ArrayObject::GetType() {
  return type_;
}
void ArrayObject::Resize(size_t size) {
  buffer_.clear();
  for (size_t i = 0;i < size; ++i) {
    buffer_.push_back(new VariableObject(element_type_));
  }
}
int ArrayObject::GetSize() {
  return buffer_.size();
}


