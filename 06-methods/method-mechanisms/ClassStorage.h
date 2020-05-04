
#pragma once

#include <symbol_table/Symbol.h>
#include <unordered_map>
#include <grammar/nterms_classes/class_declarations/ClassDeclaration.h>
#include <objects/PrimitiveType.h>

class ClassStorage {
public:
    static ClassStorage& GetInstance();
    void SetMethod(const Symbol& symbol, std::unordered_map<Symbol, MethodDeclaration*> methods);
    void SetField(const Symbol& symbol, std::unordered_map<Symbol, std::shared_ptr<PrimitiveType>> fields);
    std::unordered_map<Symbol, MethodDeclaration*> GetMethods(const Symbol& symbol) const;
    std::unordered_map<Symbol,  std::shared_ptr<PrimitiveType>> GetFields(const Symbol& symbol) const;
    ClassStorage(const ClassStorage& other) = delete;
    ClassStorage& operator= (const ClassStorage&) = delete;
private:
    ClassStorage() = default;
    ~ClassStorage() = default;
    std::unordered_map<Symbol, std::unordered_map<Symbol, MethodDeclaration*>> class_methods_;
    std::unordered_map<Symbol, std::unordered_map<Symbol, std::shared_ptr<PrimitiveType>>> class_fields_;
};


