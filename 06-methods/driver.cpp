#include <visitors/MethodCallVisitor.h>
#include <method-mechanisms/ClassStorage.h>
#include "driver.hh"
#include "parser.hh"

#include "visitors/Interpreter.h"
#include "visitors/PrintVisitor.h"

#include "visitors/SymbolTreeVisitor.h"



Driver::Driver() :
    trace_parsing(false),
    trace_scanning(false),
    scanner(*this), parser(scanner, *this) {
}


int Driver::parse(const std::string& f) {
    file = f;
    location.initialize(&file);
    scan_begin();
    parser.set_debug_level(trace_parsing);
    int res = parser();
    std::cout << "parser " << res << std::endl;
    scan_end();
    return res;
}

int Driver::Evaluate() {
    SymbolTreeVisitor visitor;
    visitor.Visit(program);

    std::cout << "Symbol tree built" << std::endl;

    ScopeLayerTree root = visitor.GetRoot();

    auto classes = visitor.GetClasses();
    auto main_class = visitor.GetMainClass();
    ClassStorage& storage = ClassStorage::GetInstance();
    for (const auto& cl : classes) {
      std::unordered_map<Symbol, MethodDeclaration*> methods;
      for (const auto& method: cl.second->GetMethodTypes()) {
        methods[method.first] = method.second->GetMethodDeclaration();
      }
      std::unordered_map<Symbol, std::shared_ptr<PrimitiveType>> fields;
      for (const auto& field: cl.second->GetFieldTypes()) {
        fields[field.first] = field.second;
      }
      storage.SetMethod(cl.first, methods);
      storage.SetField(cl.first, fields);
    }

    auto main_function = main_class->GetMethodDeclaration();

    std::shared_ptr<MethodType> method_type = std::dynamic_pointer_cast<MethodType>(
        root.Get(Symbol("main"))
    );

    MethodCallVisitor method_visitor(
        root.GetScopeByName(Symbol("main")),
        method_type
      );

    method_visitor.SetTree(&root);

    method_visitor.Visit(main_function);

    root.PrintTree("symbol_tree.txt");
    // Interpreter interpreter(root);
    // int interpreter_result = interpreter.GetResult(program);

//    delete root;
    // return interpreter_result;*/
    return 0;
}

void Driver::scan_begin() {
    scanner.set_debug(trace_scanning);
  if (file.empty() || file == "-") {
  } else {
    stream.open(file);
    std::cout << file << std::endl;
    scanner.yyrestart(&stream);
  }
}

void Driver::scan_end()
{
    stream.close();
}

void Driver::PrintTree(const std::string& filename) {
    PrintVisitor visitor(filename);
    visitor.Visit(program);
}

