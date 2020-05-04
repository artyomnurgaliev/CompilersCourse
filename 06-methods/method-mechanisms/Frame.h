#pragma once

#include <objects/MethodType.h>
#include <stack>

#include <memory>
#include <objects/objs/Object.h>
class Frame {
 public:
  explicit Frame(size_t params_size);
  void SetParams(const std::vector<Object*>& values);
  void SetFields(const std::vector<Object*>& values);

  size_t AllocVariable(PrimitiveType* primitive_type);

  void DeallocScope();
  void AllocScope();

  Object* Get(int index) const;

  void Set(int index, Object* value);

  void SetParentFrame(Frame* frame);

  Object* GetReturnValue() const;

  void SetParentReturnValue(Object* value);

  bool HasParent();
  int GetFieldsSize() const;

private:
  int params_size_ = 0;
  int fields_size_ = 0;

  std::stack<int> offsets_;
  std::vector<Object*> params_;
  std::vector<Object*> variables_;
  Object* return_value_{};

  void SetReturnValue(Object* value);

  Frame* parent_frame = nullptr;

};



