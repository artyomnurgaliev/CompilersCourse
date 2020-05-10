#pragma once
#include <vector>
#include <objects/PrimitiveArrayType.h>
#include "Object.h"
class ArrayObject : public Object {
 public:
  ArrayObject(PrimitiveArrayType* array_type);
  void SetValue(int value) override;
  void SetValue(Object *object) override;
  int GetValue() override;

  PrimitiveArrayType *GetType() override;
  PrimitiveSimpleType *GetElementType();
  void SetAtIndex(Object *value, size_t index);
  Object *AtIndex(size_t index);
  std::unordered_map<Symbol, Object *> GetFields() override;
  void Resize(size_t size) ;
  int GetSize();
 private:
  PrimitiveArrayType *type_;
  PrimitiveSimpleType *element_type_;
  std::vector<Object *> buffer_;
};

