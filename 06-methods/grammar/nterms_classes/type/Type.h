#pragma once
#include <string>
#include <base_elements/BaseElement.h>
#include <nterms_classes/type/SimpleType.h>
#include <nterms_classes/type/ArrayType.h>
class Type : public BaseElement{
public:
  explicit Type(SimpleType* simple_type);
  explicit Type(ArrayType* array_type);
  void Accept(Visitor* visitor) override ;
  SimpleType *GetSimpleType() const;
  void SetSimpleType(SimpleType *simple_type);
  ArrayType *GetArrayType() const;
  void SetArrayType(ArrayType *array_type);
  bool IsSimpleType() const;
  void SetIsSimpleType(bool is_simple_type);
  std::string GetType();

private:
  SimpleType* simple_type_ = nullptr;
  ArrayType* array_type_ = nullptr;
  bool is_simple_type_ = true;
};

