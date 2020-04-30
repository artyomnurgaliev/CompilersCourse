#include "SymbolTreeVisitor.h"

#include "elements.h"

#include <iostream>

SymbolTreeVisitor::SymbolTreeVisitor(): tree_(new ScopeLayer) {
    current_layer_ = tree_.root_;
}

void SymbolTreeVisitor::Visit(SimpleType* simple_type){}
void SymbolTreeVisitor::Visit(ArrayType* array_type) {}
void SymbolTreeVisitor::Visit(AssertStatement* assert_statement){

}
void SymbolTreeVisitor::Visit(AssignmentStatement* assignment_statement) {
}
void SymbolTreeVisitor::Visit(IfStatement* if_statement) {
  auto new_layer = new ScopeLayer(current_layer_);

  current_layer_ = new_layer;
  if_statement->GetStatement()->Accept(this);
  current_layer_ = current_layer_->GetParent();
}
void SymbolTreeVisitor::Visit(IfElseStatement* if_else_statement){
  auto new_layer = new ScopeLayer(current_layer_);

  current_layer_ = new_layer;
  if_else_statement->GetStatement()->Accept(this);
  current_layer_ = current_layer_->GetParent();

  new_layer = new ScopeLayer(current_layer_);

  current_layer_ = new_layer;
  if_else_statement->GetElseStatement()->Accept(this);
  current_layer_ = current_layer_->GetParent();
}
void SymbolTreeVisitor::Visit(LocalVariableDeclaration* local_variable_declaration){
  local_variable_declaration->GetVariableDeclaration()->Accept(this);
}
void SymbolTreeVisitor::Visit(MethodInvocationStatement* method_invocation_statement) {}
void SymbolTreeVisitor::Visit(ReturnStatement* return_statement) {}
void SymbolTreeVisitor::Visit(ScopeStatement* scope_statement) {
  auto new_layer = new ScopeLayer(current_layer_);

  current_layer_ = new_layer;
  scope_statement->GetStatementList()->Accept(this);
  current_layer_ = current_layer_->GetParent();
}
void SymbolTreeVisitor::Visit(SoutStatement* sout_statement){
}
void SymbolTreeVisitor::Visit(StatementList* statement_list){
  for (auto st: statement_list->GetStatements()) {
    st->Accept(this);
  }
}
void SymbolTreeVisitor::Visit(WhileStatement* while_statement) {
  auto new_layer = new ScopeLayer(current_layer_);

  current_layer_ = new_layer;
  while_statement->GetStatement()->Accept(this);
  current_layer_ = current_layer_->GetParent();
}
void SymbolTreeVisitor::Visit(SimpleLvalue* simple_lvalue) {}
void SymbolTreeVisitor::Visit(ArrayElementLvalue* array_element_lvalue) {}
void SymbolTreeVisitor::Visit(AccessToArrayElementExpression* access_to_array_element_expression){}
void SymbolTreeVisitor::Visit(ArrayDefenitionExpression* array_defenition_expression) {}
void SymbolTreeVisitor::Visit(ArrayLengthExpression* array_length_expression){
}
void SymbolTreeVisitor::Visit(BinaryOperatorExpression* binary_operator_expression){
}
void SymbolTreeVisitor::Visit(DefenitionExpression* defenition_expression) {
}
void SymbolTreeVisitor::Visit(ExpressionList* expression_list){
  for (auto expr: expression_list->GetExpressions()) {
    expr->Accept(this);
  }
}
void SymbolTreeVisitor::Visit(IdentExpression* ident_expression) {
}
void SymbolTreeVisitor::Visit(MethodInvocationExpression* method_invocation_expression){
}
void SymbolTreeVisitor::Visit(NotExpression* not_expression) {
}
void SymbolTreeVisitor::Visit(NumberExpression* number_expression) {
}
void SymbolTreeVisitor::Visit(ParenthesisExpression* parenthesis_expression) {
}
void SymbolTreeVisitor::Visit(ThisExpression* this_expression) {
}
void SymbolTreeVisitor::Visit(BoolExpression* bool_expression) {
}
void SymbolTreeVisitor::Visit(Declaration* declaration) {
  if (declaration->IsVariable()) {
    declaration->GetVariableDeclaration()->Accept(this);
  } else {
    declaration->GetMethodDeclaration()->Accept(this);
  }
}
void SymbolTreeVisitor::Visit(DeclarationList* declaration_list) {
  for (auto decl: declaration_list->GetDeclarations()) {
    decl->Accept(this);
  }
}
void SymbolTreeVisitor::Visit(MethodDeclaration* method_declaration) {
  current_layer_->DeclareMethod(Symbol(method_declaration->GetIdentifier()),
                                method_declaration);
  auto new_layer = new ScopeLayer(current_layer_);
  current_layer_ = new_layer;
  method_declaration->GetFormals()->Accept(this);
  method_declaration->GetStatements()->Accept(this);

  tree_.AddMapping(Symbol(method_declaration->GetIdentifier()), new_layer);

  current_layer_ = current_layer_->GetParent();

  //// TODO - functions_[Symbol(method_declaration->GetIdentifier())] = method_declaration;
}
void SymbolTreeVisitor::Visit(VariableDeclaration* variable_declaration) {
  current_layer_->DeclareVariable(Symbol(variable_declaration->GetIdentifier()), variable_declaration->GetType());
}
void SymbolTreeVisitor::Visit(ClassDeclaration* class_declaration) {
  current_layer_->DeclareClass(Symbol(class_declaration->GetIdentifier()),
                                class_declaration);
  auto new_layer = new ScopeLayer(current_layer_);
  current_layer_ = new_layer;
  class_declaration->GetDeclarationList()->Accept(this);

  tree_.AddMapping(Symbol(class_declaration->GetIdentifier()), new_layer);

  current_layer_ = current_layer_->GetParent();

  //// TODO - functions_[Symbol(method_declaration->GetIdentifier())] = method_declaration;

}
void SymbolTreeVisitor::Visit(ClassDeclarationList* class_declaration_list) {
  for (auto class_decl: class_declaration_list->GetClassDeclarations()) {
    class_decl->Accept(this);
  }
}
void SymbolTreeVisitor::Visit(MainClass* main_class) {
  current_layer_->DeclareMainClass(Symbol(main_class->GetIdentifier()),
                               main_class->GetStatementList());
  auto new_layer = new ScopeLayer(current_layer_);
  current_layer_ = new_layer;
  main_class->GetStatementList()->Accept(this);

  tree_.AddMapping(Symbol(main_class->GetIdentifier()), new_layer);

  current_layer_ = current_layer_->GetParent();
}
void SymbolTreeVisitor::Visit(Type* type) {
}
void SymbolTreeVisitor::Visit(TypeIdentifier* type_identifier) {
}
void SymbolTreeVisitor::Visit(MethodInvocation* method_invocation) {
}
void SymbolTreeVisitor::Visit(FormalList* formal_list) {
  for (auto formal: formal_list->GetFormals()) {
    formal->Accept(this);
  }
}
void SymbolTreeVisitor::Visit(Formal* formal) {
  current_layer_->DeclareVariable(Symbol(formal->GetIdentifier()), formal->GetType());
}
void SymbolTreeVisitor::Visit(BinaryOperator* binary_operator) {
}
void SymbolTreeVisitor::Visit(Program* program) {
  program->GetMainClass()->Accept(this);
  program->GetClassDeclarationList()->Accept(this);
}
void SymbolTreeVisitor::Visit(Expression *expression) {
}
void SymbolTreeVisitor::Visit(Lvalue *lvalue) {
}
void SymbolTreeVisitor::Visit(Statement *statement) {
}
void SymbolTreeVisitor::Visit(
    LocalVariableDeclarationStatement *local_variable_declaration_statement) {
  local_variable_declaration_statement->GetLocalVariableDeclaration()->Accept(this);
}

ScopeLayerTree SymbolTreeVisitor::GetRoot() {
  return tree_;
}


//// TODO - methods and classes
/*
std::unordered_map<Symbol, Function *> SymbolTreeVisitor::GetFunctions() const {
  return functions_;
}*/