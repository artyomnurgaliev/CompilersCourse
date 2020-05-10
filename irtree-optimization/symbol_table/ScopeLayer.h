#pragma once

#include "Symbol.h"
#include "objects/ObjectType.h"

#include <memory>
#include <nterms_classes/declarations/MethodDeclaration.h>
#include <string>
#include <unordered_map>
#include <vector>
#include <objects/ClassType.h>
#include <objects/MethodType.h>
#include <objects/PrimitiveSimpleType.h>
#include <objects/PrimitiveArrayType.h>

class ScopeLayer {
 public:
    explicit ScopeLayer(ScopeLayer* parent);
    ScopeLayer();
    ~ScopeLayer();
    std::shared_ptr<PrimitiveSimpleType> DeclareSimpleVariable(Symbol symbol, SimpleType* type);
    std::shared_ptr<PrimitiveArrayType> DeclareArrayVariable(Symbol symbol, ArrayType* type);
    std::shared_ptr<MethodType> DeclareMethod(Symbol symbol, MethodDeclaration* method_declaration);
    std::shared_ptr<ClassType> DeclareClass(Symbol symbol, ClassDeclaration* class_declaration);
    void Put(Symbol symbol, std::shared_ptr<ObjectType> value);
    std::shared_ptr<ObjectType> Get(Symbol symbol);
    bool Has(Symbol symbol);

    void AddChild(ScopeLayer* child);
    void AttachParent();

    ScopeLayer* GetChild(size_t index);
    ScopeLayer* GetParent() const;

    void PrintLayer(std::ostream& stream, int num_tabs) const;
 private:
    void PrintTabs(std::ostream &stream, int num_tabs) const;
    std::unordered_map<Symbol, std::shared_ptr<ObjectType>> values_;
    std::unordered_map<Symbol, size_t> offsets_;
    std::vector<Symbol> symbols_;
    std::string name_;
    ScopeLayer* parent_;
    std::vector<ScopeLayer* > children_;
};