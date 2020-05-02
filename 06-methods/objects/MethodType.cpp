
#include "MethodType.h"
#include <nterms_classes/FormalList.h>

MethodType::MethodType(Type *type, FormalList *formal_list) : return_value_type_(type), formal_list_(formal_list){
}
std::string MethodType::GetTypeName() {
  return "Method Object, returning " + return_value_type_->GetType() + " value";
}
Type *MethodType::GetType() {
  return return_value_type_;
}
