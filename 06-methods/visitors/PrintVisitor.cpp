#include "PrintVisitor.h"

#include "elements.h"

#include <iostream>

PrintVisitor::PrintVisitor(const std::string& filename) : stream_(filename) {
}

void PrintVisitor::Visit(SimpleType* simple_type){
  PrintTabs();
  stream_ << "Simple Type:" << simple_type->GetSimpleTypeIdentifier() << std::endl;
}
void PrintVisitor::Visit(ArrayType* array_type) {
  PrintTabs();
  stream_ << "Array Type:" << std::endl;
  ++num_tabs_;
  array_type->GetSimpleType()->Accept(this);
  --num_tabs_;
}
void PrintVisitor::Visit(AssertStatement* assert_statement){
  PrintTabs();
  stream_ << "Assert statement:" << std::endl;
  ++num_tabs_;
  assert_statement->GetExpression()->Accept(this);
  --num_tabs_;
}
void PrintVisitor::Visit(AssignmentStatement* assignment_statement) {
  PrintTabs();
  stream_ << "Assignment statement:" << std::endl;
  ++num_tabs_;
  assignment_statement->GetLvalue()->Accept(this);
  assignment_statement->GetExpression()->Accept(this);
  --num_tabs_;
}
void PrintVisitor::Visit(IfStatement* if_statement) {
  PrintTabs();
  stream_ << "If statement:" << std::endl;
  ++num_tabs_;
  PrintTabs();
  stream_ << "If:" << std::endl;
  if_statement->GetExpression()->Accept(this);
  PrintTabs();
  stream_ << "Then:" << std::endl;
  if_statement->GetStatement()->Accept(this);
  --num_tabs_;
}
void PrintVisitor::Visit(IfElseStatement* if_else_statement){
  PrintTabs();
  stream_ << "If else statement:" << std::endl;
  ++num_tabs_;
  PrintTabs();
  stream_ << "If:" << std::endl;
  if_else_statement->GetExpression()->Accept(this);
  PrintTabs();
  stream_ << "Then:" << std::endl;
  if_else_statement->GetStatement()->Accept(this);
  PrintTabs();
  stream_ << "Else:" << std::endl;
  if_else_statement->GetElseStatement()->Accept(this);
  --num_tabs_;
}
void PrintVisitor::Visit(LocalVariableDeclaration* local_variable_declaration){
  PrintTabs();
  stream_ << "Local Variable Declaration:" << std::endl;
  ++num_tabs_;
  local_variable_declaration->GetVariableDeclaration()->Accept(this);
  --num_tabs_;
}
void PrintVisitor::Visit(MethodInvocationStatement* method_invocation_statement) {
  PrintTabs();
  stream_ << "Method Invocation Statement:" << std::endl;
  ++num_tabs_;
  method_invocation_statement->GetMethodInvocation()->Accept(this);
  --num_tabs_;
}
void PrintVisitor::Visit(ReturnStatement* return_statement) {
  PrintTabs();
  stream_ << "Return Statement:" << std::endl;
  ++num_tabs_;
  return_statement->GetExpression()->Accept(this);
  --num_tabs_;
}
void PrintVisitor::Visit(ScopeStatement* scope_statement) {
  PrintTabs();
  stream_ << "Scope Statement:" << std::endl;
  ++num_tabs_;
  scope_statement->GetStatementList()->Accept(this);
  --num_tabs_;
}
void PrintVisitor::Visit(SoutStatement* sout_statement){
  PrintTabs();
  stream_ << "Sout statement:" << std::endl;
  ++num_tabs_;
  sout_statement->GetExpression()->Accept(this);
  --num_tabs_;
}

void PrintVisitor::Visit(StatementList* statement_list){
  PrintTabs();
  stream_ << "Statement List:" << std::endl;
  ++num_tabs_;
  for (auto st: statement_list->GetStatements()) {
    st->Accept(this);
  }
  --num_tabs_;
}
void PrintVisitor::Visit(WhileStatement* while_statement) {
  PrintTabs();
  stream_ << "While Statement:" << std::endl;
  ++num_tabs_;
  PrintTabs();
  stream_ << "While: " << std::endl;
  while_statement->GetExpression()->Accept(this);
  PrintTabs();
  stream_ << "do: " << std::endl;
  while_statement->GetStatement()->Accept(this);
  --num_tabs_;
}

void PrintVisitor::Visit(SimpleLvalue* simple_lvalue) {
  PrintTabs();
  stream_ << "Simple lvalue:" << std::endl;
  ++num_tabs_;
  PrintTabs();
  stream_ << "identifier: " << simple_lvalue->GetIdentifier() << std::endl;
  --num_tabs_;
}
void PrintVisitor::Visit(ArrayElementLvalue* array_element_lvalue) {
  PrintTabs();
  stream_ << "Array element lvalue:" << std::endl;
  ++num_tabs_;
  PrintTabs();
  stream_ << "identifier: " << array_element_lvalue->GetIdentifier() << std::endl;
  array_element_lvalue->GetExpression()->Accept(this);
  --num_tabs_;
}
void PrintVisitor::Visit(AccessToArrayElementExpression* access_to_array_element_expression){
  PrintTabs();
  stream_ << "Access to array element expression:" << std::endl;
  ++num_tabs_;
  access_to_array_element_expression->GetFirst()->Accept(this);
  access_to_array_element_expression->GetSecond()->Accept(this);
  --num_tabs_;
}
void PrintVisitor::Visit(ArrayNewExpression* array_defenition_expression) {
  PrintTabs();
  stream_ << "Array Definition Expression: " << std::endl;
  ++num_tabs_;
  array_defenition_expression->GetSimpleType()->Accept(this);
  array_defenition_expression->GetExpression()->Accept(this);
  --num_tabs_;
}
void PrintVisitor::Visit(ArrayLengthExpression* array_length_expression){
  PrintTabs();
  stream_ << "Array Length Expression:" << std::endl;
  ++num_tabs_;
  array_length_expression->GetExpression()->Accept(this);
  --num_tabs_;
}

void PrintVisitor::Visit(BinaryOperatorExpression* binary_operator_expression){
  PrintTabs();
  stream_ << "Binary Operator Expression: " << std::endl;
  ++num_tabs_;
  binary_operator_expression->GetFirst()->Accept(this);
  binary_operator_expression->GetBinaryOperator()->Accept(this);
  binary_operator_expression->GetSecond()->Accept(this);
  --num_tabs_;
}

void PrintVisitor::Visit(NewExpression* defenition_expression) {
  PrintTabs();
  stream_ << "Defenition Expression: " << std::endl;
  ++num_tabs_;
  defenition_expression->GetTypeIdentifier()->Accept(this);
  --num_tabs_;
}

void PrintVisitor::Visit(ExpressionList* expression_list){
  PrintTabs();
  stream_ << "Expression List: " << std::endl;
  ++num_tabs_;
  for (auto expr: expression_list->GetExpressions()) {
    expr->Accept(this);
  }
  --num_tabs_;
}
void PrintVisitor::Visit(IdentExpression* ident_expression) {
  PrintTabs();
  stream_ << "Ident Expression:" << std::endl;
  ++num_tabs_;
  PrintTabs();
  stream_ << "identifier: " << ident_expression->GetIdentifier() << std::endl;
  --num_tabs_;
}
void PrintVisitor::Visit(MethodInvocationExpression* method_invocation_expression){
  PrintTabs();
  stream_ << "Method Invocation Expression: " << std::endl;
  ++num_tabs_;
  method_invocation_expression->GetMethodInvocation()->Accept(this);
  --num_tabs_;
}
void PrintVisitor::Visit(NotExpression* not_expression) {
  PrintTabs();
  stream_ << "Not Expression:" << std::endl;
  ++num_tabs_;
  not_expression->GetExpression()->Accept(this);
  --num_tabs_;
}
void PrintVisitor::Visit(NumberExpression* number_expression) {
  PrintTabs();
  stream_ << "Number Expression: " << number_expression->GetValue() << std::endl;
}
void PrintVisitor::Visit(ParenthesisExpression* parenthesis_expression) {
  PrintTabs();
  stream_ << "Parenthesis Expression: " << std::endl;
  ++num_tabs_;
  parenthesis_expression->GetExpression()->Accept(this);
  --num_tabs_;
}
void PrintVisitor::Visit(ThisExpression* this_expression) {
  PrintTabs();
  stream_ << "This Expression" << std::endl;
}
void PrintVisitor::Visit(BoolExpression* bool_expression) {
  PrintTabs();
  stream_ << "Bool Expression: " << bool_expression->GetValue() << std::endl;
}
void PrintVisitor::Visit(Declaration* declaration) {
  PrintTabs();
  stream_ << "Declaration: " << std::endl;
  ++num_tabs_;
  if (declaration->IsVariable()) {
    declaration->GetVariableDeclaration()->Accept(this);
  } else {
    declaration->GetMethodDeclaration()->Accept(this);
  }
  --num_tabs_;
}
void PrintVisitor::Visit(DeclarationList* declaration_list) {
  PrintTabs();
  stream_ << "Declaration List: " << std::endl;
  ++num_tabs_;
  for (auto decl : declaration_list->GetDeclarations()) {
    decl->Accept(this);
  }
  --num_tabs_;
}
void PrintVisitor::Visit(MethodDeclaration* method_declaration) {
  PrintTabs();
  stream_ << "Method Declaration: " << std::endl;
  ++num_tabs_;
  method_declaration->GetType()->Accept(this);
  PrintTabs();
  stream_ << "identifier: " << method_declaration->GetIdentifier() << std::endl;
  method_declaration->GetFormals()->Accept(this);
  method_declaration->GetStatements()->Accept(this);
  --num_tabs_;
}
void PrintVisitor::Visit(VariableDeclaration* variable_declaration) {
  PrintTabs();
  stream_ << "Variable Declaration :" << std::endl;
  ++num_tabs_;
  variable_declaration->GetType()->Accept(this);
  PrintTabs();
  stream_ << "identifier: " << variable_declaration->GetIdentifier() << std::endl;
  --num_tabs_;
}
void PrintVisitor::Visit(ClassDeclaration* class_declaration) {
  PrintTabs();
  stream_ << "Class Declaration: " << std::endl;
  ++num_tabs_;
  PrintTabs();
  stream_ << "identifier: " << class_declaration->GetIdentifier() << std::endl;
  PrintTabs();
  stream_ << "extends identifier: " << class_declaration->GetExtendsIdentifier() << std::endl;

  class_declaration->GetDeclarationList()->Accept(this);
  --num_tabs_;
}
void PrintVisitor::Visit(ClassDeclarationList* class_declaration_list) {
  PrintTabs();
  stream_ << "Class Declaration List: " << std::endl;
  ++num_tabs_;
  for (auto cl_decl : class_declaration_list->GetClassDeclarations()) {
    cl_decl->Accept(this);
  }
  --num_tabs_;
}
void PrintVisitor::Visit(MainClass* main_class) {
  PrintTabs();
  stream_ << "MainClass: " << std::endl;
  ++num_tabs_;
  PrintTabs();
  stream_ << "identifier: " << main_class->GetIdentifier() << std::endl;
  main_class->GetStatementList()->Accept(this);
  --num_tabs_;
}
void PrintVisitor::Visit(Type* type) {
  PrintTabs();
  stream_ << "Type: " << std::endl;
  ++num_tabs_;
  if (type->IsSimpleType()) {
    type->GetSimpleType()->Accept(this);
  } else {
    type->GetArrayType()->Accept(this);
  }
  --num_tabs_;
}
void PrintVisitor::Visit(TypeIdentifier* type_identifier) {
  PrintTabs();
  stream_ << "Type Identifier: " << std::endl;
  ++num_tabs_;
  PrintTabs();
  stream_ << "identifier: " << type_identifier->GetIdentifier() << std::endl;
  --num_tabs_;
}
void PrintVisitor::Visit(MethodInvocation* method_invocation) {
  PrintTabs();
  stream_ << "Method Invocation: " << std::endl;
  ++num_tabs_;
  method_invocation->GetExpression()->Accept(this);
  PrintTabs();
  stream_ << "identifier: " << method_invocation->GetIdentifier() << std::endl;
  method_invocation->GetFirst()->Accept(this);
  method_invocation->GetExpressionList()->Accept(this);
  --num_tabs_;
}
void PrintVisitor::Visit(FormalList* formal_list) {
  PrintTabs();
  stream_ << "FormalList: " << std::endl;
  ++num_tabs_;
  for (auto formal: formal_list->GetFormals()) {
    formal->Accept(this);
  }
  --num_tabs_;
}
void PrintVisitor::Visit(Formal* formal) {
  PrintTabs();
  stream_ << "Formal: " << std::endl;
  ++num_tabs_;
  formal->GetType()->Accept(this);
  PrintTabs();
  stream_ << "identifier: " << formal->GetIdentifier() << std::endl;
  --num_tabs_;
}
void PrintVisitor::Visit(BinaryOperator* binary_operator) {
  PrintTabs();
  stream_ << "BinaryOperator: " << binary_operator->GetOperatorName() << std::endl;
}
void PrintVisitor::Visit(Program* program) {
  PrintTabs();
  stream_ << "Program:" << std::endl;
  ++num_tabs_;
  program->GetMainClass()->Accept(this);
  program->GetClassDeclarationList()->Accept(this);
  --num_tabs_;
}


PrintVisitor::~PrintVisitor() {
  stream_.close();
}
void PrintVisitor::Visit(Expression *expression) {}
void PrintVisitor::Visit(Lvalue *lvalue) {}
void PrintVisitor::Visit(Statement *statement) {}
void PrintVisitor::Visit(
  LocalVariableDeclarationStatement *local_variable_declaration_statement) {
  PrintTabs();
  stream_ << "Local Variable Declaration Statement:" << std::endl;
  ++num_tabs_;
  local_variable_declaration_statement->GetLocalVariableDeclaration()->Accept(this);
  --num_tabs_;
}
void PrintVisitor::PrintTabs() {
  for (int i = 0; i < num_tabs_; ++i) {
    stream_ << '\t';
  }
}