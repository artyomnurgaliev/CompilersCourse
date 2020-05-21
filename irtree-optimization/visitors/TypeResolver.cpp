#include <method-mechanisms/ClassStorage.h>
#include "TypeResolver.h"

#include "elements.h"

void TypeResolver::Visit(SimpleType *simple_type) {

}
void TypeResolver::Visit(ArrayType *array_type) {

}
void TypeResolver::Visit(AssertStatement *assert_statement) {

}
void TypeResolver::Visit(AssignmentStatement *assignment_statement) {

}
void TypeResolver::Visit(IfStatement *if_statement) {

}
void TypeResolver::Visit(IfElseStatement *if_else_statement) {

}
void TypeResolver::Visit(LocalVariableDeclaration *local_variable_declaration) {

}
void TypeResolver::Visit(LocalVariableDeclarationStatement *local_variable_declaration_statement) {

}
void TypeResolver::Visit(MethodInvocationStatement *method_invocation_statement) {

}
void TypeResolver::Visit(ReturnStatement *return_statement) {

}
void TypeResolver::Visit(ScopeStatement *scope_statement) {

}
void TypeResolver::Visit(SoutStatement *sout_statement) {

}
void TypeResolver::Visit(Statement *statement) {

}
void TypeResolver::Visit(StatementList *statement_list) {

}
void TypeResolver::Visit(WhileStatement *while_statement) {

}
void TypeResolver::Visit(Lvalue *lvalue) {

}
void TypeResolver::Visit(SimpleLvalue *simple_lvalue) {

}
void TypeResolver::Visit(ArrayElementLvalue *array_element_lvalue) {

}
void TypeResolver::Visit(AccessToArrayElementExpression *access_to_array_element_expression) {
  tos_value_ = Accept(access_to_array_element_expression->GetFirst());
}
void TypeResolver::Visit(ArrayNewExpression *array_new_expression) {
  tos_value_ = array_new_expression->GetSimpleType()->GetSimpleTypeIdentifier();
}
void TypeResolver::Visit(ArrayLengthExpression *array_length_expression) {
  tos_value_ = "int";
}
void TypeResolver::Visit(BinaryOperatorExpression *binary_operator_expression) {
  tos_value_ = Accept(binary_operator_expression->GetFirst());
}
void TypeResolver::Visit(NewExpression *new_expression) {
  tos_value_ = new_expression->GetTypeIdentifier()->GetIdentifier();
}
void TypeResolver::Visit(Expression *expression) {

}
void TypeResolver::Visit(ExpressionList *expression_list) {

}
void TypeResolver::Visit(IdentExpression *ident_expression) {
  const auto &id = ident_expression->GetIdentifier();
  auto type = irtree_build_visitor_->GetCurrentLayer()->Get(Symbol(id));
  tos_value_ = type->GetTypeName();
}
void TypeResolver::Visit(MethodInvocationExpression *method_invocation_expression) {
  std::string object_type = Accept(method_invocation_expression->GetMethodInvocation()->GetExpression());
  std::string method = method_invocation_expression->GetMethodInvocation()->GetIdentifier();

  auto methods = ClassStorage::GetInstance().GetMethods(Symbol(object_type));
  if (methods.find(Symbol(method)) == methods.end()) {
    throw std::runtime_error("This object doesn't have such method");
  } else {
    auto result = methods[Symbol(method)];
    tos_value_ = result->GetReturnValueType()->GetType();
  }
}
void TypeResolver::Visit(NotExpression *not_expression) {
  tos_value_ = Accept(not_expression->GetExpression());
}
void TypeResolver::Visit(NumberExpression *number_expression) {
  tos_value_ = "int";
}
void TypeResolver::Visit(ParenthesisExpression *parenthesis_expression) {
  tos_value_ = Accept(parenthesis_expression->GetExpression());
}
void TypeResolver::Visit(ThisExpression *this_expression) {
  tos_value_ = irtree_build_visitor_->GetCurrentClassName();
}
void TypeResolver::Visit(BoolExpression *bool_expression) {
  tos_value_ = "boolean";
}
void TypeResolver::Visit(Declaration *declaration) {

}
void TypeResolver::Visit(DeclarationList *declaration_list) {

}
void TypeResolver::Visit(MethodDeclaration *method_declaration) {

}
void TypeResolver::Visit(VariableDeclaration *variable_declaration) {

}
void TypeResolver::Visit(ClassDeclaration *class_declaration) {

}
void TypeResolver::Visit(ClassDeclarationList *class_declaration_list) {

}
void TypeResolver::Visit(MainClass *main_class) {

}
void TypeResolver::Visit(Type *type) {

}
void TypeResolver::Visit(TypeIdentifier *type_identifier) {

}
void TypeResolver::Visit(MethodInvocation *method_invocation) {

}
void TypeResolver::Visit(FormalList *formal_list) {

}
void TypeResolver::Visit(Formal *formal) {

}
void TypeResolver::Visit(BinaryOperator *binary_operator) {

}
void TypeResolver::Visit(Program *program) {

}
TypeResolver::TypeResolver(IrtreeBuildVisitor *irtree_build_visitor) : irtree_build_visitor_(irtree_build_visitor) {
}
