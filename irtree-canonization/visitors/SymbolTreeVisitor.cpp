#include "SymbolTreeVisitor.h"

#include "elements.h"

#include <iostream>

SymbolTreeVisitor::SymbolTreeVisitor() : tree_(new ScopeLayer()) {
  current_layer_ = tree_.root_;
}

void SymbolTreeVisitor::Visit(SimpleType *simple_type) {
  /// do nothing
}
void SymbolTreeVisitor::Visit(ArrayType *array_type) {
  array_type->GetSimpleType()->Accept(this);
}
void SymbolTreeVisitor::Visit(AssertStatement *assert_statement) {
  assert_statement->GetExpression()->Accept(this);
}
void SymbolTreeVisitor::Visit(AssignmentStatement *assignment_statement) {
  assignment_statement->GetLvalue()->Accept(this);
  assignment_statement->GetExpression()->Accept(this);
}
void SymbolTreeVisitor::Visit(IfStatement *if_statement) {
  auto new_layer = new ScopeLayer(current_layer_);

  current_layer_ = new_layer;
  if_statement->GetStatement()->Accept(this);
  current_layer_ = current_layer_->GetParent();
}
void SymbolTreeVisitor::Visit(IfElseStatement *if_else_statement) {
  auto new_layer = new ScopeLayer(current_layer_);

  current_layer_ = new_layer;
  if_else_statement->GetStatement()->Accept(this);
  current_layer_ = current_layer_->GetParent();

  new_layer = new ScopeLayer(current_layer_);

  current_layer_ = new_layer;
  if_else_statement->GetElseStatement()->Accept(this);
  current_layer_ = current_layer_->GetParent();
}
void SymbolTreeVisitor::Visit(LocalVariableDeclaration *local_variable_declaration) {
  local_variable_declaration->GetVariableDeclaration()->Accept(this);
}
void SymbolTreeVisitor::Visit(MethodInvocationStatement *method_invocation_statement) {
  method_invocation_statement->GetMethodInvocation()->Accept(this);
}
void SymbolTreeVisitor::Visit(ReturnStatement *return_statement) {
  return_statement->GetExpression()->Accept(this);
}
void SymbolTreeVisitor::Visit(ScopeStatement *scope_statement) {
  auto new_layer = new ScopeLayer(current_layer_);

  current_layer_ = new_layer;
  scope_statement->GetStatementList()->Accept(this);
  current_layer_ = current_layer_->GetParent();
}
void SymbolTreeVisitor::Visit(SoutStatement *sout_statement) {
  sout_statement->GetExpression()->Accept(this);
}
void SymbolTreeVisitor::Visit(StatementList *statement_list) {
  for (auto st: statement_list->GetStatements()) {
    st->Accept(this);
  }
}
void SymbolTreeVisitor::Visit(WhileStatement *while_statement) {
  auto new_layer = new ScopeLayer(current_layer_);

  current_layer_ = new_layer;
  while_statement->GetStatement()->Accept(this);
  current_layer_ = current_layer_->GetParent();
}
void SymbolTreeVisitor::Visit(SimpleLvalue *simple_lvalue) {
  current_layer_->Get(Symbol(simple_lvalue->GetIdentifier()));
}
void SymbolTreeVisitor::Visit(ArrayElementLvalue *array_element_lvalue) {
  current_layer_->Get(Symbol(array_element_lvalue->GetIdentifier()));
  array_element_lvalue->GetExpression()->Accept(this);
}
void SymbolTreeVisitor::Visit(AccessToArrayElementExpression *access_to_array_element_expression) {
  access_to_array_element_expression->GetFirst()->Accept(this);
  access_to_array_element_expression->GetSecond()->Accept(this);
}
void SymbolTreeVisitor::Visit(ArrayNewExpression *array_new_expression) {
  array_new_expression->GetSimpleType()->Accept(this);
  array_new_expression->GetExpression()->Accept(this);
}
void SymbolTreeVisitor::Visit(ArrayLengthExpression *array_length_expression) {
  array_length_expression->GetExpression()->Accept(this);
}
void SymbolTreeVisitor::Visit(BinaryOperatorExpression *binary_operator_expression) {
  binary_operator_expression->GetFirst()->Accept(this);
  binary_operator_expression->GetBinaryOperator()->Accept(this);
  binary_operator_expression->GetSecond()->Accept(this);
}

void SymbolTreeVisitor::Visit(NewExpression *new_expression) {
  new_expression->GetTypeIdentifier()->Accept(this);
}
void SymbolTreeVisitor::Visit(ExpressionList *expression_list) {
  for (auto expr: expression_list->GetExpressions()) {
    expr->Accept(this);
  }
}
void SymbolTreeVisitor::Visit(IdentExpression *ident_expression) {
  /// do nothing
}
void SymbolTreeVisitor::Visit(MethodInvocationExpression *method_invocation_expression) {
  method_invocation_expression->GetMethodInvocation()->Accept(this);
}
void SymbolTreeVisitor::Visit(NotExpression *not_expression) {
  not_expression->GetExpression()->Accept(this);
}
void SymbolTreeVisitor::Visit(NumberExpression *number_expression) {
  /// do nothing
}
void SymbolTreeVisitor::Visit(ParenthesisExpression *parenthesis_expression) {
  parenthesis_expression->GetExpression()->Accept(this);
}
void SymbolTreeVisitor::Visit(ThisExpression *this_expression) {
  /// do nothing
}
void SymbolTreeVisitor::Visit(BoolExpression *bool_expression) {
  /// do nothing
}
void SymbolTreeVisitor::Visit(Declaration *declaration) {
  if (declaration->IsVariable()) {
    auto variable_declaration = declaration->GetVariableDeclaration();
    if (variable_declaration->GetType()->IsSimpleType()) {
      auto var = current_layer_->DeclareSimpleVariable(Symbol(variable_declaration->GetIdentifier()),
                                                       variable_declaration->GetType()->GetSimpleType());
      classes_[current_class_]->AddField(Symbol(variable_declaration->GetIdentifier()), var);
    } else {
      auto var = current_layer_->DeclareArrayVariable(Symbol(variable_declaration->GetIdentifier()),
                                                      variable_declaration->GetType()->GetArrayType());
      classes_[current_class_]->AddField(Symbol(variable_declaration->GetIdentifier()), var);
    }
  } else {
    declaration->GetMethodDeclaration()->Accept(this);
  }
}
void SymbolTreeVisitor::Visit(DeclarationList *declaration_list) {
  for (auto decl: declaration_list->GetDeclarations()) {
    decl->Accept(this);
  }
}
void SymbolTreeVisitor::Visit(MethodDeclaration *method_declaration) {
  auto method = current_layer_->DeclareMethod(Symbol(method_declaration->GetIdentifier()),
                                              method_declaration);
  classes_[current_class_]->AddMethod(Symbol(method_declaration->GetIdentifier()), method);
  auto new_layer = new ScopeLayer(current_layer_);
  tree_.AddMapping(Symbol(method_declaration->GetIdentifier()), new_layer);
  current_layer_ = new_layer;
  method_declaration->GetType()->Accept(this);
  method_declaration->GetFormals()->Accept(this);
  method_declaration->GetStatements()->Accept(this);

  current_layer_ = current_layer_->GetParent();
}
void SymbolTreeVisitor::Visit(VariableDeclaration *variable_declaration) {
  if (variable_declaration->GetType()->IsSimpleType()) {
    auto var = current_layer_->DeclareSimpleVariable(Symbol(variable_declaration->GetIdentifier()),
                                                     variable_declaration->GetType()->GetSimpleType());
  } else {
    auto var = current_layer_->DeclareArrayVariable(Symbol(variable_declaration->GetIdentifier()),
                                                    variable_declaration->GetType()->GetArrayType());
  }
}
void SymbolTreeVisitor::Visit(ClassDeclaration *class_declaration) {
  current_class_ = Symbol(class_declaration->GetIdentifier());
  auto class_decl = current_layer_->DeclareClass(current_class_,
                                                 class_declaration);
  classes_[current_class_] = class_decl;
  auto new_layer = new ScopeLayer(current_layer_);
  tree_.AddMapping(Symbol(class_declaration->GetIdentifier()), new_layer);
  current_layer_ = new_layer;
  class_declaration->GetDeclarationList()->Accept(this);

  current_layer_ = current_layer_->GetParent();
}
void SymbolTreeVisitor::Visit(ClassDeclarationList *class_declaration_list) {
  for (auto class_decl: class_declaration_list->GetClassDeclarations()) {
    class_decl->Accept(this);
  }
}
void SymbolTreeVisitor::Visit(MainClass *main_class) {
  auto main = current_layer_->DeclareMethod(Symbol("main"),
                                            new MethodDeclaration(main_class->GetStatementList()));
  main_class_ = main;
  current_class_ = Symbol("main");
  auto new_layer = new ScopeLayer(current_layer_);
  tree_.AddMapping(Symbol("main"), new_layer);
  current_layer_ = new_layer;
  main_class->GetStatementList()->Accept(this);
  current_layer_ = current_layer_->GetParent();
}
void SymbolTreeVisitor::Visit(Type *type) {
  if (type->IsSimpleType()) {
    type->GetSimpleType()->Accept(this);
  } else {
    type->GetArrayType()->Accept(this);
  }
}
void SymbolTreeVisitor::Visit(TypeIdentifier *type_identifier) {
  /// do nothing (check for the type is automatically in creation of VariableObject)
}
void SymbolTreeVisitor::Visit(MethodInvocation *method_invocation) {
  method_invocation->GetExpression()->Accept(this);
  if (method_invocation->GetFirst() != nullptr) {
    method_invocation->GetFirst()->Accept(this);
  }
  method_invocation->GetExpressionList()->Accept(this);
  const auto &method_name = method_invocation->GetIdentifier();
  /// check if Method exists
  tree_.GetScopeByName(Symbol(method_name));

}
void SymbolTreeVisitor::Visit(FormalList *formal_list) {
  for (auto formal: formal_list->GetFormals()) {
    formal->Accept(this);
  }
}
void SymbolTreeVisitor::Visit(Formal *formal) {
  if (formal->GetType()->IsSimpleType()) {
    auto var = current_layer_->DeclareSimpleVariable(Symbol(formal->GetIdentifier()),
                                                     formal->GetType()->GetSimpleType());
  } else {
    auto var = current_layer_->DeclareArrayVariable(Symbol(formal->GetIdentifier()),
                                                    formal->GetType()->GetArrayType());
  }
}
void SymbolTreeVisitor::Visit(BinaryOperator *binary_operator) {
}
void SymbolTreeVisitor::Visit(Program *program) {
  program->GetClassDeclarationList()->Accept(this);
  program->GetMainClass()->Accept(this);
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
std::unordered_map<Symbol, std::shared_ptr<ClassType>> SymbolTreeVisitor::GetClasses() const {
  return classes_;
}
std::unordered_set<std::string> SymbolTreeVisitor::GetDeclaredTypes() {
  return declared_types_;
}
std::shared_ptr<MethodType> SymbolTreeVisitor::GetMainClass() const {
  return main_class_;
}
