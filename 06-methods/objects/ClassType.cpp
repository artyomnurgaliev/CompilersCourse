#include "ClassType.h"

std::unordered_map<Symbol, std::shared_ptr<MethodType>> ClassType::GetMethods() {
  return methods_;
}
ClassType::ClassType(const std::string& extends_identifier) : extends_class_(Symbol(extends_identifier)) {
}
void ClassType::AddMethod(const Symbol& symbol, std::shared_ptr<MethodType> method) {
  methods_[symbol] = method;
}
std::string ClassType::GetTypeName() {
  return "Class";
}
