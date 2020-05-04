#pragma once
#include <objects/ObjectType.h>
#include <symbol_table/Symbol.h>
#include <objects/PrimitiveType.h>
class Object {
 public:
  virtual void SetValue(int value) = 0;
  virtual void SetValue(Object* object) = 0;
  virtual int GetValue() = 0;
  virtual PrimitiveType* GetType() = 0;
  virtual std::unordered_map<Symbol, Object*> GetFields() = 0;
};


