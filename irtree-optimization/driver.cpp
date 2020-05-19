#include <irtree/visitors/PrintVisitor.h>
#include <visitors/IrtreeBuildVisitor.h>
#include <visitors/MethodCallVisitor.h>
#include <visitors/PrintVisitor.h>
#include <visitors/SymbolTreeVisitor.h>
#include <include/driver.hh>
#include <method-mechanisms/ClassStorage.h>

Driver::Driver() :
  trace_parsing(false),
  trace_scanning(false),
  scanner(*this), parser(scanner, *this) {
}

int Driver::parse(const std::string &f) {
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
  ClassStorage &storage = ClassStorage::GetInstance();
  for (const auto &cl : classes) {
    std::unordered_map<Symbol, std::shared_ptr<MethodType>> methods;
    for (const auto &method: cl.second->GetMethodTypes()) {
      methods[method.first] = method.second;
    }
    std::unordered_map<Symbol, std::shared_ptr<PrimitiveType>> fields;
    for (const auto &field: cl.second->GetFieldTypes()) {
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
    method_type,
    new VariableObject(new PrimitiveSimpleType(new SimpleType("int")), 0)
  );

  method_visitor.SetTree(&root);

  method_visitor.Visit(main_function);

  IrtreeBuildVisitor irt_build_visitor;
  irt_build_visitor.SetTree(&root);
  irt_build_visitor.Visit(program);

  IrtMapping methods = irt_build_visitor.GetTrees();

  for (auto func_view = methods.begin(); func_view != methods.end(); ++func_view) {
    IRT::PrintVisitor print_visitor_irt(func_view->first + "_irt.txt");
    methods[func_view->first]->Accept(&print_visitor_irt);
  }
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

void Driver::scan_end() {
  stream.close();
}

void Driver::PrintTree(const std::string &filename) {
  PrintVisitor visitor(filename);
  visitor.Visit(program);
}

