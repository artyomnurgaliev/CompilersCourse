#include "ClassType.h"

#include <utility>

std::unordered_map<Symbol, std::shared_ptr<MethodType>> ClassType::GetMethodTypes() {
  return method_types_;
}
ClassType::ClassType(const std::string &extends_identifier, ClassDeclaration *class_declaration)
  : class_declaration_(class_declaration), extends_class_(Symbol(extends_identifier)) {
}
void ClassType::AddMethod(const Symbol &symbol, std::shared_ptr<MethodType> method) {
  method_types_[symbol] = std::move(method);
}
ClassDeclaration *ClassType::GetClassDeclaration() {
  return class_declaration_;
}
void ClassType::AddField(const Symbol &symbol, std::shared_ptr<PrimitiveType> field) {
  field_types_[symbol] = std::move(field);
}
std::unordered_map<Symbol, std::shared_ptr<PrimitiveType>> ClassType::GetFieldTypes() {
  return field_types_;
}
/*
std::string ClassType::GetTypeName() {
  return "Class";
}
std::string ClassType::GetObject() {
  return "ClassType";
}
*/