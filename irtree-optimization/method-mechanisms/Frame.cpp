#include <objects/objs/VariableObject.h>
#include <objects/objs/ArrayObject.h>
#include "Frame.h"
Frame::Frame(size_t params_size) {
  params_size_ = params_size;
  AllocScope();
}

void Frame::SetParams(const std::vector<Object *> &values) {
  if (values.size() != params_size_) {
    throw std::runtime_error("Mismatched number of arguments");
  }
  for (auto p: values) {
    params_.push_back(p);
  }
}
void Frame::SetFields(const std::vector<Object *> &values) {
  fields_size_ = values.size();
  for (auto p: values) {
    params_.push_back(p);
  }
}
size_t Frame::AllocVariable(PrimitiveType *primitive_type) {
  size_t index = variables_.size();
  if (primitive_type->IsArray()) {
    variables_.push_back(new ArrayObject((PrimitiveArrayType *) primitive_type));
  } else {
    variables_.push_back(new VariableObject((PrimitiveSimpleType *) primitive_type));
  }

  return index;
}

void Frame::DeallocScope() {
  size_t new_size = offsets_.top();
  offsets_.pop();

  // TODO(@akhtyamovpavel) - Call destructors
  variables_.resize(new_size);
}

void Frame::AllocScope() {
  offsets_.push(variables_.size());
}

Object *Frame::Get(int index) const {
  if (index >= 0) {
    return variables_.at(index);
  } else {
    return params_.at(-index - 1);
  }
}

void Frame::Set(int index, Object *value) {
  if (index >= 0) {
    variables_.at(index)->SetValue(value);
  } else {
    params_.at(-index - 1)->SetValue(value);
  }
}

void Frame::SetReturnValue(Object *value) {
  return_value_ = value;
}

void Frame::SetParentFrame(Frame *frame) {
  parent_frame = frame;

}

void Frame::SetParentReturnValue(Object *value) {
  parent_frame->return_value_ = value;

}

bool Frame::HasParent() {
  return parent_frame != nullptr;
}

Object *Frame::GetReturnValue() const {
  return return_value_;
}
int Frame::GetFieldsSize() const {
  return fields_size_;
}
