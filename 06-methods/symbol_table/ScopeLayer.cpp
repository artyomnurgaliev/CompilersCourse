#include "ScopeLayer.h"

#include <iostream>
#include <symbol_table/objects/ClassType.h>
#include <symbol_table/objects/MainClassType.h>
#include <symbol_table/objects/MethodType.h>
#include <symbol_table/objects/PrimitiveObjectType.h>

ScopeLayer::ScopeLayer(ScopeLayer* parent): parent_(parent) {
    std::cout << "Constructor called" << std::endl;
    std::cout << "End contstructor called" << std::endl;
    parent_->AddChild(this);
}

void ScopeLayer::AttachParent() {
    
}

ScopeLayer::ScopeLayer(): parent_(nullptr) {}

void ScopeLayer::DeclareVariable(Symbol symbol, Type* type) {
  if (values_.find(symbol) != values_.end()) {
    throw std::runtime_error("Variable has declared");
  }

  values_[symbol] = std::make_shared<PrimitiveObjectType>(type);

  offsets_[symbol] = symbols_.size();
  symbols_.push_back(symbol);
}

void ScopeLayer::DeclareMethod(Symbol symbol,
                               MethodDeclaration *method_declaration) {
  if (values_.find(symbol) != values_.end()) {
    throw std::runtime_error("Method has declared");
  }
  values_[symbol] = std::make_shared<MethodType>(method_declaration->GetType(), method_declaration->GetFormals());
  offsets_[symbol] = symbols_.size();
  symbols_.push_back(symbol);
}

void ScopeLayer::DeclareMainClass(Symbol symbol,
                                  StatementList *statement_list) {
  if (values_.find(symbol) != values_.end()) {
    throw std::runtime_error("Main Class has declared");
  }
  values_[symbol] = std::make_shared<MainClassType>(statement_list);
  offsets_[symbol] = symbols_.size();
  symbols_.push_back(symbol);
}


void ScopeLayer::DeclareClass(Symbol symbol,
                              ClassDeclaration *class_declaration) {
  if (values_.find(symbol) != values_.end()) {
    throw std::runtime_error("Class has declared");
  }
  values_[symbol] = std::make_shared<ClassType>(class_declaration->GetExtendsIdentifier(),class_declaration->GetDeclarationList());
  symbols_.push_back(symbol);
  offsets_[symbol] = symbols_.size();
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
        throw std::runtime_error("Variable not declared");
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


