
#pragma once

#include <symbol_table/Symbol.h>
#include <unordered_map>
#include <grammar/nterms_classes/class_declarations/ClassDeclaration.h>
#include <objects/PrimitiveType.h>
#include <objects/MethodType.h>

class ClassStorage {
public:
    static ClassStorage& GetInstance();
    void SetMethod(const Symbol& symbol, std::unordered_map<Symbol, std::shared_ptr<MethodType>> methods);
    void SetField(const Symbol& symbol, std::unordered_map<Symbol, std::shared_ptr<PrimitiveType>> fields);
    std::unordered_map<Symbol, std::shared_ptr<MethodType>> GetMethods(const Symbol& symbol) const;
    std::unordered_map<Symbol,  std::shared_ptr<PrimitiveType>> GetFields(const Symbol& symbol) const;
    ClassStorage(const ClassStorage& other) = delete;
    ClassStorage& operator= (const ClassStorage&) = delete;
    std::vector<Symbol> GetMethodsNames(Symbol symbol);
    void SetClassMethodsNames(const Symbol& symbol, std::vector<Symbol> class_methods_names);
    std::vector<Symbol> GetFieldsNames(Symbol symbol);
    void SetClassFieldsNames(const Symbol& symbol, std::vector<Symbol> class_methods_names);
 private:
    ClassStorage() = default;
    ~ClassStorage() = default;
    std::unordered_map<Symbol, std::vector<Symbol>> class_methods_names_;
    std::unordered_map<Symbol, std::vector<Symbol>> class_fields_names_;
    std::unordered_map<Symbol, std::unordered_map<Symbol, std::shared_ptr<MethodType>>> class_methods_;
    std::unordered_map<Symbol, std::unordered_map<Symbol, std::shared_ptr<PrimitiveType>>> class_fields_;
};


