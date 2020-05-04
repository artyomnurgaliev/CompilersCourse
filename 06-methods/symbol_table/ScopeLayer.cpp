#include "ScopeLayer.h"

#include <iostream>

ScopeLayer::ScopeLayer(ScopeLayer* parent): parent_(parent) {
    std::cout << "Constructor called" << std::endl;
    std::cout << "End contstructor called" << std::endl;
    parent_->AddChild(this);
}

void ScopeLayer::AttachParent() {
    
}

ScopeLayer::ScopeLayer(): parent_(nullptr) {}



std::shared_ptr<MethodType> ScopeLayer::DeclareMethod(Symbol symbol,
                               MethodDeclaration *method_declaration) {
  if (values_.find(symbol) != values_.end()) {
    throw std::runtime_error("Method has declared");
  }
  auto method = std::make_shared<MethodType>(method_declaration);
  values_[symbol] = method;
  offsets_[symbol] = symbols_.size();
  symbols_.push_back(symbol);
  return method;
}

std::shared_ptr<ClassType> ScopeLayer::DeclareClass(Symbol symbol,
                              ClassDeclaration *class_declaration) {
  if (values_.find(symbol) != values_.end()) {
    throw std::runtime_error("Class has declared");
  }
  auto class_decl = std::make_shared<ClassType>(class_declaration->GetExtendsIdentifier(), class_declaration);
  values_[symbol] = class_decl;
  symbols_.push_back(symbol);
  offsets_[symbol] = symbols_.size();
  return class_decl;
}


void ScopeLayer::Put(Symbol symbol, std::shared_ptr<ObjectType> value) {

  ScopeLayer* current_layer = this;

  while (!current_layer->Has(symbol) && current_layer->parent_ != nullptr) {
      current_layer = current_layer->parent_;
  }
  if (current_layer->Has(symbol)) {
      current_layer->values_.find(symbol)->second = value;
  } else {
      throw std::runtime_error("Variable not declared");
  }
}

bool ScopeLayer::Has(Symbol symbol) {
    return values_.find(symbol) != values_.end();
}


std::shared_ptr<ObjectType> ScopeLayer::Get(Symbol symbol) {
    ScopeLayer* current_layer = this;

    while (!current_layer->Has(symbol) && current_layer->parent_ != nullptr) {
        current_layer = current_layer->parent_;
    }
    if (current_layer->Has(symbol)) {
        return current_layer->values_.find(symbol)->second;
    } else {
        throw std::runtime_error("Not declared");
    }
}

ScopeLayer* ScopeLayer::GetChild(size_t index) {
    std::cout << "Children of scope: " << children_.size() << std::endl;
    return children_[index];
}

void ScopeLayer::AddChild(ScopeLayer* child) {
    children_.push_back(child);
}

ScopeLayer* ScopeLayer::GetParent() const {
    return parent_;
}

ScopeLayer::~ScopeLayer() {
  for (ScopeLayer* layer: children_) {
    delete layer;
  }
}
void ScopeLayer::PrintTabs(std::ostream &stream, int num_tabs) const {
  for (int i = 0; i < num_tabs; ++i) {
    stream << "\t";
  }
}
void ScopeLayer::PrintLayer(std::ostream &stream, int num_tabs) const {

  for (const auto & symbol : symbols_) {
    PrintTabs(stream, num_tabs);
    stream << symbol.GetName() << std::endl;
  }
  for (ScopeLayer* layer : children_) {
    layer->PrintLayer(stream, num_tabs + 1);
  }
}
std::shared_ptr<PrimitiveSimpleType> ScopeLayer::DeclareSimpleVariable(Symbol symbol, SimpleType *type) {
  if (values_.find(symbol) != values_.end()) {
    throw std::runtime_error("Variable has declared");
  }

  auto type_id = type->GetSimpleTypeIdentifier();
  auto variable = std::make_shared<PrimitiveSimpleType>(type);
  values_[symbol] = variable;
  offsets_[symbol] = symbols_.size();
  symbols_.push_back(symbol);
  return variable;
}
std::shared_ptr<PrimitiveArrayType> ScopeLayer::DeclareArrayVariable(Symbol symbol, ArrayType *type) {
  if (values_.find(symbol) != values_.end()) {
    throw std::runtime_error("Variable has declared");
  }
  auto variable = std::make_shared<PrimitiveArrayType>(type);
  values_[symbol] = variable;
  offsets_[symbol] = symbols_.size();
  symbols_.push_back(symbol);
  return variable;
}


