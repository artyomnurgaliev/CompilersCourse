
#include "MethodType.h"
#include <nterms_classes/FormalList.h>
/*
std::string MethodType::GetTypeName() {
  return "Method Object, returning " + return_value_type_->GetType() + " value";
}
*/
Type *MethodType::GetReturnValueType() {
  return return_value_type_;
}
/*
std::string MethodType::GetObject() {
  return "MethodType";
}
 */
MethodType::MethodType(MethodDeclaration *method_declaration) : method_declaration_(method_declaration),
                                                                return_value_type_(method_declaration->GetType()),
                                                                formal_list_(method_declaration->GetFormals()) {

}
MethodDeclaration *MethodType::GetMethodDeclaration() {
  return method_declaration_;
}
