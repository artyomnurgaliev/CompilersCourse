#include <iostream>
#include <method-mechanisms/ClassStorage.h>
#include <objects/objs/ArrayObject.h>
#include <objects/objs/VariableObject.h>
#include "MethodCallVisitor.h"

#include "elements.h"
MethodCallVisitor::MethodCallVisitor(ScopeLayer *method_scope,
                                     std::shared_ptr<MethodType> method,
                                     VariableObject *this_obj) :
  frame(method->GetMethodDeclaration()->GetFormals()->GetSize()),
  root_layer(method_scope),
  this_(this_obj) {
  current_layer_ = root_layer;
  offsets_.push(0);
  tos_value_ = new VariableObject(
    new PrimitiveSimpleType(
      new SimpleType("int")),
    0);
  std::vector<Object *> fields;
  int index = -1;
  for (const auto &field : this_obj->GetFields()) {
    fields.push_back(field.second);
    table_.CreateVariable(field.first);
    table_.Put(field.first, index);
    --index;
  }
  frame.SetFields(fields);
}

void MethodCallVisitor::Visit(SimpleType *simple_type) {
  /// do nothing
}
void MethodCallVisitor::Visit(ArrayType *array_type) {
  /// do nothing
}
void MethodCallVisitor::Visit(AssertStatement *assert_statement) {
  if (!Accept(assert_statement->GetExpression())->GetValue()) {
    throw std::runtime_error("Assert failed");
  }
}
void MethodCallVisitor::Visit(AssignmentStatement *assignment_statement) {
  auto result = Accept(assignment_statement->GetExpression());
  int index = table_.Get(Symbol(assignment_statement->GetLvalue()->GetIdentifier()));
  if (assignment_statement->GetLvalue()->IsSimple()) {
    frame.Set(index, result);
  } else {
    int index_in_array = Accept(assignment_statement->GetLvalue())->GetValue();
    dynamic_cast<ArrayObject *>(frame.Get(index))->SetAtIndex(result, index_in_array);
  }

}
void MethodCallVisitor::Visit(IfStatement *if_statement) {
  if (Accept(if_statement->GetExpression())->GetValue()) {
    current_layer_ = current_layer_->GetChild(offsets_.top());
    offsets_.push(0);
    frame.AllocScope();
    table_.BeginScope();
    if_statement->GetStatement()->Accept(this);
    offsets_.pop();
    size_t index = offsets_.top();
    offsets_.pop();
    offsets_.push(index + 1);
    current_layer_ = current_layer_->GetParent();
    frame.DeallocScope();
    table_.EndScope();
  }
}
void MethodCallVisitor::Visit(IfElseStatement *if_else_statement) {
  if (Accept(if_else_statement->GetExpression())->GetValue()) {
    current_layer_ = current_layer_->GetChild(offsets_.top());
    offsets_.push(0);
    frame.AllocScope();
    table_.BeginScope();
    if_else_statement->GetStatement()->Accept(this);
    offsets_.pop();
    size_t index = offsets_.top();
    offsets_.pop();
    offsets_.push(index + 2);
    current_layer_ = current_layer_->GetParent();
    frame.DeallocScope();
    table_.EndScope();
  } else {
    current_layer_ = current_layer_->GetChild(offsets_.top() + 1);
    offsets_.push(0);
    frame.AllocScope();
    table_.BeginScope();
    if_else_statement->GetElseStatement()->Accept(this);
    offsets_.pop();
    size_t index = offsets_.top();
    offsets_.pop();
    offsets_.push(index + 2);
    current_layer_ = current_layer_->GetParent();
    frame.DeallocScope();
    table_.EndScope();
  }
}
void MethodCallVisitor::Visit(LocalVariableDeclaration *local_variable_declaration) {
  local_variable_declaration->GetVariableDeclaration()->Accept(this);
}
void MethodCallVisitor::Visit(MethodInvocationStatement *method_invocation_statement) {
  method_invocation_statement->GetMethodInvocation()->Accept(this);
}
void MethodCallVisitor::Visit(ReturnStatement *return_statement) {
  if (frame.HasParent()) {
    frame.SetParentReturnValue(Accept(return_statement->GetExpression()));
  }
  returned_ = true;
}
void MethodCallVisitor::Visit(ScopeStatement *scope_statement) {
  current_layer_ = current_layer_->GetChild(offsets_.top());
  offsets_.push(0);
  frame.AllocScope();
  table_.BeginScope();
  scope_statement->GetStatementList()->Accept(this);
  offsets_.pop();
  size_t index = offsets_.top();
  offsets_.pop();
  offsets_.push(index + 1);
  current_layer_ = current_layer_->GetParent();
  frame.DeallocScope();
  table_.EndScope();
}
void MethodCallVisitor::Visit(SoutStatement *sout_statement) {
  std::cout << Accept(sout_statement->GetExpression())->GetValue() << std::endl;
}
void MethodCallVisitor::Visit(StatementList *statement_list) {
  for (auto statement : statement_list->GetStatements()) {
    if (!returned_) {
      statement->Accept(this);
    }
  }
}
void MethodCallVisitor::Visit(WhileStatement *while_statement) {
  while (Accept(while_statement->GetExpression())->GetValue()) {
    current_layer_ = current_layer_->GetChild(offsets_.top());
    offsets_.push(0);
    frame.AllocScope();
    table_.BeginScope();
    while_statement->GetStatement()->Accept(this);
    offsets_.pop();
    current_layer_ = current_layer_->GetParent();
    frame.DeallocScope();
    table_.EndScope();
  }
  size_t index = offsets_.top();
  offsets_.pop();
  offsets_.push(index + 1);
}
void MethodCallVisitor::Visit(SimpleLvalue *simple_lvalue) {
  /// do nothing
}
void MethodCallVisitor::Visit(ArrayElementLvalue *array_element_lvalue) {
  tos_value_ = Accept(array_element_lvalue->GetExpression());
}
void MethodCallVisitor::Visit(AccessToArrayElementExpression *access_to_array_element_expression) {
  int index = Accept(access_to_array_element_expression->GetSecond())->GetValue();
  tos_value_ = dynamic_cast<ArrayObject *>(Accept(access_to_array_element_expression->GetFirst()))->AtIndex(index);
}
void MethodCallVisitor::Visit(ArrayNewExpression *array_new_expression) {
  auto new_arr =
    new ArrayObject(
      new PrimitiveArrayType(
        new PrimitiveSimpleType(array_new_expression->GetSimpleType())));
  size_t size = Accept(array_new_expression->GetExpression())->GetValue();
  new_arr->Resize(size);
  tos_value_ = new_arr;
}
void MethodCallVisitor::Visit(ArrayLengthExpression *array_length_expression) {
  auto arr = Accept(array_length_expression->GetExpression());
  int size = dynamic_cast<ArrayObject *>(arr)->GetSize();
  tos_value_ = new VariableObject(
    new PrimitiveSimpleType(
      new SimpleType("int")), size);
}
void MethodCallVisitor::Visit(BinaryOperatorExpression *binary_operator_expression) {
  auto leftobj = Accept(binary_operator_expression->GetFirst());
  auto rightobj = Accept(binary_operator_expression->GetSecond());
  auto left_type = leftobj->GetType()->GetTypeName();
  auto right_type = rightobj->GetType()->GetTypeName();

  auto left = leftobj->GetValue();
  auto right = rightobj->GetValue();
  if (left_type != right_type) {
    throw std::runtime_error("Different types of binary expression parts");
  }
  if (left_type != "int" && left_type != "boolean") {
    throw std::runtime_error("Strange type for binary expression");
  }
  auto op = binary_operator_expression->GetBinaryOperator()->GetOperatorName();
  std::string result_type;
  int result;
  if (op == "&&") {
    result = left && right;
    result_type = "boolean";
  }
  if (op == "||") {
    result = left || right;
    result_type = "boolean";
  }
  if (op == "<") {
    result = left < right;
    result_type = "boolean";
  }
  if (op == ">") {
    result = left > right;
    result_type = "boolean";
  }
  if (op == "==") {
    result = left == right;
    result_type = "boolean";
  }
  if (op == "+") {
    result = left + right;
    result_type = "int";
  }
  if (op == "-") {
    result = left - right;
    result_type = "int";
  }
  if (op == "*") {
    result = left * right;
    result_type = "int";
  }
  if (op == "/") {
    result = left / right;
    result_type = "int";
  }
  if (op == "%") {
    result = left % right;
    result_type = "int";
  }

  tos_value_ = new VariableObject(new PrimitiveSimpleType(new SimpleType(result_type)), result);
}
void MethodCallVisitor::Visit(NewExpression *new_expression) {
  tos_value_ = new VariableObject(
    new PrimitiveSimpleType(
      new SimpleType(new_expression->GetTypeIdentifier())));
}
void MethodCallVisitor::Visit(ExpressionList *expression_list) {
  /// do nothing (it is params in method invocation)
}
void MethodCallVisitor::Visit(IdentExpression *ident_expression) {
  int index = table_.Get(Symbol(ident_expression->GetIdentifier()));
  tos_value_ = frame.Get(index);
}
void MethodCallVisitor::Visit(MethodInvocationExpression *method_invocation_expression) {
  tos_value_ = Accept(method_invocation_expression->GetMethodInvocation());
}
void MethodCallVisitor::Visit(NotExpression *not_expression) {
  int result = Accept(not_expression->GetExpression())->GetValue();
  result = !result;
  tos_value_ = new VariableObject(
    new PrimitiveSimpleType(
      new SimpleType("boolean")), result);
}
void MethodCallVisitor::Visit(NumberExpression *number_expression) {
  tos_value_ = new VariableObject(
    new PrimitiveSimpleType(
      new SimpleType("int")),
    number_expression->GetValue());
}
void MethodCallVisitor::Visit(ParenthesisExpression *parenthesis_expression) {
  tos_value_ = Accept(parenthesis_expression->GetExpression());
}
void MethodCallVisitor::Visit(ThisExpression *this_expression) {
  tos_value_ = this_;
}
void MethodCallVisitor::Visit(BoolExpression *bool_expression) {
  tos_value_ = new VariableObject(
    new PrimitiveSimpleType(
      new SimpleType("boolean")),
    bool_expression->GetValue());
}
void MethodCallVisitor::Visit(Declaration *declaration) {
  if (declaration->IsVariable()) {
    declaration->GetVariableDeclaration()->Accept(this);
  } else {
    declaration->GetMethodDeclaration()->Accept(this);
  }
}
void MethodCallVisitor::Visit(DeclarationList *declaration_list) {
  for (auto d: declaration_list->GetDeclarations()) {
    d->Accept(this);
  }
}
void MethodCallVisitor::Visit(MethodDeclaration *method_declaration) {
  method_declaration->GetFormals()->Accept(this);
  method_declaration->GetStatements()->Accept(this);
}
void MethodCallVisitor::Visit(VariableDeclaration *variable_declaration) {
  size_t index;
  if (variable_declaration->GetType()->IsSimpleType()) {
    index = frame.AllocVariable(new PrimitiveSimpleType(
      variable_declaration->GetType()->GetSimpleType()));
  } else {
    index = frame.AllocVariable(new PrimitiveArrayType(
      variable_declaration->GetType()->GetArrayType()));
  }
  table_.CreateVariable(Symbol(variable_declaration->GetIdentifier()));
  table_.Put(Symbol(variable_declaration->GetIdentifier()), index);
}
void MethodCallVisitor::Visit(ClassDeclaration *class_declaration) {
  /// do nothing
}
void MethodCallVisitor::Visit(ClassDeclarationList *class_declaration_list) {
  /// do nothing
}
void MethodCallVisitor::Visit(MainClass *main_class) {
  main_class->GetStatementList()->Accept(this);
}
void MethodCallVisitor::Visit(Type *type) {
  /// do nothing
}
void MethodCallVisitor::Visit(TypeIdentifier *type_identifier) {
  /// do nothing
}
void MethodCallVisitor::Visit(MethodInvocation *method_invocation) {
  std::cout << "Method called " << method_invocation->GetIdentifier() << std::endl;
  /*auto method_type = current_layer_->Get(Symbol(method_invocation->GetIdentifier()));

  std::shared_ptr<MethodType> method_converted = std::dynamic_pointer_cast<MethodType>(method_type);
  if (method_converted == nullptr) {
    throw std::runtime_error("Method not defined");
  }*/

  auto *object = dynamic_cast<VariableObject *>(Accept(method_invocation->GetExpression()));

  std::string object_class = object->GetType()->GetTypeName();
  auto methods = ClassStorage::GetInstance().GetMethods(Symbol(object_class));
  if (methods.find(Symbol(method_invocation->GetIdentifier())) == methods.end()) {
    throw std::runtime_error("Can't call this method from object of this type");
  }
  std::vector<Object *> params;
  auto *expression_list = new ExpressionList();
  if (method_invocation->GetFirst() != nullptr) {
    expression_list->AddExpression(method_invocation->GetFirst());
  }
  for (auto expr: method_invocation->GetExpressionList()->GetExpressions()) {
    expression_list->AddExpression(expr);
  }
  for (auto expr : expression_list->GetExpressions()) {
    params.push_back(Accept(expr));
  }
  auto method = methods[Symbol(method_invocation->GetIdentifier())];

  MethodCallVisitor new_visitor(
    tree_->GetScopeByName(Symbol(method_invocation->GetIdentifier())),
    method,
    object
  );
  new_visitor.SetParams(params);
  new_visitor.SetTree(tree_);
  new_visitor.GetFrame().SetParentFrame(&frame);
  new_visitor.Visit(method->GetMethodDeclaration());
  tos_value_ = frame.GetReturnValue();
}

void MethodCallVisitor::Visit(FormalList *formal_list) {
  int index = -frame.GetFieldsSize() - 1;
  for (auto formal : formal_list->GetFormals()) {
    table_.CreateVariable(Symbol(formal->GetIdentifier()));
    table_.Put(Symbol(formal->GetIdentifier()), index);
    --index;
  }
}
void MethodCallVisitor::Visit(Formal *formal) {
  /// realization in formal_list
}
void MethodCallVisitor::Visit(BinaryOperator *binary_operator) {
  /// do nothing
}
void MethodCallVisitor::Visit(Program *program) {
  /// do nothing, because Visitor starts from "main"
}
void MethodCallVisitor::Visit(Expression *expression) {
  /// do nothing
}
void MethodCallVisitor::Visit(Lvalue *lvalue) {
  /// do nothing
}
void MethodCallVisitor::Visit(Statement *statement) {
  /// do nothing
}
void MethodCallVisitor::Visit(LocalVariableDeclarationStatement *local_variable_declaration_statement) {
  local_variable_declaration_statement->GetLocalVariableDeclaration()->Accept(this);
}

void MethodCallVisitor::SetTree(ScopeLayerTree *tree) {
  tree_ = tree;
}

Frame &MethodCallVisitor::GetFrame() {
  return frame;
}
void MethodCallVisitor::SetParams(const std::vector<Object *> &params) {
  frame.SetParams(params);
}
