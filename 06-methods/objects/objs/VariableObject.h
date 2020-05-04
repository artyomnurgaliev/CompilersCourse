#pragma once
#include <objects/PrimitiveSimpleType.h>
#include "Object.h"
class VariableObject : public Object{
 public:
  explicit VariableObject(PrimitiveSimpleType* type);
  VariableObject(PrimitiveSimpleType* type, int value);
  void SetValue(int value) override;
  void SetValue(Object* object) override;
  int GetValue() override;

  PrimitiveSimpleType* GetType() override;
  std::unordered_map<Symbol, Object*> GetFields() override;

 private:
  PrimitiveSimpleType* type_;
  int value_ = 0;
  std::unordered_map<Symbol, Object*> fields_;
};


