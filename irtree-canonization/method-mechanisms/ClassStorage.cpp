#include "ClassStorage.h"

#include <utility>

ClassStorage &ClassStorage::GetInstance() {
    static ClassStorage storage;
    return storage;
}

void ClassStorage::SetMethod(const Symbol& symbol, std::unordered_map<Symbol, std::shared_ptr<MethodType>> methods) {
    class_methods_[symbol] = std::move(methods);
}


std::unordered_map<Symbol, std::shared_ptr<MethodType>> ClassStorage::GetMethods(const Symbol& symbol) const {
    if (class_methods_.find(symbol) != class_methods_.end()) {
        return class_methods_.at(symbol);
    } else {
        throw std::runtime_error("Class not found");
    }
}
void ClassStorage::SetField(const Symbol& symbol, std::unordered_map<Symbol, std::shared_ptr<PrimitiveType>> fields) {
  class_fields_[symbol] = std::move(fields);
}
std::unordered_map<Symbol,  std::shared_ptr<PrimitiveType>> ClassStorage::GetFields(const Symbol& symbol) const {
  if (class_fields_.find(symbol) != class_fields_.end()) {
    return class_fields_.at(symbol);
  } else {
    throw std::runtime_error("Class not found");
  }
}

std::vector<Symbol> ClassStorage::GetMethodsNames(Symbol symbol) {
  return class_methods_names_[symbol];
}
void ClassStorage::SetClassMethodsNames(const Symbol& symbol, std::vector<Symbol> class_methods_names) {
  class_methods_names_[symbol] = std::move(class_methods_names);
}
std::vector<Symbol> ClassStorage::GetFieldsNames(Symbol symbol) {
  return class_fields_names_[symbol];
}
void ClassStorage::SetClassFieldsNames(const Symbol& symbol, std::vector<Symbol> class_fields_names) {
  class_fields_names_[symbol] = std::move(class_fields_names);
}